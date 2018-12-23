#pragma once
#include<glew.h>
#include<vector>
#include"GLTexture.h"


class Sprite
{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float widht, float height,std::string texturePath);
		void draw();

	private:
		float _x, _y, _widht, _height;
		GLuint _vboID;
		GLTexture _texture;

};



