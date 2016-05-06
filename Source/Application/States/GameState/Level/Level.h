#ifndef LEVEL_H
#define LEVEL_H

#include <Application\ApplicationDefinitions\ApplicationDefinitions.h>
#include <fstream>

struct Block
{
	ColoredSprite Sprite;
	int BlockType;
	bool bIsAlive = true;
};

class Level
{
public:
	inline std::vector<Block> & GetBlocks() { return this->Blocks; }
	inline unsigned int GetBreakableBlocksCount() { return this->BreakableBlocksCount; }
	bool LoadLevel(const char * FilePath);
	bool WriteLevel(const char * FilePath);

	void RenderLevel();

	Level();
	Level(const Level & Right) = delete;
	Level(Level && Right) = delete;
	Level & operator=(const Level & Right) = delete;
	Level & operator=(Level && Right) = delete;
private:
	std::vector<Block> Blocks;
	unsigned int BreakableBlocksCount;
	ColoredSprite LeftBorder;
	ColoredSprite RightBorder;
	ColoredSprite TopBorder;
};

#endif