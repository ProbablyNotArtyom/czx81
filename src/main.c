

	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>

	#include <GL/glew.h>

	#include <stdlib.h>
	#include <stdbool.h>
	#include <stdio.h>
	#include <time.h>
	#include <math.h>
	#include <unistd.h>

	#include <z80.h>
	#include <system.h>
	#include <emu.h>

//-------------------------------------------------

#define FB_WIDTH 	256
#define FB_HEIGHT 	192

//-------------------------------------------------

System_Context_t 	*main_context;

SDL_Window 		*window;
SDL_Texture 	*frame;
SDL_Renderer	*renderer;

int				debug;

static char 	*helptxt = {
	"SDL2 zx81 emulator written by NotArtyom\r\n"
	"Usage: zx81 [-h][-d] -r path_to_rom\r\n"
	"\r\n"
	"    -h           shows this help text\r\n"
	"    -r <file>    uses <file> as the zx81 system ROM\r\n"
	"    -d <level>   enables debug mode. multiple debug args will increase verbosity\r\n"
};

//-------------------------------------------------

int main(int argc, char *argv[]) {
	debug = false;
	int opt;
	char *rom_filename = NULL;

	// Parse the command line options and handle and flags
	while ((opt = getopt(argc, argv, "r:hd")) != -1) {
		switch (opt) {
			case 'r':
				rom_filename = optarg;
				break;
			default:
			case 'h':
				fprintf(stderr, helptxt);
				exit(0);
				break;
			case 'd':
				debug++;
				break;
		}
	}

	// Make sure we aren't running blind
	if (SDL_Init(SDL_INIT_VIDEO)) return_error("[!] SDL failed to init.\n");

	// Create the main SDL window
	// Also create the main renderer used for copying the framebuffer around
	window = SDL_CreateWindow( "zx81 / NotArtyom", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_UTILITY);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	// Create a white border around the main render area
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	// Enable integer scaling. float scaling is possible, but due to a bug in SDL2, it doesn't function properly with tile based screens
	// So we settle for integer scaling
	SDL_RenderSetIntegerScale(renderer, true);
	// Make sure the active render area is always centered in the border area no matter what size the window is
	SDL_RenderSetLogicalSize(renderer, FB_WIDTH, FB_HEIGHT);

	// Call the toplevel setup function that handles the machine specific initialization
	setup_system(rom_filename);

	// The main rendering loop
	bool quit = false;
	SDL_Event sdl_event;
	while (!quit) {
        while(SDL_PollEvent(&sdl_event) != 0) {
            // If ESC button is pressed, exit the render loop next time around
            if(sdl_event.type == SDL_QUIT) quit = true;
        }
		// Clear the toplevel renderer
		SDL_RenderClear(renderer);
		// Render the VRAM contents onto the toplevel renderer
		render_vram(renderer);
		// Update the window with the new frame
		SDL_RenderPresent(renderer);
		cycle_system(main_context);
	}

	// Clean up after ourselves
	SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}

// Returns a formatted error message and exits main()
void return_error(char *err, ...) {
	va_list ap;
	va_start(ap, err);

	char buffer[512];
	vsnprintf(buffer, 511, err, ap);
	fprintf(stderr, buffer);
	va_end(ap);
	exit(-1);
}
