#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <Application\States\GameState\Level\Level.h>

class Game 
{
public:
	bool Render(DWORD dt);
	bool Logic(DWORD dt);
	Game();
private:
	//Game state
	GAME_STATE GameState;
	bool bPaused;
	bool bPauseKeyGuard;

	//Level
	Level CurrentLevel;
	int CurrentLevelNumber;

	//Blocks
	int AliveBlocksCount;

	//Player
	int PlayerLifes;

	//Ball
	float BallX;
	float BallY;
	float BallSpeed;
	Vector2f BallDirection;
	TexturedColoredSprite BallSprite;
	void UpdateBall(DWORD dt);
	void RandomizeXDirection();
	void RandomizeYDirection();

	//Paddle
	float PaddleX;
	float PaddleSpeed;
	ColoredSprite PaddleSprite;
	void ResetPaddle();
	void UpdatePaddle(DWORD dt);

	//New game
	TexturedColoredSprite HelpSprite;
	void NewGameLogic();

	//New Ball
	void NewBallLogic(DWORD dt);
	bool bRepeatSpaceGuard;

	//Game
	void GameLogic(DWORD dt);

	//GameOver
	void GameOverLogic();
	TexturedColoredSprite GameOverSprite;
};

#endif