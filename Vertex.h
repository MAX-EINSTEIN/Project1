#pragma once
#include <glew.h>

struct Position
{
	GLfloat x;
	GLfloat y;
};
struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};
struct UV
{
	float u;
	float v;
};

struct vertex
{
	Position position;
	Color color;
	UV uv;

	void setUV(float u,float v){
		uv.u = u;
		uv.v = v;
	}
};