#include <cstddef>
#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"




Sprite::Sprite()
{
	_vboID = 0;
}


Sprite::~Sprite()
{
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float widht, float height,std::string texturPath)
{
	_x = x;
	_y = y;
	_widht = widht;
	_height = height;

	_texture = ResourceManager::getTexture(texturPath);

	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}

	vertex VertexData[6];
	VertexData[0].position.x = x + widht;
	VertexData[0].position.y = y + height;
	VertexData[0].setUV(1.0f, 1.0f);

	VertexData[1].position.x = x;
	VertexData[1].position.y = y + height;
	VertexData[1].setUV(0.0f, 1.0f);

	VertexData[2].position.x = x;
	VertexData[2].position.y = y;
	VertexData[2].setUV(0.0f, 0.0f);


	VertexData[3].position.x = x ;
	VertexData[3].position.y = y ;
	VertexData[3].setUV(0.0f, 0.0f);


	VertexData[4].position.x = x + widht;
	VertexData[4].position.y = y ;
	VertexData[4].setUV(1.0f, 0.0f);


	VertexData[5].position.x = x + widht;
	VertexData[5].position.y = y + height;
	VertexData[5].setUV(1.0f, 1.0f);


	for (int i = 0; i < 6; i++) {
		VertexData[i].color.r = 255;
		VertexData[i].color.g = 0;
		VertexData[i].color.b = 255;
		VertexData[i].color.a = 255;
	}

	
	VertexData[1].color.r = 0;
	VertexData[1].color.g = 0;
	VertexData[1].color.b = 255;
	VertexData[1].color.a = 255;

	VertexData[4].color.r = 255;
	VertexData[4].color.g = 0;
	VertexData[4].color.b = 0;
	VertexData[4].color.a = 255;

	VertexData[2].color.r = 0;
	VertexData[2].color.g = 255;
	VertexData[2].color.b = 0;
	VertexData[2].color.a = 255;

	VertexData[3].color.r = 0;
	VertexData[3].color.g = 255;
	VertexData[3].color.b = 0;
	VertexData[3].color.a = 255;

	VertexData[5].color.r = 255;
	VertexData[5].color.g = 100;
	VertexData[5].color.b = 255;
	VertexData[5].color.a = 255;

	VertexData[0].color.r = 255;
	VertexData[0].color.g = 100;
	VertexData[0].color.b = 255;
	VertexData[0].color.a = 255;

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(VertexData),VertexData,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, _texture.id);
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
