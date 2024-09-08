#include <stdio.h>
#include <stdlib.h>
#include "glad.h"

class Shader {
	unsigned int vertex_shader;
	unsigned int fragment_shader;
	unsigned int program;

	void compile_shader(unsigned int shader) {
		glCompileShader(shader);
		int success;
		glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
		if(!success)
			fprintf(stderr,"Failed to compile vertex shader\n");
	}

public:
	Shader() {
		this->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		this->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		this->program = glCreateProgram();
	}

	void load_vertex_shader(const char *path) {
		const char *source = (char *) malloc(sizeof(char) * 256);
		char *ptr = (char *) source;
		FILE *fptr = fopen(path,"r");
		char c = fgetc(fptr);
		int i = 0;
		while(c != EOF && i < 256) {
			ptr[i] = c;
			c = fgetc(fptr);
			i++;
		}
		fclose(fptr);
		glShaderSource(this->vertex_shader,1,&source,0);
	}

	void load_fragment_shader(const char *path) {
		const char *source = (char *) malloc(sizeof(char) * 256);
		char *ptr = (char *) source;
		FILE *fptr = fopen(path,"r");
		char c = fgetc(fptr);
		int i = 0;
		while(c != EOF && i < 256) {
			ptr[i] = c;
			c = fgetc(fptr);
			i++;
		}
		fclose(fptr);
		glShaderSource(this->fragment_shader,1,&source,0);
	}

	void compile() {
		this->compile_shader(this->vertex_shader);
		this->compile_shader(this->fragment_shader);
		glAttachShader(this->program,this->vertex_shader);
		glAttachShader(this->program,this->fragment_shader);
		glLinkProgram(this->program);
		int success;
		glGetProgramiv(this->program,GL_LINK_STATUS,&success);
		if(!success)
			fprintf(stderr,"Failed to link program\n");
	}

	void use() {
		glUseProgram(this->program);
	}
};
