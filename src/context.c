
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

System_Context_t *context_create(System_Context_t *context) {
	if (debug) printf("[:] context: creating new context\n");

	// Allocate the context
	context = (System_Context_t *)malloc(sizeof(System_Context_t));
	if (context == NULL) return NULL;

	// Initialize the context
	context->num_blocks = 0;
	context->memblocks = NULL;

	// Initialize the CPU emulation context
	cpu_context_init(context);

	return context;
}

void context_add_memblock(System_Context_t *context, struct Memblock *block) {
	if (debug) printf("[:] context: adding memblock with base $%X and length $%X\n", block->address, block->len);

	// Get a pointer to the last memblock pointer in the list
	// This gets a little messy with the double pointers and all
	struct Memblock **ptr = traverse_memblock_list(context, context->num_blocks);
	// Write the address of the new memblock to the place pointed to by ptr
	// ptr needs to be a double pointer so that we can directly fiddle with the pointers inside the structs
	*ptr = block;
	if (context->num_blocks >= 1) (*traverse_memblock_list(context, context->num_blocks-1))->next = block;

	// We now have one more memblock to keep track of
	context->num_blocks++;

}

struct Memblock **traverse_memblock_list(System_Context_t *context, const int index) {
	if (debug) printf("[:] context: traversing memblocks to index %d\n", index);

	// Abort if we're looking for a memblock that definitely doesn't exist
	if (context->num_blocks < index) return_error("[!] Queried memblock invalid: %d\n", index);
	// Preload the pointer pointer with the address of the pointer in the context struct
	// We use double pointers so that we can access the struct members as individuals
	struct Memblock **ptr = &(context->memblocks);
	// Travel down the linked list to our needed index
	for (int i = 0; i < index; i++) ptr = &(*ptr)->next;
	return ptr;
}

void print_memblock(struct Memblock *block) {
	printf("memblock at address %X:\n", block);
	if (block == NULL) {
		printf("   NULL POINTER\n");
		return;
	}
	printf("   data: $%08X\n", block->data);
	printf("   len: $%X\n", block->len);
	printf("   address: $%X\n", block->address);
	printf("   flags: $%X\n", block->flags);
	if (block->name) printf("   name: %s\n", block->name);
	printf("   next: $%08X\n", block->next);
}

int add_default_memblocks(System_Context_t *context) {
	struct Memblock *blockptr;
	for (int i = 0; i < NUM_DEFAULT_MEMBLOCKS; i++) {
		if (debug) printf("[:] Adding default memblock '%s'\n", system_default_memblocks[i].name);
		// Copy the constant memblock into memory
		blockptr = (struct Memblock *)malloc(sizeof(struct Memblock));
		if (blockptr == NULL) return_error("[!] Failed to allocate memory for memblock\n");
		blockptr->len = system_default_memblocks[i].len;
		blockptr->address = system_default_memblocks[i].address;
		blockptr->flags = system_default_memblocks[i].flags;
		blockptr->name = system_default_memblocks[i].name;
		blockptr->next = system_default_memblocks[i].next;
		if (system_default_memblocks[i].flags == MEMBLOCK_FLAG_MIRROR) {
			blockptr->data == blockptr->address;
		} else {
			blockptr->data = (uint8_t *)malloc(blockptr->len);
			if (blockptr->data == NULL) return_error("[!] Failed to allocate data memory for memblock\n");
		}

		context_add_memblock(context, blockptr);
	}
}
