#include "InitState.h"
#include <fstream>

bool InitApp()
{
	//logger
	std::ofstream * File = new std::ofstream(LOG_FILENAME, std::ofstream::out);
	Logger::Init(File, true);

	//window
	gWndHelper = new WindowHelper(L"ArkanoidWindowClass", MsgProc);
	if (!(gWindowHandle = gWndHelper->CreateWnd(L"Arkanoid", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT)))
	{
		return false;
	}
	ShowWindow(gWindowHandle, SW_SHOW);
	SetFocus(gWindowHandle);

	//open gl
	gOpnGLHelper = new OpengGLHelper;
	if (!gOpnGLHelper->Init(gWindowHandle))
	{
		return 0;
	}

	//Camera
	gCamera = new OrthoCamera(LOGICAL_SCENE_WIDTH, LOGICAL_SCENE_HEIGHT);
	gCamera->ApplyTransformations(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

	gTextureManager = new OpenGLTextureManager;
	const GLuint DefaultTexture = gTextureManager->GetDefaultTexture();
	if (!DefaultTexture)
	{
		LOG("WARNING FAILED to create default texture");
	}

	gRenderer = new OpenGLRenderer(gOpnGLHelper->GetDeviceContext(), DefaultTexture);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_2D);

	gGame = new Game();

	return true;
}