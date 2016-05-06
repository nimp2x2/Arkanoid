#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer(HDC _DeviceContext, GLuint _DefaultTexture) : CurrentTexture{ _DefaultTexture }, DeviceContext{ _DeviceContext }, DefaultTexture{ _DefaultTexture }
{
	assert(_DeviceContext);
	assert(_DefaultTexture);
}

OpenGLRenderer::~OpenGLRenderer()
{
}

void OpenGLRenderer::BeginScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->CurrentPrimitive = PrimitiveType::NONE;
	this->CurrentTexture = this->DefaultTexture;
	glDisable(GL_TEXTURE_2D);
}

void OpenGLRenderer::EndScene()
{
	if (this->CurrentPrimitive != PrimitiveType::NONE)
	{
		glEnd();
	}
	SwapBuffers(this->DeviceContext);
}

void OpenGLRenderer::Render(const Line & _Line)
{
	if (this->CurrentPrimitive != PrimitiveType::LINE)
	{
		if (this->CurrentPrimitive != PrimitiveType::NONE)
		{
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_LINES);
		this->CurrentPrimitive = PrimitiveType::LINE;
	}
	glColor3f(_Line.Color.X, _Line.Color.Y, _Line.Color.Z);
	glVertex3f(_Line.Point1.X, _Line.Point1.Y, _Line.Point1.Z);
	glVertex3f(_Line.Point2.X, _Line.Point2.Y, _Line.Point2.Z);
}

void OpenGLRenderer::Render(const ColoredSprite & _ColoredSprite)
{
	if (this->CurrentPrimitive != PrimitiveType::COLORED_SPRITE)
	{
		if (this->CurrentPrimitive != PrimitiveType::NONE)
		{
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		this->CurrentPrimitive = PrimitiveType::COLORED_SPRITE;
	}
	glColor3f(_ColoredSprite.Color.X, _ColoredSprite.Color.Y, _ColoredSprite.Color.Z);
	glVertex3f(_ColoredSprite.Position.X, _ColoredSprite.Position.Y, _ColoredSprite.Position.Z);
	glVertex3f(_ColoredSprite.Position.X + _ColoredSprite.Width, _ColoredSprite.Position.Y, _ColoredSprite.Position.Z);
	glVertex3f(_ColoredSprite.Position.X + _ColoredSprite.Width, _ColoredSprite.Position.Y + _ColoredSprite.Height, _ColoredSprite.Position.Z);
	glVertex3f(_ColoredSprite.Position.X, _ColoredSprite.Position.Y + _ColoredSprite.Height, _ColoredSprite.Position.Z);
}

void OpenGLRenderer::Render(const TexturedColoredSprite & _TexturedColoredSprite)
{
	if (this->CurrentPrimitive != PrimitiveType::TEXTURED_COLORED_SPRITE)
	{
		if (this->CurrentPrimitive != PrimitiveType::NONE)
		{
			glEnd();
		}
		glEnable(GL_TEXTURE_2D);
		this->CurrentTexture = _TexturedColoredSprite.Texture ? _TexturedColoredSprite.Texture : this->DefaultTexture;
		glBindTexture(GL_TEXTURE_2D, this->CurrentTexture);
		glBegin(GL_QUADS);
		this->CurrentPrimitive = PrimitiveType::TEXTURED_COLORED_SPRITE;
	}
	else 
	{
		if (this->CurrentTexture != _TexturedColoredSprite.Texture)
		{
			glEnd();
			this->CurrentTexture = _TexturedColoredSprite.Texture ? _TexturedColoredSprite.Texture : this->DefaultTexture;
			glBindTexture(GL_TEXTURE_2D, this->CurrentTexture);
			glBegin(GL_QUADS);
		}
	}

	glColor3f(_TexturedColoredSprite.Color.X, _TexturedColoredSprite.Color.Y, _TexturedColoredSprite.Color.Z);

	glTexCoord2f(_TexturedColoredSprite.TextureCoordinates.X, _TexturedColoredSprite.TextureCoordinates.Y);
	glVertex3f(_TexturedColoredSprite.Position.X, _TexturedColoredSprite.Position.Y, _TexturedColoredSprite.Position.Z);
	/*
	X = x0
	Y = y0
	Z = x1
	W = y1
	*/
	
	glTexCoord2f(_TexturedColoredSprite.TextureCoordinates.Z, _TexturedColoredSprite.TextureCoordinates.Y);
	glVertex3f(_TexturedColoredSprite.Position.X + _TexturedColoredSprite.Width, _TexturedColoredSprite.Position.Y, _TexturedColoredSprite.Position.Z);
	
	glTexCoord2f(_TexturedColoredSprite.TextureCoordinates.Z, _TexturedColoredSprite.TextureCoordinates.W);
	glVertex3f(_TexturedColoredSprite.Position.X + _TexturedColoredSprite.Width, _TexturedColoredSprite.Position.Y + _TexturedColoredSprite.Height, _TexturedColoredSprite.Position.Z);

	glTexCoord2f(_TexturedColoredSprite.TextureCoordinates.X, _TexturedColoredSprite.TextureCoordinates.W);
	glVertex3f(_TexturedColoredSprite.Position.X, _TexturedColoredSprite.Position.Y + _TexturedColoredSprite.Height, _TexturedColoredSprite.Position.Z);
}