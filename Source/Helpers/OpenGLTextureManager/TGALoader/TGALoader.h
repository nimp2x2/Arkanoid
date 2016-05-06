#ifndef TGA_LOADER_H
#define TGA_LOADER_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl\gl.h>
#include <fstream>
#include <cassert>

class TgaTexture
{
public:
	GLubyte	* ImageData;
	GLuint Bpp;
	GLuint Width;
	GLuint Height;
	GLuint Type;

	bool LoadTGA(const char * FilePath);

	TgaTexture();
	~TgaTexture();
	TgaTexture(const TgaTexture & Right) = delete;
	TgaTexture(TgaTexture && Right);
	TgaTexture & operator=(const TgaTexture & Right) = delete;
	TgaTexture & operator=(TgaTexture && Right);
private:
	bool LoadUncompressedTGA(std::ifstream * File);
};

#endif