#include "Level.h"

Level::Level()
{
	LeftBorder.Position = Vector3f(0.f, 0.f, LEVER_LAYER);
	LeftBorder.Width = BORDER_WIDTH;
	LeftBorder.Height = LOGICAL_SCENE_HEIGHT;

	RightBorder.Position = Vector3f(LOGICAL_SCENE_WIDTH - BORDER_HEIGHT, 0.f, LEVER_LAYER);
	RightBorder.Width = BORDER_WIDTH;
	RightBorder.Height = LOGICAL_SCENE_HEIGHT;

	TopBorder.Position = Vector3f(0.f, LOGICAL_SCENE_HEIGHT - BORDER_HEIGHT, LEVER_LAYER);
	TopBorder.Width = LOGICAL_SCENE_WIDTH;
	TopBorder.Height = BORDER_HEIGHT;
}

bool Level::LoadLevel(const char * FilePath)
{
	this->Blocks.clear();
	assert(FilePath);

	int BlocksCount = 0;
	std::ifstream LevelDataFile;
	LevelDataFile.open(FilePath, std::ifstream::in);

	if (!LevelDataFile)
	{
		return false;
	}
	LevelDataFile >> BlocksCount;
	this->Blocks.resize(BlocksCount);
	this->BreakableBlocksCount = BlocksCount;

	for (auto & i : this->Blocks)
	{
		i.bIsAlive = true;
		i.Sprite.Width = BLOCK_WIDTH;
		i.Sprite.Height = BLOCK_HEIGHT;
		LevelDataFile >> i.Sprite.Position.X;
		LevelDataFile >> i.Sprite.Position.Y;
		i.Sprite.Position.Z = BLOCK_LAYER;
		LevelDataFile >> i.BlockType;
		i.Sprite.Color = BLOCK_COLORS[i.BlockType];
		if (i.BlockType == UNBREAKABLE_BLOCK_INDEX)
		{
			--this->BreakableBlocksCount;
		}
	}

	return true;
}

bool Level::WriteLevel(const char * FilePath)
{
	assert(FilePath);

	std::ofstream LevelDataFile;
	LevelDataFile.open(FilePath, std::ifstream::out);

	if (!LevelDataFile)
	{
		return false;
	}
	LevelDataFile << this->Blocks.size() << std::endl;

	for (auto & i : this->Blocks)
	{
		LevelDataFile << i.Sprite.Position.X << " ";
		LevelDataFile << i.Sprite.Position.Y << " ";
		LevelDataFile << i.BlockType << std::endl;
	}

	return true;
}

void Level::RenderLevel()
{
	gRenderer->Render(this->LeftBorder);
	gRenderer->Render(this->RightBorder);
	gRenderer->Render(this->TopBorder);
	for (auto & i : this->Blocks)
	{
		if (i.bIsAlive)
		{
			gRenderer->Render(i.Sprite);
		}
	}
}