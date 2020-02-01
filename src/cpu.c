
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <GL/glew.h>

	#include <stdlib.h>
	#include <stdbool.h>
	#include <stdio.h>
	#include <time.h>
	#include <math.h>

	#include <z80.h>
	#include <system.h>
	#include <emu.h>

//-------------------------------------------------

static uint8_t cpu_mem_read_callback(int param, ushort address) {
	return read_memspace_byte(main_context, address);
}

static void cpu_mem_write_callback(int param, ushort address, uint8_t data) {
	return write_memspace_byte(main_context, address, data);
}

static uint8_t cpu_io_read_callback(int param, ushort address) {
	uint8_t data = address >> 8;
    if (data == 0xFE) system_nmi_enabled = true;
	if (data == 0xFD) system_nmi_enabled = false;
    return data;
}

static void cpu_io_write_callback(int param, ushort address, uint8_t data) {
	if (debug > 0)printf("PW %02x\n", data);
}

void cpu_context_init(System_Context_t *context) {
	if (debug) printf("[:] Creating CPU context\n");

	context->context.memRead = cpu_mem_read_callback;
    context->context.memWrite = cpu_mem_write_callback;
    context->context.ioRead = cpu_io_read_callback;
    context->context.ioWrite = cpu_io_write_callback;
	cpu_do_reset(context);
}

void cpu_do_reset (System_Context_t *context) {
	Z80RESET(&context->context);
}

void cpu_do_step(System_Context_t *context, const int steps) {
	for (int i = 0; i < steps; i++) {
		if (debug > 1) {
			char instrbuff[64];
			Z80Debug(&context->context, NULL, &instrbuff);
			printf("%s\n", instrbuff);
		}
		Z80Execute(&context->context);
	}
}

void cycle_system(System_Context_t *context) {
	cpu_do_step(context, 1);
}
