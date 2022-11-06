#include "Labyrinth.h"
#include <iostream>

int DFS(Cell* start, Cell* end, int depth)
{
	if (start == end) return depth;
	else if (depth <= 0) return -1;

	auto targetArray = start->getPtrArray();
	int result;

	for (auto targetArrayIterator = targetArray.begin(); targetArrayIterator != targetArray.end(); ++targetArrayIterator) {
		result = DFS(*targetArrayIterator, end, depth - 1);
		if (result >= 0) return result + 1;
	}

	return -1;
}

int IDS(int startX, int startY, int endX, int endY, Labyrinth& labyrinth)
{
	Cell* startCell = labyrinth.getCell(startX, startY);
	Cell* endCell = labyrinth.getCell(endX, endY);

	int depth = 0, result;
	while (true)
	{
		result = DFS(startCell, endCell, depth);
		std::cout << "Depth " << depth << " done!\n";
		if (result >= 0) break;
		++depth;
	}
	return result;
}