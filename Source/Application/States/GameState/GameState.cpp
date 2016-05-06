#include "GameState.h"

Game::Game() : GameState{ GAME_STATE::NEW_GAME }
{
	this->bPaused = false;
	this->bPauseKeyGuard = false;

	this->CurrentLevelNumber = 0;

	this->AliveBlocksCount = 0;

	//space guard
	this->bRepeatSpaceGuard = false;

	//player
	this->PlayerLifes = PLAYER_START_LIFES_COUNT;

	//Paddle
	this->PaddleSprite.Position = Vector3f(PADDLE_START_X, PADDLE_START_Y, PADDLE_LAYER);
	this->PaddleSprite.Width = PADDLE_WIDTH;
	this->PaddleSprite.Height = PADDLE_HEIGHT;
	this->PaddleX = PADDLE_START_X;
	this->PaddleSprite.Color = Vector3f(1.0f, 0.0f, 0.0f);
	this->PaddleSpeed = 0.f;

	//Ball
	this->BallX = 0.f;
	this->BallY = 0.f;
	this->BallSpeed = BALL_SPEED;
	this->BallDirection = Vector2f(1.f, 1.f);
	this->BallDirection.Normalize();
	this->BallSprite.Texture = gTextureManager->LoadTexture("BallTexture", BALL_TEXTURE_PATH);
	this->BallSprite.Width = this->BallSprite.Height = BALL_SIZE;
	this->BallSprite.Position.Z = BALL_LAYER;

	//help text
	HelpSprite.Texture = gTextureManager->LoadTexture("HelpTextTexture", HELPTEXT_TEXTURE_PATH);
	HelpSprite.TextureCoordinates.X = 34.f / 512.f;
	HelpSprite.TextureCoordinates.Y = (256.f - 172.f) / 256.f;
	HelpSprite.TextureCoordinates.Z = 491.f / 512.f;
	HelpSprite.TextureCoordinates.W = (256.f - 6.f) / 256.f;
	HelpSprite.Width = HELP_TEXT_WIDTH;
	HelpSprite.Height = HELP_TEXT_HEIGHT;
	HelpSprite.Position = Vector3f(HELP_TEXT_X, HELP_TEXT_Y, HELP_TEXT_LAYER);

	//Game over sprite
	GameOverSprite.Texture = gTextureManager->LoadTexture("GameOverTextTexture", GAMEOVERTEXT_TEXTURE_PATH);
	GameOverSprite.TextureCoordinates.Z = 217.f / 256.f;
	GameOverSprite.TextureCoordinates.W = (64.f - 37.f) / 64.f;
	GameOverSprite.Width = GAMEOVERTEXT_TEXT_WIDTH;
	GameOverSprite.Height = GAMEOVERTEXT_TEXT_HEIGHT;
	GameOverSprite.Position = Vector3f(GAMEOVERTEXT_TEXT_X, GAMEOVERTEXT_TEXT_Y, GAMEOVERTEXT_TEXT_LAYER);
}

bool Game::Render(DWORD dt)
{
	gRenderer->BeginScene();
	switch (this->GameState)
	{
	case GAME_STATE::NEW_GAME:
		gRenderer->Render(this->HelpSprite);
		break;
	case GAME_STATE::NEW_BALL:
		gRenderer->Render(BallSprite);
		CurrentLevel.RenderLevel();
		gRenderer->Render(this->PaddleSprite);
		break;
	case GAME_STATE::GAME_OVER:
		gRenderer->Render(this->GameOverSprite);
		break;
	case GAME_STATE::GAME:
		gRenderer->Render(BallSprite);
		CurrentLevel.RenderLevel();
		gRenderer->Render(this->PaddleSprite);
		break;
	default:
		return false;
	}
	gRenderer->EndScene();
	return true;
}

bool Game::Logic(DWORD dt)
{
	if (GetKeyState(0x50) & 0x80) // P key
	{
		if (this->bPauseKeyGuard)
		{
			this->bPaused = !this->bPaused;
			bPauseKeyGuard = false;
		}
	}
	else{
		bPauseKeyGuard = true;
	}
	if (!this->bPaused)
	{
		switch (this->GameState)
		{
		case GAME_STATE::NEW_GAME:
			NewGameLogic();
			break;
		case GAME_STATE::NEW_BALL:
			NewBallLogic(dt);
			break;
		case GAME_STATE::GAME_OVER:
			GameOverLogic();
			break;
		case GAME_STATE::GAME:
			GameLogic(dt);
			break;
		default:
			return false;
		}
	}
	
	return true;
}

void Game::UpdatePaddle(DWORD dt)
{
	if (GetKeyState(VK_LEFT) & 0x80)
	{
		this->PaddleSpeed -= PADDLE_ACCEL * dt;
		if (this->PaddleSpeed < -PADDLE_MAX_SPEED)
		{
			this->PaddleSpeed = -PADDLE_MAX_SPEED;
		}
	}
	else if (GetKeyState(VK_RIGHT) & 0x80)
	{
		this->PaddleSpeed += PADDLE_ACCEL * dt;
		if (this->PaddleSpeed > PADDLE_MAX_SPEED)
		{
			this->PaddleSpeed = PADDLE_MAX_SPEED;
		}
	}
	else
	{
		this->PaddleSpeed = 0.f;
	}

	this->PaddleX += this->PaddleSpeed * dt;

	if (this->PaddleX < BORDER_WIDTH)
	{
		this->PaddleX = BORDER_WIDTH;
		this->PaddleSpeed = 0.f;
	}
	if (this->PaddleX > (LOGICAL_SCENE_WIDTH - BORDER_WIDTH - PADDLE_WIDTH))
	{
		this->PaddleX = LOGICAL_SCENE_WIDTH - BORDER_WIDTH - PADDLE_WIDTH;
		this->PaddleSpeed = 0.f;
	}
	this->PaddleSprite.Position = Vector3f(this->PaddleX, PADDLE_START_Y, PADDLE_LAYER);
}

void Game::ResetPaddle()
{
	this->PaddleSprite.Position = Vector3f(PADDLE_START_X, PADDLE_START_Y, PADDLE_LAYER);
	this->PaddleX = PADDLE_START_X;
	this->PaddleSpeed = 0.f;
}

void Game::UpdateBall(DWORD dt)
{
	float newX = this->BallX + (this->BallDirection.X * this->BallSpeed);
	float newY = this->BallY + (this->BallDirection.Y * this->BallSpeed);

	//collision with borders
	//left
	if (newX < BORDER_WIDTH)
	{
		newX = BORDER_WIDTH;
		this->BallDirection.X = -this->BallDirection.X;
		RandomizeXDirection();
	}

	//right
	if (newX > (LOGICAL_SCENE_WIDTH - BORDER_WIDTH - BALL_SIZE))
	{
		newX = LOGICAL_SCENE_WIDTH - BORDER_WIDTH - BALL_SIZE;
		this->BallDirection.X = -this->BallDirection.X;
		RandomizeXDirection();
	}

	//top
	if (newY > (LOGICAL_SCENE_HEIGHT - BORDER_HEIGHT - BALL_SIZE))
	{
		newY = LOGICAL_SCENE_HEIGHT - BORDER_HEIGHT - BALL_SIZE;
		this->BallDirection.Y = -this->BallDirection.Y;
		RandomizeYDirection();
	}

	//paddle
	if ((this->BallX >= (this->PaddleX - BALL_SIZE)) && (this->BallX <= (this->PaddleX + PADDLE_WIDTH + BALL_SIZE)))
	{
		if (newY < (PADDLE_START_Y + PADDLE_HEIGHT))
		{
			if (newY > (PADDLE_START_Y + PADDLE_HEIGHT - PADDLE_MAX_ALLOWED_PENETRATION))
			{
				newY = PADDLE_START_Y + PADDLE_HEIGHT;
				this->BallDirection.Y = -this->BallDirection.Y + (PADDLE_MAX_DIRECTION_CHANGE * (this->PaddleSpeed / PADDLE_MAX_SPEED));
				this->BallDirection.Normalize();
			}
		}
	}

	//blocks
	for (auto & i : this->CurrentLevel.GetBlocks())
	{
		if (!i.bIsAlive)
		{
			continue;
		}

		//left
		if ((this->BallY >= (i.Sprite.Position.Y - BALL_SIZE)) && (this->BallY <= (i.Sprite.Position.Y + i.Sprite.Height)) && (this->BallX < i.Sprite.Position.X))
		{
			if ((newX >= i.Sprite.Position.X) && (newX <= (i.Sprite.Position.X + i.Sprite.Width)))
			{
				if (i.BlockType != UNBREAKABLE_BLOCK_INDEX)
				{
					i.bIsAlive = false;
					--this->AliveBlocksCount;
				}
				newX = i.Sprite.Position.X - BALL_SIZE;
				this->BallDirection.X = -this->BallDirection.X;
				RandomizeXDirection();
				break;
			}
		}

		//right
		if ((this->BallY >= (i.Sprite.Position.Y - BALL_SIZE)) && (this->BallY <= (i.Sprite.Position.Y + i.Sprite.Height)) && (this->BallX > (i.Sprite.Position.X + i.Sprite.Width)))
		{
			if ((newX >= (i.Sprite.Position.X)) && (newX <= (i.Sprite.Position.X + i.Sprite.Width)))
			{
				if (i.BlockType != UNBREAKABLE_BLOCK_INDEX)
				{
					i.bIsAlive = false;
					--this->AliveBlocksCount;
				}
				newX = i.Sprite.Position.X + i.Sprite.Width;
				this->BallDirection.X = -this->BallDirection.X;
				RandomizeXDirection();
				break;
			}
		}

		//top
		if ((this->BallX >= (i.Sprite.Position.X - BALL_SIZE)) && (this->BallX <= (i.Sprite.Position.X + i.Sprite.Width)) && (this->BallY > i.Sprite.Position.Y + i.Sprite.Height))
		{
			if ((newY >= (i.Sprite.Position.Y)) && (newY <= (i.Sprite.Position.Y + i.Sprite.Height)))
			{
				if (i.BlockType != UNBREAKABLE_BLOCK_INDEX)
				{
					i.bIsAlive = false;
					--this->AliveBlocksCount;
				}
				newY = i.Sprite.Position.Y + i.Sprite.Height;
				this->BallDirection.Y = -this->BallDirection.Y;
				RandomizeYDirection();
				break;
			}
		}

		//bot
		if ((this->BallX >= (i.Sprite.Position.X - BALL_SIZE)) && (this->BallX <= (i.Sprite.Position.X + i.Sprite.Width)) && (this->BallY < i.Sprite.Position.Y))
		{
			if ((newY >= (i.Sprite.Position.Y)) && (newY <= (i.Sprite.Position.Y + i.Sprite.Height)))
			{
				if (i.BlockType != UNBREAKABLE_BLOCK_INDEX)
				{
					i.bIsAlive = false;
					--this->AliveBlocksCount;
				}
				newY = i.Sprite.Position.Y - BALL_SIZE;
				this->BallDirection.Y = -this->BallDirection.Y;
				RandomizeYDirection();
				break;
			}
		}
	}

	this->BallX = newX;
	this->BallY = newY;
	this->BallSprite.Position.X = this->BallX;
	this->BallSprite.Position.Y = this->BallY;

	if (this->BallY < 0.f)
	{
		if (!(--this->PlayerLifes))
		{
			this->GameState = GAME_STATE::GAME_OVER;
		}
		else
		{
			this->GameState = GAME_STATE::NEW_BALL;
		}
	}
}

void Game::NewGameLogic()
{
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		if (this->bRepeatSpaceGuard)
		{
			this->GameState = GAME_STATE::NEW_BALL;
			this->bRepeatSpaceGuard = false;
			ResetPaddle();
			this->PlayerLifes = PLAYER_START_LIFES_COUNT;
			this->CurrentLevelNumber = 0;
			this->CurrentLevel.LoadLevel(LEVELS_FILE_PATHS[0]);
			this->AliveBlocksCount = this->CurrentLevel.GetBreakableBlocksCount();
		}
	}
	else
	{
		this->bRepeatSpaceGuard = true;
	}
}

void Game::NewBallLogic(DWORD dt)
{
	UpdatePaddle(dt);
	this->BallX = this->PaddleX + (PADDLE_WIDTH / 2.f) - (BALL_SIZE / 2.f);
	this->BallY = PADDLE_START_Y + PADDLE_HEIGHT;
	this->BallSprite.Position.X = this->BallX;
	this->BallSprite.Position.Y = this->BallY;

	if (GetKeyState(VK_SPACE) & 0x80)
	{
		if (this->bRepeatSpaceGuard)
		{
			this->GameState = GAME_STATE::GAME;
			this->BallSpeed = BALL_SPEED;
			this->BallDirection = Vector2f(1.f, 1.f);
			this->BallDirection.Normalize();
		}
	}
	else
	{
		this->bRepeatSpaceGuard = true;
	}
}

void Game::GameLogic(DWORD dt)
{
	UpdatePaddle(dt);
	UpdateBall(dt);
	
	if (!this->AliveBlocksCount)
	{
		this->GameState = GAME_STATE::NEW_BALL;
		++this->CurrentLevelNumber;
		if (this->CurrentLevelNumber < LEVELS_COUNT)
		{
			this->CurrentLevel.LoadLevel(LEVELS_FILE_PATHS[this->CurrentLevelNumber]);
		}
		else
		{
			this->CurrentLevel.LoadLevel(LEVELS_FILE_PATHS[LEVELS_COUNT - 1]);
		}
		this->AliveBlocksCount = this->CurrentLevel.GetBreakableBlocksCount();
	}
	if (GetKeyState(0x52) & 0x80) //R key
	{
		this->GameState = GAME_STATE::NEW_BALL;
		this->bRepeatSpaceGuard = false;
		ResetPaddle();
		this->PlayerLifes = PLAYER_START_LIFES_COUNT;
		this->CurrentLevelNumber = 0;
		this->CurrentLevel.LoadLevel(LEVELS_FILE_PATHS[0]);
		this->AliveBlocksCount = this->CurrentLevel.GetBreakableBlocksCount();
	}
}

void Game::GameOverLogic()
{
	if (GetKeyState(VK_SPACE) & 0x80)
	{
		this->bRepeatSpaceGuard = false;
		this->GameState = GAME_STATE::NEW_BALL;
		ResetPaddle();
		this->PlayerLifes = PLAYER_START_LIFES_COUNT;
		this->CurrentLevelNumber = 0;
		this->CurrentLevel.LoadLevel(LEVELS_FILE_PATHS[0]);
	}
}

void Game::RandomizeXDirection()
{
	this->BallDirection.X += static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.2)) - 0.1f;
	this->BallDirection.Normalize();
}

void Game::RandomizeYDirection()
{
	this->BallDirection.Y += static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.2)) - 0.1f;
	this->BallDirection.Normalize();
}