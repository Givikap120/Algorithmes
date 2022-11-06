#include "Labyrinth.h"
#include <iostream>
#include <vector>
#include <algorithm>

namespace debug
{

struct Variant
{
	Cell* ptr;
	int traveledDistance, euristicDistance;
	Variant(Cell* _ptr, int _traveledDistance, int _euristicDistance) :ptr(_ptr), traveledDistance(_traveledDistance), euristicDistance(_euristicDistance)
	{}
	inline int x() { return ptr->coordX; }
	inline int y() { return ptr->coordY; }
};

inline int calculateEuristic(Cell* cellPtr, int endX, int endY) { return abs(endX + endY - cellPtr->coordX - cellPtr->coordY); }
inline int calculateEuristic(int startX, int startY, int endX, int endY) { return abs(endX + endY - startX - startY); }

typedef __int8 Bool;
typedef std::vector<std::vector<Bool>> binary_table;

bool findAnyWay(std::vector<Variant>& queue, binary_table& visited, int index, int endX, int endY, int& iterations)
{
	++iterations;
	auto finded = queue[index];

	if (finded.x() == endX and finded.y() == endY) return true;

	visited[finded.y()][finded.x()] = 1;

	auto adjoining = finded.ptr->getPtrArray();
	auto adjoiningIter = adjoining.begin();

	for (size_t i = 0; i < adjoining.size(); ++i)
	{
		if (visited[(*adjoiningIter)->coordY][(*adjoiningIter)->coordX]) { ++adjoiningIter; continue; }
		
		queue.push_back(Variant(*(adjoiningIter._Ptr), finded.traveledDistance + 1, calculateEuristic(*adjoiningIter, endX, endY)));
		++adjoiningIter;
	}
	return false;
}

bool findMinWay(std::vector<Variant>& queue, binary_table& visited, int index, int endX, int endY, int bestDistance, int& iterations)
{
	++iterations;
	auto finded = queue[index];

	if (finded.x() == endX and finded.y() == endY) return true;

	visited[finded.y()][finded.x()] = 1;

	if (finded.euristicDistance + finded.traveledDistance >= bestDistance) return false;

	auto adjoining = finded.ptr->getPtrArray();
	auto adjoiningIter = adjoining.begin();

	for (size_t i = 0; i < adjoining.size(); ++i)
	{
		if (visited[(*adjoiningIter)->coordY][(*adjoiningIter)->coordX]) continue;

		queue.push_back(Variant(*(adjoiningIter._Ptr), finded.traveledDistance + 1, calculateEuristic(*adjoiningIter, endX, endY)));
		++adjoiningIter;
	}
	return false;
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

}

using namespace debug;

int Astar_debug(int startX, int startY, int endX, int endY, Labyrinth& labyrinth, int& iterations, int& visited)
{
	iterations = 0;
	std::vector<Variant> priorityQueue;
	binary_table visitedTable(labyrinth.sizeY, std::vector<Bool>(labyrinth.sizeX, 0));

	priorityQueue.push_back(Variant(&labyrinth[startY][startX], 0, calculateEuristic(startX, startY, endX, endY)));
	findAnyWay(priorityQueue, visitedTable, 0, endX, endY, iterations);
	priorityQueue.erase(priorityQueue.begin());

	bool result = false;
	int findedIndex;
	while (priorityQueue.size() > 0)
	{
		findedIndex = std::min_element(priorityQueue.begin(), priorityQueue.end(),
			[](const Variant& v1, const Variant& v2) -> bool {
				return v1.euristicDistance + v1.traveledDistance < v2.euristicDistance + v2.traveledDistance; })
			- priorityQueue.begin();
				result = findAnyWay(priorityQueue, visitedTable, findedIndex, endX, endY, iterations);
				if (result) break;
				priorityQueue.erase(priorityQueue.begin() + findedIndex);
	}

	if (!result)
	{
		visited = countTrues(visitedTable);
		return -1;
	}

	int bestDistance = priorityQueue[findedIndex].traveledDistance;

	while (priorityQueue.size() > 0)
	{
		findedIndex = std::min_element(priorityQueue.begin(), priorityQueue.end(),
			[](const Variant& v1, const Variant& v2) -> bool {
				return v1.euristicDistance + v1.traveledDistance < v2.euristicDistance + v2.traveledDistance; })
			- priorityQueue.begin();
				result = findMinWay(priorityQueue, visitedTable, findedIndex, endX, endY, bestDistance, iterations);
				if (result and priorityQueue[findedIndex].traveledDistance < bestDistance) bestDistance = priorityQueue[findedIndex].traveledDistance;
				priorityQueue.erase(priorityQueue.begin() + findedIndex);
	}

	visited = countTrues(visitedTable);
	return bestDistance;
}