#include "TGALoader.h"

struct TGAHeader
{
	GLubyte Header[12];
};

struct TGA
{
	GLubyte		header[6];
	GLuint		bytesPerPixel;
	GLuint		imageSize;
	GLuint		temp;
	GLuint		type;
	GLuint		Height;
	GLuint		Width;
	GLuint		Bpp;
};

const GLubyte uTGAcompare[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

TgaTexture::TgaTexture() : ImageData{ nullptr }, Bpp{ 0 }, Width{ 0 }, Height{ 0 }, Type{ 0 }
{
}

TgaTexture::~TgaTexture()
{
	if (this->ImageData)
	{
		delete[] this->ImageData;
	}
}

TgaTexture::TgaTexture(TgaTexture && Right) : ImageData{ Right.ImageData }, Bpp{ Right.Bpp }, Width{ Right.Width }, Height{ Right.Height }, Type{ Right.Type }
{
	Right.ImageData = nullptr;
}

TgaTexture & TgaTexture::operator=(TgaTexture && Right)
{
	if (this == &Right)
	{
		return *this;
	}
	this->ImageData = Right.ImageData;
	this->Bpp = Right.Bpp;
	this->Width = Right.Width;
	this->Height = Right.Height;
	this->Type = Right.Type;
	Right.ImageData = nullptr;
	return *this;
}

bool TgaTexture::LoadTGA(const char * FilePath)
{
	assert(FilePath);

	std::ifstream TGAFile;
	TGAFile.open(FilePath, std::ifstream::in | std::ifstream::binary);

	if (!TGAFile.is_open())
	{
		return false;
	}
	
	TGAHeader TGAHeader;
	TGAFile.read((char*)&TGAHeader, sizeof(TGAHeader));

	if (memcmp(uTGAcompare, &TGAHeader, sizeof(TGAHeader)) == 0)
	{
		return this->LoadUncompressedTGA(&TGAFile);
	}
	else
	{
		return false;
	}
}

bool TgaTexture::LoadUncompressedTGA(std::ifstream * File)
{
	assert(File);
	assert(File->good());

	TGA TGAImageData;
	File->read((char*)&TGAImageData.header, sizeof(TGAImageData.header));

	this->Width = TGAImageData.header[1] * 256 + TGAImageData.header[0];
	this->Height = TGAImageData.header[3] * 256 + TGAImageData.header[2];
	this->Bpp = TGAImageData.header[4];
	TGAImageData.Width = this->Width;					
	TGAImageData.Height = this->Height;	
	TGAImageData.Bpp = this->Bpp;

	if ((this->Width <= 0) || (this->Height <= 0) || ((this->Bpp != 24) && (this->Bpp != 32)))
	{
		return false;
	}

	if (this->Bpp == 24)
	{
		this->Type = GL_RGB;
	}		
	else
	{
		this->Type = GL_RGBA;
	}

	TGAImageData.bytesPerPixel = (TGAImageData.Bpp / 8);
	TGAImageData.imageSize = (TGAImageData.bytesPerPixel * TGAImageData.Width * TGAImageData.Height);
	this->ImageData = new GLubyte[TGAImageData.imageSize];

	if (!this->ImageData)
	{
		return false;
	}

	File->read((char*)this->ImageData, TGAImageData.imageSize);

	for (GLuint cswap = 0; cswap < (int)TGAImageData.imageSize; cswap += TGAImageData.bytesPerPixel)
	{
		this->ImageData[cswap] ^= this->ImageData[cswap + 2] ^= this->ImageData[cswap] ^= this->ImageData[cswap + 2];
	}
	return true;
}