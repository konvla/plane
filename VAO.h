#ifndef VAO_H
#define VAO_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	GLuint ID;

	VAO();

	void LinkAttrib(VBO VBO, GLuint layout, GLuint numCompon, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void UnBind();
	void Delete();
};

#endif