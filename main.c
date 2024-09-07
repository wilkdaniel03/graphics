#include <stdio.h>
#include "_deps/sdl2-src/include/SDL.h"
#include "glad.h"

SDL_Window *win;
SDL_GLContext ctx;

int main() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		fprintf(stderr,"Failed to init\n");
	win = SDL_CreateWindow(
		"Hello GL",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		500,
		500,
		SDL_WINDOW_OPENGL
	);
	ctx = SDL_GL_CreateContext(win);
	if(SDL_GL_MakeCurrent(win,ctx) < 0)
		fprintf(stderr,"Failed to attach context\n");

	gladLoadGLLoader(SDL_GL_GetProcAddress);
	gladLoadGL();
	glClearColor(0.,0.5,0.,1.);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(win);

	SDL_Event event;

	while(1) {
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
			break;
	}

	return 0;
}
