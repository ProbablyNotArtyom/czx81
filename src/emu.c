
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
	#include <rom.h>

//-------------------------------------------------

#define Z80_CPU_SPEED           4000000   /* In Hz. */
#define CYCLES_PER_STEP         1
#define MAXIMUM_STRING_LENGTH   100

//-------------------------------------------------

void setup_system(char *rom_filename) {

	// Init the context
	main_context = context_create(main_context);

	// Init the ROM memblock for the context
	struct Memblock	*rom_memblock = (struct Memblock *)malloc(sizeof(struct Memblock));
	// If we have been given a filename to load, prioritize that over the included ROM
	if (rom_filename != NULL) {
		FILE *rom;
		if ((rom = fopen(rom_filename, "rb")) == NULL) return_error("[!] System ROM not found: %s.\n", rom_filename);
		// File found, Load the ROM & its attributes
		fseek(rom, 0, SEEK_END);
		rom_memblock->len = ftell(rom);
		fseek(rom, 0, SEEK_SET);
		rom_memblock->data = (uint8_t *)malloc(rom_memblock->len);
		fread(rom_memblock->data + rom_memblock->address, 1, rom_memblock->len, rom);
		fclose(rom);
	} else {
		// The -r option wasn't passed to main, so use the internal ROM
		rom_memblock->len = zx81_rom_len;
		rom_memblock->data = &zx81_rom;
	}

	// Set the virtual address of the ROM & make sure its readable
	rom_memblock->address = 0x0000;
	rom_memblock->flags = MEMBLOCK_FLAG_READ;
	rom_memblock->name = NULL;
	// Add the ROM memblock to the emulator context
	context_add_memblock(main_context, rom_memblock);
	add_default_memblocks(main_context);

	// Initialize the video hardware stuff
	setup_video();

	//print_memblock(main_context->memblocks);
	//uint8_t dat = read_memspace_byte(main_context, 0x1000);
	//printf("$%X\n", dat);
}

uint8_t read_memspace_byte(System_Context_t *context, size_t address) {
	if (debug > 3) printf("memspace: reading byte at $%X\n", address);

	// Preload the pointer with the address of the first memblock
	// Then iterate through as many as possible
	struct Memblock **ptr = &(context->memblocks);
	struct Memblock *blockptr;
	for (int i = 0; i < context->num_blocks; i++) {
		blockptr = (*ptr);
		// Abort if the memblock doesn't exist
		if (blockptr == NULL) return NULL;
		// Check if the address is in the memblock's range, and break if so
		if ((address >= blockptr->address) && (address < (blockptr->address + blockptr->len))) break;
		// If it's not in range, then try the next memblock
		ptr = &(*ptr)->next;
	}

	// If no memblocks match, then return a garbage byte, in this case NULL
	if (blockptr == NULL) return 0x00;
	// Make sure the memblock that did match is capable of being read from
	if (blockptr->flags & MEMBLOCK_FLAG_READ) {
		// Subtract the read address from the memblock base to get the address's index in the memblock's data array
		return (blockptr->data[address - blockptr->address]);
	}
	// We can't read from the matched memblock, so for now just return NULL
	if (debug > 2) puts("[!] Attempted write to read-only memblock.\n");
	return 0x00;
}

void write_memspace_byte(System_Context_t *context, size_t address, uint8_t val) {
	if (debug > 3) printf("memspace: writing $%X to $%X\n", val, address);

	// Preload the pointer with the address of the first memblock
	// Then iterate through as many as possible
	struct Memblock *ptr = context->memblocks;
	for (int i = 0; i < context->num_blocks; i++) {
		// Abort if the memblock doesn't exist
		if (ptr == NULL) return NULL;
		// Check if the address is in the memblock's range, and break if so
		if ((address >= ptr->address) && (address < (ptr->address + ptr->len))) break;
		// If it's not in range, then try the next memblock
		else ptr = ptr->next;
	}

	// If no memblocks match, then pretend nothing happened
	if (ptr == NULL) return;
	// Make sure the memblock that did match is capable of being written to
	if (ptr->flags & MEMBLOCK_FLAG_WRITE) {
		// Subtract the read address from the memblock base to get the address's index in the memblock's data array
		// Then write the value to it
		ptr->data[address - ptr->address] = val;
	}
}
