#include <stdio.h>
#include <stdlib.h>
#include "_deps/sdl2-src/include/SDL.h"
#include "glad.h"

#define WIDTH 1920*0.3
#define HEIGHT 1080*0.4

SDL_Window *win;
SDL_GLContext ctx;

const double TRIANGLE_VERTICES[3][2] = {
	{ -0.5, -0.5 },
	{ 0.5, -0.5 },
	{ 0., 0.5 }
};

const char *PTR;
const char *PTR2;
int success;

void render_triangle() {
	unsigned int vao;
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	unsigned int vbo;
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(TRIANGLE_VERTICES),TRIANGLE_VERTICES,GL_STATIC_DRAW);
	glVertexAttribPointer(0,2,GL_DOUBLE,GL_FALSE,2*sizeof(double),(void *)0);
	glEnableVertexAttribArray(0);
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader,1,&PTR,0);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader,GL_COMPILE_STATUS,&success);
	if(!success)
		fprintf(stderr,"Failed to compile vertex shader\n");
	unsigned int fragment_shader= glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader,1,&PTR2,0);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader,GL_COMPILE_STATUS,&success);
	if(!success)
		fprintf(stderr,"Failed to compile fragment shader\n");
	unsigned int shader_program = glCreateProgram();
	glAttachShader(shader_program,vertex_shader);
	glAttachShader(shader_program,fragment_shader);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program,GL_LINK_STATUS,&success);
	if(!success)
		fprintf(stderr,"Failed to link program\n");
	glUseProgram(shader_program);
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

	PTR = malloc(sizeof(char) * 256);
	char *copy = (char *) PTR;
	FILE *f = fopen("./vertex.shader","r");
	char c;
	int i = 0;
	while((c = fgetc(f)) != EOF && i < 256) {
		copy[i] = c;
		i++;
	}

	PTR2 = malloc(sizeof(char) * 256);
	copy = (char *) PTR2;
	f = fopen("./fragment.shader","r");
	i = 0;
	while((c = fgetc(f)) != EOF && i < 256) {
		copy[i] = c;
		i++;
	}

	while(1) {
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
			break;
		glClearColor(0.3,1.,0.4,1.);
		glClear(GL_COLOR_BUFFER_BIT);
		render_triangle();
		SDL_GL_SwapWindow(win);
	}

	return 0;
}
