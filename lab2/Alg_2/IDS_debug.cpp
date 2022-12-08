#include "Labyrinth.h"
#include <iostream>

typedef __int8 Bool;
typedef std::vector<std::vector<Bool>> binary_table;

int DFS_debug(Cell* start, Cell* end, int depth, int& iterations, binary_table& visited, std::vector<Cell*>& path)
{
	++iterations;

	visited[start->coordY][start->coordX] = 1;

	if (start == end) {
		path.push_back(start);
		return depth;
	}
	else if (depth <= 0) return -1;

	auto targetArray = start->getPtrArray();
	int result;

	for (auto targetArrayIterator = targetArray.begin(); targetArrayIterator != targetArray.end(); ++targetArrayIterator) {
		result = DFS_debug(*targetArrayIterator, end, depth - 1, iterations, visited, path);
		if (result >= 0) {
			path.push_back(start);
			return result + 1;
		}
	}

	return -1;
}

int countTrues(binary_table& table)
{
	int counter = 0;
	for (size_t i = 0; i < table.size(); ++i)
	{
		for (size_t j = 0; j < table[i].size(); ++j)
		{
			if (table[i][j]) ++counter;
		}
	}
	return counter;
}

void printPath(const std::vector<Cell*>& path)
{
	for (size_t i = 0; i < path.size(); ++i)
	{
		std::cout << path[i]->coordX << "-" << path[i]->coordY << " ";
	}
	std::cout << '\n';
}


int IDS_debug(int startX, int startY, int endX, int endY, Labyrinth& labyrinth, int& iterations, int& visited)
{
	iterations = 0, visited = 0;
	Cell* startCell = labyrinth.getCell(startX, startY);
	Cell* endCell = labyrinth.getCell(endX, endY);

	binary_table visitedTable(labyrinth.sizeY, std::vector<Bool>(labyrinth.sizeX, 0));

	int depth = 0, result;
	std::vector<Cell*> path;
	while (true)
	{
		result = DFS_debug(startCell, endCell, depth, iterations, visitedTable, path);
		std::cout << "Depth " << depth << " done!\n";
		if (result >= 0) break;
		++depth;
	}
	std::reverse(path.begin(), path.end());

	std::cout << "\nPath:\n";
	printPath(path);

	visited = countTrues(visitedTable);

	return result;
}