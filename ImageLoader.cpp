#include "ImageLoader.h"
#include"IOManager.h"
#include"Error.h"
#include"picoPNG.h"


GLTexture ImageLoader::loadPNG(std::string filePath)
{
	GLTexture texture = {};
	std::vector<unsigned char> in;
	std::vector<unsigned char> out;
	unsigned long int width, height;
	if (IOManager::readFileToBuffer(filePath, in) == false) {
		fatalError("\nUnable to read file to buffer in image loader !!!");
	}
	int errorCode = decodePNG(out,width,height,&(in[0]),in.size());
	if (errorCode != 0) {
		fatalError("\nUnable to decode PNG !!!");
	}

	glGenTextures(1, &(texture.id));
	texture.width = width;
	texture.heigth = height;

	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}
