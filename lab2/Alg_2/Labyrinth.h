#pragma once
#include <vector>
#include <string>

struct Cell {
	Cell *top, *bot, *left, *right;

	int coordX, coordY;

	Cell();
	Cell(Cell* top, Cell* bot, Cell* left, Cell* right);

	bool operator==(const Cell& cmpr) const;

	void set(Cell* top, Cell* bot, Cell* left, Cell* right, int coordX, int coordY);
	std::vector<Cell*> getPtrArray();

	void addWallTop();
	void addWallBot();
	void addWallLeft();
	void addWallRight();
};

class Labyrinth {
	unsigned int sizeX, sizeY;
	std::vector<std::vector<Cell>> table;

	void createDeadend(int x, int y);

public:
	Labyrinth();
	Labyrinth(int sizeX, int sizeY = -1);

	void createTable(int sizeX, int sizeY);

	bool operator==(const Labyrinth& cmpr) const;

	std::vector<Cell>& operator[](int i);

	void importFromFile_Text(std::string filename);
	void exportToFile_Text(std::string filename);

	void generate(float wallChance = 0.2, float deadendChance = 0.2);

	Cell* getCell(int x, int y);

	void print();

	int countDeadends();
	inline int countAllNodes() { return sizeX * sizeY; }

	friend int IDS(int startX, int startY, int endX, int endY, Labyrinth& labyrinth);
	friend int Astar(int startX, int startY, int endX, int endY, Labyrinth& labyrinth);

	friend int IDS_debug(int startX, int startY, int endX, int endY, Labyrinth& labyrinth, int& iterations, int& visited);
	friend int Astar_debug(int startX, int startY, int endX, int endY, Labyrinth& labyrinth, int& iterations, int& visited);
};

int IDS(int startX, int startY, int endX, int endY, Labyrinth& labyrinth);
int Astar(int startX, int startY, int endX, int endY, Labyrinth& labyrinth);

int IDS_debug(int startX, int startY, int endX, int endY, Labyrinth& labyrinth, int& iterations, int& visited);
int Astar_debug(int startX, int startY, int endX, int endY, Labyrinth& labyrinth, int& iterations, int& visited);