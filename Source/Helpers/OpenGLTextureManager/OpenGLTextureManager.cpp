#include "OpenGLTextureManager.h"
#include <Helpers\OpenGLTextureManager\TGALoader\TGALoader.h>

OpenGLTextureManager::OpenGLTextureManager() : DefaultTexture{ 0 }, Textures{}
{
	this->Textures.clear();
}

OpenGLTextureManager::~OpenGLTextureManager()
{
	this->UnloadAll();
	if (!this->DefaultTexture)
	{
		glDeleteTextures(1, &this->DefaultTexture);
	}
}

GLuint OpenGLTextureManager::GetTexture(const char * TextureName) const
{
	assert(TextureName);

	auto Result = this->Textures.find(TextureName);
	if (Result == this->Textures.end())
	{
		return Result->second;
	}
	else
	{
		return 0;
	}
}

GLuint OpenGLTextureManager::LoadTexture(const char * TextureName, const char * TexturePath)
{
	assert(TextureName);
	assert(TexturePath);

	auto Result = this->Textures.find(TextureName);
	if (Result == this->Textures.end())
	{
		TgaTexture TGATexture;
		if (TGATexture.LoadTGA(TexturePath))
		{
			GLuint Texture;
			glGenTextures(1, &Texture);
			glBindTexture(GL_TEXTURE_2D, Texture);
			glTexImage2D(GL_TEXTURE_2D, 0, TGATexture.Bpp / 8, TGATexture.Width, TGATexture.Height, 0, TGATexture.Type, GL_UNSIGNED_BYTE, TGATexture.ImageData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			this->Textures.insert({ std::string(TextureName), Texture });
			return Texture;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return Result->second;
	}
}

bool OpenGLTextureManager::UnloadTexture(const char * TextureName)
{
	assert(TextureName);

	auto Result = this->Textures.find(TextureName);
	if (Result == this->Textures.end())
	{
		return false;
	}
	else
	{
		glDeleteTextures(1, &Result->second);
		this->Textures.erase(Result);
		return true;
	}
}

void OpenGLTextureManager::UnloadAll()
{
	glBindTexture(GL_TEXTURE_2D, this->GetDefaultTexture());
	for (auto & i : this->Textures)
	{
		glDeleteTextures(1, &i.second);
	}
	this->Textures.clear();
}

GLuint OpenGLTextureManager::GetDefaultTexture()
{
	if (!this->DefaultTexture) 
	{
		glGenTextures(1, &this->DefaultTexture);
		const float Pixels[] = 
		{
			0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
		};
		glBindTexture(GL_TEXTURE_2D, this->DefaultTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, Pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	return this->DefaultTexture;
}