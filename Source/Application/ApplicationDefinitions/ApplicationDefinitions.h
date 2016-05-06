#ifndef APPLICATION_DEFINITIONS_H
#define APPLICATION_DEFINITIONS_H

#include <Helpers\MainLoop\MainLoop.h>

//Scene
const int LOGICAL_SCENE_WIDTH = 320;
const int LOGICAL_SCENE_HEIGHT = 240;

//window
const int DEFAULT_WINDOW_WIDTH = 800;
const int DEFAULT_WINDOW_HEIGHT = 600;

//Log
const char * const LOG_FILENAME = "Log.txt";

//Helpers
extern HWND gWindowHandle;
extern WindowHelper * gWndHelper;
extern OpengGLHelper * gOpnGLHelper;
extern OrthoCamera * gCamera;
extern OpenGLRenderer * gRenderer;
extern OpenGLTextureManager * gTextureManager;

//forward declaration
class Game;
extern Game * gGame;

//msg process func
LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);

//game state enum
enum class GAME_STATE { NEW_GAME, NEW_BALL, GAME, GAME_OVER};

//z values for layers
//less value == closer to cam
const float LEVER_LAYER = -5.f;

//Borders
const float BORDER_WIDTH = 5.f;
const float BORDER_HEIGHT = 5.f;

//Ball
const float BALL_SPEED = 3.0f;
const float BALL_SIZE = 5.f;
const char * const BALL_TEXTURE_PATH = "Data/Textures/ball.tga";
const float BALL_LAYER = -6.f;

//Paddle
const float PADDLE_ACCEL = 0.01f;
const float PADDLE_MAX_SPEED = 0.3f;
const float PADDLE_WIDTH = 40.f;
const float PADDLE_HEIGHT = 15.f;
const float PADDLE_START_X = LOGICAL_SCENE_WIDTH / 2.f - PADDLE_WIDTH / 2.f;
const float PADDLE_START_Y = 20.f;
const float PADDLE_LAYER = -4.f;
const float PADDLE_MAX_ALLOWED_PENETRATION = BALL_SPEED * 2;
const float PADDLE_MAX_DIRECTION_CHANGE = 0.3f;

//Help Text
const char * const HELPTEXT_TEXTURE_PATH = "Data/Textures/text.tga";
const float HELP_TEXT_WIDTH = 320.f;
const float HELP_TEXT_HEIGHT = 117.f;
const float HELP_TEXT_X = 0.f;
const float HELP_TEXT_Y = 100.f;
const float HELP_TEXT_LAYER = -2.f;

//Gameover text
const char * const GAMEOVERTEXT_TEXTURE_PATH = "Data/Textures/gameover.tga";
const float GAMEOVERTEXT_TEXT_WIDTH = 220.f;
const float GAMEOVERTEXT_TEXT_HEIGHT = 30.f;
const float GAMEOVERTEXT_TEXT_X = 50.f;
const float GAMEOVERTEXT_TEXT_Y = 100.f;
const float GAMEOVERTEXT_TEXT_LAYER = -2.f;

//Player 
const int PLAYER_START_LIFES_COUNT = 3;

//Levels
const char * const LEVELS_FILE_PATHS[] =
{
	"Data/Levels/level1.dat",
	"Data/Levels/level2.dat",
	"Data/Levels/level3.dat",
};
const int LEVELS_COUNT = 3;

//Blocks
const float BLOCK_WIDTH = 35.f;
const float BLOCK_HEIGHT = 15.f;
const float BLOCK_LAYER = -4.f;

const Vector3f BLOCK_COLORS[] =
{
	Vector3f(0.f, 1.f, 0.f),
	Vector3f(0.f, 0.f, 1.f),
	Vector3f(0.f, 1.f, 1.f),
	Vector3f(1.f, 1.f, 0.f),
	Vector3f(1.f, 0.f, 1.f),
	Vector3f(1.f, 1.f, 1.f),
};
const int UNBREAKABLE_BLOCK_INDEX = 5;

#endif