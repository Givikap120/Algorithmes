#include "Labyrinth.h"
#include <iostream>

typedef __int8 Bool;
typedef std::vector<std::vector<Bool>> binary_table;

int DFS_debug(Cell* start, Cell* end, int depth, int& iterations, binary_table& visited)
{
	++iterations;

	visited[start->coordY][start->coordX] = 1;

	if (start == end) return depth;
	else if (depth <= 0) return -1;

	auto targetArray = start->getPtrArray();
	int result;

	for (auto targetArrayIterator = targetArray.begin(); targetArrayIterator != targetArray.end(); ++targetArrayIterator) {
		result = DFS_debug(*targetArrayIterator, end, depth - 1, iterations, visited);
		if (result >= 0) return result + 1;
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

int IDS_debug(int startX, int startY, int endX, int endY, Labyrinth& labyrinth, int& iterations, int& visited)
{
	iterations = 0, visited = 0;
	Cell* startCell = labyrinth.getCell(startX, startY);
	Cell* endCell = labyrinth.getCell(endX, endY);

	binary_table visitedTable(labyrinth.sizeY, std::vector<Bool>(labyrinth.sizeX, 0));

	int depth = 0, result;
	while (true)
	{
		result = DFS_debug(startCell, endCell, depth, iterations, visitedTable);
		std::cout << "Depth " << depth << " done!\n";
		if (result >= 0) break;
		++depth;
	}

	visited = countTrues(visitedTable);

	return result;
}