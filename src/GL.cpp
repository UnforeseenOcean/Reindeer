#include <iostream>
#include <assert.h>
#include "GL.hpp"

bool gluLinkProgram(GLuint program)
{
	glLinkProgram(program);
	
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if(!linked)
    {
		int log_length, chars_written;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

		char *log = (char *)malloc(log_length);

		glGetProgramInfoLog(program, log_length, &chars_written, log);

		std::cout << "Failed to link program: \n" << log;

		free(log);
		
		throw "Unable to link program";
		
		return false;
    }
	
	return true;
}

void gluRaiseErrors()
{
	GLenum gl_error = glGetError();

	if(gl_error)
	{
		std::cout << "glGetError returned " << gl_error << "\n";
		assert(0);
	}
}

bool gluCompileShader(GLuint program, GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, 0);

    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
		int log_length, chars_written;
		
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

		char *log = (char *)malloc(log_length);

		glGetShaderInfoLog(shader, log_length, &chars_written, log);

		std::cout << "Failed to compile shader: \n" << log;
		
		free(log);

		throw "Unable to compile shader";

		return false;
    }
	
	glAttachShader(program, shader);
	glDeleteShader(shader);
	
	return true;
}
