//-------------------------------------------------
// Header for definitions of system attributes
//-------------------------------------------------

#ifndef _EMUDEFS_HEADER
#define _EMUDEFS_HEADER

	#include <z80.h>
	#include "system.h"

//-------------------------------------------------

#define MEMBLOCK_FLAG_READ		0b00000001		// Memory can be read from
#define MEMBLOCK_FLAG_WRITE		0b00000010		// Memory can be written to
#define MEMBLOCK_FLAG_RW		0b00000011

#define DEFINE_MEMBLOCK(name,ptr,len,addr,flag)	\
	{ ptr, len, addr, flag, name, 0 }

struct Memblock {
	uint8_t				*data;		// Pointer to the segment's data
	size_t				len;		// Length of the memory segment
	size_t				address;	// Address of the segment in the emulated memory space
	uint8_t				flags;		// Attributes of the memblock

	char		 		*name;		// Name string of the memblock. optional
	struct Memblock		*next;		// Next memblock in list
};

typedef struct {
	Z80Context 			context;		// CPU Emulator context
	struct Memblock		*memblocks;		// Memory segments
	size_t				num_blocks;		// Number of memblocks
} System_Context_t;

//-------------------------------------------------

extern System_Context_t 	*main_context;

extern SDL_Window 			*window;
extern SDL_Texture 			*frame;
extern SDL_Renderer			*renderer;
extern SDL_GLContext 		*glcontext;

extern bool					debug;

//-------------------------------------------------

void return_error(char *err, ...);
void render_vram(SDL_Renderer *renderer);
void setup_system(char *);
void cycle_system();

uint8_t read_memspace_byte(System_Context_t *context, size_t address);
void write_memspace_byte(System_Context_t *context, size_t address, uint8_t val);

System_Context_t *context_create(System_Context_t *context);
void context_add_memblock(System_Context_t *context, struct Memblock *block);
struct Memblock **traverse_memblock_list(System_Context_t *context, const int index);
void print_memblock(struct Memblock *block);

//-------------------------------------------------
#endif
