#ifndef OPENGL_TEXTURE_MANAGER_H
#define OPENGL_TEXTURE_MANAGER_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl\gl.h>
#include <unordered_map>

class OpenGLTextureManager
{
public:
	GLuint GetDefaultTexture();
	GLuint GetTexture(const char * TextureName) const;
	GLuint LoadTexture(const char * TextureName, const char * TexturePath);
	bool UnloadTexture(const char * TextureName);
	void UnloadAll();

	OpenGLTextureManager();
	OpenGLTextureManager(const OpenGLTextureManager & Right) = delete;
	OpenGLTextureManager(OpenGLTextureManager && Right) = delete;
	OpenGLTextureManager & operator=(const OpenGLTextureManager & Right) = delete;
	OpenGLTextureManager & operator=(OpenGLTextureManager && Right) = delete;
	~OpenGLTextureManager();
private:
	std::unordered_map<std::string, GLuint> Textures;
	GLuint DefaultTexture;
};

#endif