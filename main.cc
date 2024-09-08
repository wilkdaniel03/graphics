#include <stdio.h>
#include <stdlib.h>
#include "_deps/sdl2-src/include/SDL.h"
#include "glad.h"

#include "shader.cc"

#define WIDTH 1920*0.4
#define HEIGHT 1080*0.4

SDL_Window *win;
SDL_GLContext ctx;

void render_triangle(Shader *shader, unsigned int vao, unsigned int vbo, double *vert, float r, float g, float b) {
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glEnableVertexAttribArray(0);
	glBufferData(GL_ARRAY_BUFFER,sizeof(double)*6,vert,GL_STATIC_DRAW);
	glVertexAttribPointer(0,2,GL_DOUBLE,GL_FALSE,sizeof(double)*2,(void *)0);
	shader->use();
	shader->set_color(r,g,b,1.);
	glBindVertexArray(vao);
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

	unsigned int vao;
	glGenVertexArrays(1,&vao);

	unsigned vbo;
	glGenBuffers(1,&vbo);

	Shader shader = Shader();
	shader.load_vertex_shader("./shaders/vertex.shader");
	shader.load_fragment_shader("./shaders/fragment.shader");
	shader.compile();

	double vert1[] = {
		-1., -1,
		0., -1.,
		-1., 1.
	};

	double vert2[] = {
		0., 1.,
		0., -1.,
		-1., 1.
	};

	double vert3[] = {
		0., 1.,
		0., -1.,
		1., 1.
	};

	double vert4[] = {
		1., -1.,
		0., -1.,
		1, 1.
	};

	while(1) {
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
			break;
		render_triangle(&shader,vao,vbo,vert1,1.,1.,1.);
		render_triangle(&shader,vao,vbo,vert2,1.,1.,1.);
		render_triangle(&shader,vao,vbo,vert3,1.,0.2,0.);
		render_triangle(&shader,vao,vbo,vert4,1.,0.2,0.);
		SDL_GL_SwapWindow(win);
	}

	return 0;
}
