#include <stdio.h>
#include <stdlib.h>
#include "_deps/sdl2-src/include/SDL.h"
#include "glad.h"

#include "shader.cc"

#define WIDTH 1920*0.3
#define HEIGHT 1080*0.4

SDL_Window *win;
SDL_GLContext ctx;

const double TRIANGLE_VERTICES[3][2] = {
	{ -1., -1. },
	{ 1., -1. },
	{ -1, 1. }
};

const double TRIANGLE_VERTICES2[3][2] = {
	{ 1., 1. },
	{ 1., -1. },
	{ -1., 1. }
};

void render_triangle(Shader *shader) {
	unsigned int vao;
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	unsigned int vbo;
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(TRIANGLE_VERTICES),TRIANGLE_VERTICES,GL_STATIC_DRAW);
	glVertexAttribPointer(0,2,GL_DOUBLE,GL_FALSE,2*sizeof(double),(void *)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(vao);
	shader->use();
	shader->set_color(1.,0.,0.,1.);
	glDrawArrays(GL_TRIANGLES,0,3);

	glBindVertexArray(vao);
	glBufferData(GL_ARRAY_BUFFER,sizeof(TRIANGLE_VERTICES2),TRIANGLE_VERTICES2,GL_STATIC_DRAW);
	glBindVertexArray(vao);
	shader->set_color(0.,1.,0.,1.);
	glDrawArrays(GL_TRIANGLES,0,3);
}

int main() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		fprintf(stderr,"Failed to init\n");
	win = SDL_CreateWindow(
		"Hello GL",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_OPENGL
	);

	ctx = SDL_GL_CreateContext(win);
	if(SDL_GL_MakeCurrent(win,ctx) < 0)
		fprintf(stderr,"Failed to attach context\n");

	gladLoadGLLoader(SDL_GL_GetProcAddress);
	gladLoadGL();

	glViewport(0,0,WIDTH,HEIGHT);

	SDL_Event event;

	Shader shader = Shader();
	shader.load_vertex_shader("./shaders/vertex.shader");
	shader.load_fragment_shader("./shaders/fragment.shader");
	shader.compile();

	while(1) {
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
			break;
		render_triangle(&shader);
		SDL_GL_SwapWindow(win);
	}

	return 0;
}
