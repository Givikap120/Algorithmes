#include "Labyrinth.h"
#include <fstream>
#include <iostream>
#include <sstream>

bool isNatural(const std::string& str)
{
	if (str[0] == '0') return false;
	for (auto i = str.begin(); i != str.end(); ++i)
	{
		if (!std::isdigit(*i)) return false;
	}
	return true;
}

bool getBit(int n, int bit_pos) 
{
	return (n & (1 << bit_pos)) >> bit_pos;
}

Cell::Cell()
{
	top = nullptr;
	bot = nullptr;
	left = nullptr;
	right = nullptr;

	coordX = -1;
	coordY = -1;
}

Cell::Cell(Cell* top, Cell* bot, Cell* left, Cell* right)
{
	this->top = top;
	this->bot = bot;
	this->left = left;
	this->right = right;

	coordX = -1;
	coordY = -1;
}

bool Cell::operator==(const Cell& cmpr) const
{
	if ((bool)top != (bool)cmpr.top) return false;
	if ((bool)bot != (bool)cmpr.bot) return false;
	if ((bool)left != (bool)cmpr.left) return false;
	if ((bool)right != (bool)cmpr.right) return false;

	return true;
}

bool Cell::operator!=(const Cell& cmpr) const
{
	return !(operator==(cmpr));
}

void Cell::set(Cell* top, Cell* bot, Cell* left, Cell* right, int coordX, int coordY)
{
	this->top = top;
	this->bot = bot;
	this->left = left;
	this->right = right;

	this->coordX = coordX;
	this->coordY = coordY;
}

std::vector<Cell*> Cell::getPtrArray() {
	std::vector<Cell*> result;

	if (top) result.push_back(top);
	if (bot) result.push_back(bot);
	if (left) result.push_back(left);
	if (right) result.push_back(right);

	return result;
}

void Cell::addWallTop()
{
	if (top) {
		top->bot = nullptr;
		top = nullptr;
	}
}

void Cell::addWallBot()
{
	if (bot) {
		bot->top = nullptr;
		bot = nullptr;
	}
}

void Cell::addWallLeft()
{
	if (left) {
		left->right = nullptr;
		left = nullptr;
	}
}

void Cell::addWallRight()
{
	if (right) {
		right->left = nullptr;
		right = nullptr;
	}
}

Labyrinth::Labyrinth()
{
	sizeX = 0;
	sizeY = 0;
}


void initiateRow(std::vector<Cell>* topRow, std::vector<Cell>* currentRow, std::vector<Cell>* botRow, int rowID)
{
	int size = currentRow->size();

	Cell* topRowPtr = nullptr;
	Cell* botRowPtr = nullptr;

	if (topRow) topRowPtr = topRow->begin()._Ptr;
	if (botRow) botRowPtr = botRow->begin()._Ptr;

	Cell* currentRowPtrPrev = currentRow->begin()._Ptr;
	auto currentRowPtr = currentRow->begin();

	Cell* currentRowPtrNext;
	if (currentRow->begin() + 1 == currentRow->end()) currentRowPtrNext = nullptr;
	else currentRowPtrNext = (currentRow->begin() + 1)._Ptr;

	currentRowPtr->set(topRowPtr, botRowPtr, nullptr, currentRowPtrNext, 0, rowID);
	++currentRowPtr;
	++currentRowPtrNext;
	if (topRowPtr) ++topRowPtr;
	if (botRowPtr) ++botRowPtr;

	for (size_t i = 2; i < size; ++i)
	{
		currentRowPtr->set(topRowPtr, botRowPtr, currentRowPtrPrev, currentRowPtrNext, i - 1, rowID);

		++currentRowPtrPrev;
		++currentRowPtr;
		++currentRowPtrNext;
		if (topRowPtr) ++topRowPtr;
		if (botRowPtr) ++botRowPtr;
	}

	if(size > 1) currentRowPtr->set(topRowPtr, botRowPtr, currentRowPtrPrev, nullptr, size - 1, rowID);
}

void Labyrinth::createTable(int sizeX, int sizeY)
{
	table = std::vector<std::vector<Cell>>(sizeY, std::vector<Cell>(sizeX));

	std::vector<Cell>* tablePtrPrev = table.begin()._Ptr;
	std::vector<Cell>* tablePtrCurrent = table.begin()._Ptr;
	std::vector<Cell>* tablePtrNext;
	if (table.begin() + 1 == table.end()) tablePtrNext = nullptr;
	else tablePtrNext = (table.begin() + 1)._Ptr;

	initiateRow(nullptr, tablePtrCurrent, tablePtrNext, 0);
	++tablePtrCurrent;
	++tablePtrNext;

	for (size_t i = 2; i < sizeY; ++i)
	{
		initiateRow(tablePtrPrev, tablePtrCurrent, tablePtrNext, i - 1);
		++tablePtrPrev;
		++tablePtrCurrent;
		++tablePtrNext;
	}
	if(table.size() > 1) initiateRow(tablePtrPrev, tablePtrCurrent, nullptr, sizeY - 1);

	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

Labyrinth::Labyrinth(int sizeX, int sizeY)
{
	if (sizeY < 0) sizeY = sizeX;

	createTable(sizeX, sizeY);
}

bool Labyrinth::operator==(const Labyrinth& cmpr) const
{
	if (sizeX != cmpr.sizeX or sizeY != cmpr.sizeY) return false;

	for (size_t i = 0; i < sizeY; ++i)
	{
		for (size_t j = 0; j < sizeX; ++j)
		{
			if (table[i][j] != cmpr.table[i][j]) return false;
		}
	}

	return true;
}

std::vector<Cell>& Labyrinth::operator[](int i)
{
	return table[i];
}

void Labyrinth::exportToFile_Text(std::string filename)
{
	std::ofstream file(filename);

	file << sizeX << " " << sizeY << std::endl;

	auto rowPtr = table.begin();
	for (int i = 0; i < sizeY; ++i)
	{
		auto cellPtr = rowPtr->begin();
		for (int j = 1; j < sizeX; ++j)
		{
			file << !(bool)cellPtr->right << " ";
			++cellPtr;
		}
		file << std::endl;
		++rowPtr;
	}

	rowPtr = table.begin();
	for (int i = 1; i < sizeY; ++i)
	{
		auto cellPtr = rowPtr->begin();
		for (int j = 0; j < sizeX; ++j)
		{
			file << !(bool)cellPtr->bot << " ";
			++cellPtr;
		}
		file << std::endl;
		++rowPtr;
	}

	file.close();
}


void Labyrinth::importFromFile_Text(std::string filename)
{
	std::vector<std::vector<int>> verticalWalls;
	std::vector<std::vector<int>> horizontalWalls;

	std::ifstream file(filename);

	std::string sizeXstr, sizeYstr;
	if (file.eof()) return;
	file >> sizeXstr;
	if (file.eof()) return;
	file >> sizeYstr;
	if (!isNatural(sizeXstr) or !isNatural(sizeYstr)) return;
	createTable(sizeX, sizeY);

	bool isWall = false;

	for (size_t i = 0; i < sizeY; ++i)
	{
		for (size_t j = 1; j < sizeX; ++j)
		{
			file >> isWall;
			if (isWall)	{
				table[i][j].left->right = nullptr;
				table[i][j].left = nullptr;
			}
		}
	}

	for (size_t i = 1; i < sizeY; ++i)
	{
		for (size_t j = 0; j < sizeX; ++j)
		{
			file >> isWall;
			if (isWall) {
				table[i][j].top->bot = nullptr;
				table[i][j].top = nullptr;
			}
		}
	}
}

Cell* Labyrinth::getCell(int x, int y)
{
	return &table[y][x];
}

unsigned int Labyrinth::getSizeX() const
{
	return sizeX;
}

unsigned int Labyrinth::getSizeY() const
{
	return sizeY;
}

void Labyrinth::print()
{
	for (size_t i = 0; i < sizeX; ++i)
	{
		std::cout << " ___";
	}
	std::cout << "\n";

	auto rowPtr = table.begin();
	for (int i = 0; i < sizeY; ++i)
	{
		std::cout << "|";
		auto cellPtr = rowPtr->begin();
		for (int j = 0; j < sizeX; ++j)
		{
			if (cellPtr->bot) std::cout << "   ";
			else std::cout << "___";

			if (cellPtr->right) std::cout << " ";
			else std::cout << "|";

			++cellPtr;
		}
		std::cout << "\n";
		++rowPtr;
	}
}

int Labyrinth::countDeadends()
{
	int counter = 0;
	for (size_t i = 0; i < table.size(); ++i)
	{
		for (size_t j = 0; j < table[i].size(); ++j)
		{
			if (table[i][j].getPtrArray().size() <= 1) ++counter;
		}
	}
	return counter;
}