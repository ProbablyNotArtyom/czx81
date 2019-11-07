
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
	if (debug) printf("context: creating new context\n");

	// Allocate the context
	context = (System_Context_t *)malloc(sizeof(System_Context_t));
	if (context == NULL) return NULL;

	// Initialize the context
	context->num_blocks = 0;
	context->memblocks = NULL;

	return context;
}

void context_add_memblock(System_Context_t *context, struct Memblock *block) {
	if (debug) printf("context: adding memblock with base $%X and length $%X\n", block->address, block->len);

	// Get a pointer to the last memblock pointer in the list
	// This gets a little messy with the double pointers and all
	struct Memblock **ptr = traverse_memblock_list(context, context->num_blocks);
	// Write the address of the new memblock to the place pointed to by ptr
	// ptr needs to be a double pointer so that we can directly fiddle with the pointers inside the structs
	*ptr = block;
	// We now have one more memblock to keep track of
	context->num_blocks++;
}

struct Memblock **traverse_memblock_list(System_Context_t *context, const int index) {
	if (debug) printf("context: traversing memblocks to index %d\n", index);

	// Abort if we're looking for a memblock that definitely doesn't exist
	if (context->num_blocks < index) return NULL;
	// Preload the pointer pointer with the address of the pointer in the context struct
	// We use double pointers so that we can access the struct members as individuals
	struct Memblock **ptr = &(context->memblocks);
	// Travel down the linked list to our needed index
	for (int i = 0; i < index; i++) ptr = (*ptr)->next;
	return ptr;
}

void print_memblock(struct Memblock *block) {
	printf("memblock:\n");
	if (block == NULL) {
		printf("   NULL POINTER\n");
		return;
	}
	printf("   data: $%08X\n", block->data);
	printf("   len: $%X\n", block->len);
	printf("   address: $%X\n", block->address);
	printf("   flags: $%X\n", block->flags);
	printf("   name: %s\n", block->name);
	printf("   next: $%08X\n", block->next);
}
