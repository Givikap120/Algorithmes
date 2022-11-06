#include "Labyrinth.h"

float randFloat() 
{
	return (float)rand() / RAND_MAX;
}

void Labyrinth::createDeadend(int x, int y)
{
	Cell& cell = table[y][x];
	cell.addWallBot();
	cell.addWallTop();
	cell.addWallLeft();
	cell.addWallRight();
}

void addVerticalWallsFirstLine(std::vector<Cell>::iterator cellPtr, std::vector<int>::iterator MTptr, int sizeX, float wallChance, int& MTcount)
{
	for (size_t i = 0; i < sizeX - 1; ++i)
	{
		*MTptr = MTcount;
		if (randFloat() <= wallChance) {
			cellPtr->right->left = nullptr;
			cellPtr->right = nullptr;
			++MTcount;
		}
		++cellPtr;
		++MTptr;
	}
	*MTptr = MTcount;
}

void addHorizontalWalls(std::vector<Cell>::iterator cellPtr, std::vector<int>::iterator MTptr, int sizeX, float wallChance)
{
	bool haveExit = false;
	int currentMT = -1;
	for (size_t i = 0; i < sizeX - 1; ++i)
	{
		if (*MTptr != currentMT) {
			haveExit = false;
			currentMT = *MTptr;
		}

		if (cellPtr->right or haveExit) {
			if (randFloat() <= wallChance) {
				cellPtr->bot->top = nullptr;
				cellPtr->bot = nullptr;
			}
		}
		else {
			haveExit = true;
		}

		++cellPtr;
		++MTptr;
	}
	
}

void resetMT(std::vector<Cell>::iterator cellPtr, std::vector<int>::iterator MTptr, int sizeX, float wallChance, int& MTcount)
{
	for (size_t i = 0; i < sizeX; ++i)
	{
		if (!(cellPtr->top)) {
			*MTptr = MTcount;
			++MTcount;
		}
		++cellPtr;
		++MTptr;
	}
}

void addVerticalWalls(std::vector<Cell>::iterator cellPtr, std::vector<int>::iterator MTptrNext, int sizeX, float wallChance, int& MTcount)
{
	auto MTptrCurrent = MTptrNext;
	++MTptrNext;
	for (size_t i = 0; i < sizeX - 1; ++i)
	{
		if (*MTptrNext	==	*MTptrCurrent) {
			cellPtr->right->left = nullptr;
			cellPtr->right = nullptr;
		}
		else if (randFloat() <= wallChance) {
			cellPtr->right->left = nullptr;
			cellPtr->right = nullptr;
		}
		else {
			*MTptrNext = *MTptrCurrent;
		}
		++cellPtr;
		++MTptrNext;
		++MTptrCurrent;
	}

}

void addVerticalWallsLastLine(std::vector<Cell>::iterator cellPtr, std::vector<int>::iterator MTptrNext, int sizeX, float wallChance, int& MTcount)
{
	auto MTptrCurrent = MTptrNext;
	++MTptrNext;
	for (size_t i = 0; i < sizeX - 1; ++i)
	{
		if (*MTptrNext == *MTptrCurrent and randFloat() <= wallChance) {
			cellPtr->right->left = nullptr;
			cellPtr->right = nullptr;
		}
		++cellPtr;
		++MTptrNext;
		++MTptrCurrent;
	}
}

void generateFirstLine(std::vector<Cell>& firstLine, std::vector<int>& MTline, int& MTcount, float wallChance)
{
	addVerticalWallsFirstLine(firstLine.begin(), MTline.begin(), firstLine.size(), wallChance, MTcount);
	addHorizontalWalls(firstLine.begin(), MTline.begin(), firstLine.size(), wallChance);
}

void generateLine(std::vector<Cell>& tableLine, std::vector<int>& MTline, int& MTcount, float wallChance)
{
	resetMT(tableLine.begin(), MTline.begin(), tableLine.size(), wallChance, MTcount);
	addVerticalWalls(tableLine.begin(), MTline.begin(), tableLine.size(), wallChance, MTcount);
	addHorizontalWalls(tableLine.begin(), MTline.begin(), tableLine.size(), wallChance);
}

void generateLastLine(std::vector<Cell>& lastLine, std::vector<int>& MTline, int& MTcount, float wallChance)
{
	resetMT(lastLine.begin(), MTline.begin(), lastLine.size(), wallChance, MTcount);
	addVerticalWallsLastLine(lastLine.begin(), MTline.begin(), lastLine.size(), wallChance, MTcount);
}

std::vector<std::vector<Cell>>::iterator;

void Labyrinth::generate(float wallChance, float deadendChance) 
{
	int MT_count = 0;
	std::vector<std::vector<int>> MT(sizeY, std::vector<int>(sizeX, -1));
	
	generateFirstLine(table[0], MT[0], MT_count, wallChance);


	for (size_t i = 1; i < sizeY - 1; ++i)
	{
		std::copy(MT[i - 1].begin(), MT[i - 1].end(), MT[i].begin());
		generateLine(table[i], MT[i], MT_count, wallChance);
	}

	std::copy(MT[sizeY - 2].begin(), MT[sizeY - 2].end(), MT[sizeY - 1].begin());
	generateLastLine(table[sizeY - 1], MT[sizeY - 1], MT_count, wallChance);

	MT_test = MT;
	if (randFloat() <= deadendChance) createDeadend(sizeX - 1, sizeY - 1);
}