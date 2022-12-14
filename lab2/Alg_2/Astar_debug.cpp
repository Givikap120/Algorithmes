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
		std::vector<Cell*> path;
		Variant(Cell* _ptr, int _traveledDistance, int _euristicDistance, std::vector<Cell*> _path) :ptr(_ptr), traveledDistance(_traveledDistance), euristicDistance(_euristicDistance), path(_path)
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
		finded.path.push_back(finded.ptr);

		if (finded.x() == endX and finded.y() == endY) return true;

		auto adjoining = finded.ptr->getPtrArray();
		auto adjoiningIter = adjoining.begin();

		for (size_t i = 0; i < adjoining.size(); ++i)
		{
			if (visited[(*adjoiningIter)->coordY][(*adjoiningIter)->coordX]) { ++adjoiningIter; continue; }
			visited[(*adjoiningIter)->coordY][(*adjoiningIter)->coordX] = 1;

			queue.push_back(Variant(*(adjoiningIter._Ptr), finded.traveledDistance + 1, calculateEuristic(*adjoiningIter, endX, endY), finded.path));
			++adjoiningIter;
		}
		return false;
	}

	bool findMinWay(std::vector<Variant>& queue, binary_table& visited, int index, int endX, int endY, int bestDistance, int& iterations)
	{
		++iterations;
		auto finded = queue[index];
		finded.path.push_back(finded.ptr);

		if (finded.x() == endX and finded.y() == endY) return true;

		if (finded.euristicDistance + finded.traveledDistance >= bestDistance) return false;

		auto adjoining = finded.ptr->getPtrArray();
		auto adjoiningIter = adjoining.begin();

		for (size_t i = 0; i < adjoining.size(); ++i)
		{
			if (visited[(*adjoiningIter)->coordY][(*adjoiningIter)->coordX]) continue;
			visited[(*adjoiningIter)->coordY][(*adjoiningIter)->coordX] = 1;

			queue.push_back(Variant(*(adjoiningIter._Ptr), finded.traveledDistance + 1, calculateEuristic(*adjoiningIter, endX, endY), finded.path));
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

	void printPath(Variant v)
	{
		for (size_t i = 0; i < v.path.size(); ++i)
		{
			std::cout << v.path[i]->coordX << "-" << v.path[i]->coordY << " ";
		}
		std::cout << v.ptr->coordX << "-" << v.ptr->coordY << '\n';
	}
}

using namespace debug;

int Astar_debug(int startX, int startY, int endX, int endY, Labyrinth& labyrinth, int& iterations, int& visited)
{
	iterations = 0;
	std::vector<Variant> priorityQueue;
	binary_table visitedTable(labyrinth.sizeY, std::vector<Bool>(labyrinth.sizeX, 0));

	priorityQueue.push_back(Variant(&labyrinth[startY][startX], 0, calculateEuristic(startX, startY, endX, endY), {}));
	bool result = findAnyWay(priorityQueue, visitedTable, 0, endX, endY, iterations);
	if (result) return 0;
	priorityQueue.erase(priorityQueue.begin());

	int findedIndex;
	while (priorityQueue.size() > 0)
	{
		findedIndex = std::min_element(priorityQueue.begin(), priorityQueue.end(),
			[](const Variant& v1, const Variant& v2) -> bool { return v1.euristicDistance + v1.traveledDistance < v2.euristicDistance + v2.traveledDistance; }) - priorityQueue.begin();
		result = findAnyWay(priorityQueue, visitedTable, findedIndex, endX, endY, iterations);
		if (result) break;
		priorityQueue.erase(priorityQueue.begin() + findedIndex);
	}

	if (!result)
	{
		visited = countTrues(visitedTable);
		return -1;
	}

	auto bestPath = priorityQueue[findedIndex];

	while (priorityQueue.size() > 0)
	{
		findedIndex = std::min_element(priorityQueue.begin(), priorityQueue.end(),
			[](const Variant& v1, const Variant& v2) -> bool {return v1.euristicDistance + v1.traveledDistance < v2.euristicDistance + v2.traveledDistance; }) - priorityQueue.begin();
		result = findMinWay(priorityQueue, visitedTable, findedIndex, endX, endY, bestPath.traveledDistance, iterations);
		if (result and priorityQueue[findedIndex].traveledDistance < bestPath.traveledDistance) bestPath = priorityQueue[findedIndex];
		priorityQueue.erase(priorityQueue.begin() + findedIndex);
	}
	visited = countTrues(visitedTable);

	std::cout << "Path:\n";
	printPath(bestPath);

	return bestPath.traveledDistance;
}