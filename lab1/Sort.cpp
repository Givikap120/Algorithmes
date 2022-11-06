#include "Sort.h"
#include "FileFunc.h"

#include <fstream>
#include <cmath>
#include <iostream>

typedef unsigned long long ull;

const std::string A_NAME("A"), B_NAME("B"), C_NAME("C");

int getMaxDegree(int elementCount) {
	float rawLog = log2(elementCount);
	return ceil(rawLog);
}

bool getBit(int n, int bit_pos) {
	return (n & (1 << bit_pos)) >> bit_pos;
}

int divideFile(std::string input_name, std::string a_name, std::string b_name, int degree) {
	std::fstream input(input_name, std::fstream::in | std::fstream::binary);
	std::fstream a(a_name, std::fstream::out | std::fstream::binary);
	std::fstream b(b_name, std::fstream::out | std::fstream::binary);

	int elementCount = getFileSize(input_name) / sizeof(ull);
	ull number;

	for (size_t i = 0; i < elementCount; i++)
	{
		input.read((char*)&number, sizeof(ull));
		if (getBit(i, degree)) b.write((char*)&number, sizeof(ull));
		else a.write((char*)&number, sizeof(ull));
	}

	input.close();
	a.close();
	b.close();

	return elementCount;
}

void fullMerge(std::fstream& a, std::fstream& b, std::fstream& c, int degree, ull& a_element, ull& b_element) {

	int a_counter = 1;
	int b_counter = 1;

	while (a_counter < degree and b_counter < degree) {
		if (a_element <= b_element) {
			c.write((char*)&a_element, sizeof(ull));
			a.read((char*)&a_element, sizeof(ull));
			a_counter++;
		}
		else {
			c.write((char*)&b_element, sizeof(ull));
			b.read((char*)&b_element, sizeof(ull));
			b_counter++;
		}
	}
	if (a_counter < degree) {
		for (a_counter; a_counter < degree; a_counter++)
		{
			c.write((char*)&a_element, sizeof(ull));
			a.read((char*)&a_element, sizeof(ull));
		}
	}
	else if (b_counter < degree) {
		for (b_counter; b_counter < degree; b_counter++)
		{
			c.write((char*)&b_element, sizeof(ull));
			b.read((char*)&b_element, sizeof(ull));
		}
	}
}

void partialMerge(std::fstream& a, std::fstream& b, std::fstream& c, ull& a_element, ull& b_element, int a_count, int b_count) {

	int a_counter = a.tellg() / sizeof(ull);
	int b_counter = b.tellg() / sizeof(ull);

	while (a_counter < a_count and b_counter < b_count) {
		if (a_element <= b_element) {
			c.write((char*)&a_element, sizeof(ull));
			a.read((char*)&a_element, sizeof(ull));
			a_counter++;
		}
		else {
			c.write((char*)&b_element, sizeof(ull));
			b.read((char*)&b_element, sizeof(ull));
			b_counter++;
		}
	}
	if (a_counter < a_count) {
		for (a_counter; a_counter < a_count; a_counter++)
		{
			c.write((char*)&a_element, sizeof(ull));
			a.read((char*)&a_element, sizeof(ull));
		}
	}
	else if (b_counter < b_count) {
		for (b_counter; b_counter < b_count; b_counter++)
		{
			c.write((char*)&b_element, sizeof(ull));
			b.read((char*)&b_element, sizeof(ull));
		}
	}
}

void mergeByDegree(std::string a_name, std::string b_name, std::string c_name, int degree) {
	std::fstream a(a_name, std::fstream::in | std::fstream::binary);
	std::fstream b(b_name, std::fstream::in | std::fstream::binary);
	std::fstream c(c_name, std::fstream::out | std::fstream::binary);

	int a_count = getFileSize(a_name) / sizeof(ull);
	int b_count = getFileSize(b_name) / sizeof(ull);

	int full_a_cycles = a_count / (2 * degree);
	int full_b_cycles = b_count / (2 * degree);

	if (full_a_cycles != full_b_cycles) std::cout << "HOW???\n";

	ull a_element;
	ull b_element;

	a.read((char*)&a_element, sizeof(ull));
	b.read((char*)&b_element, sizeof(ull));

	for (size_t i = 0; i < full_a_cycles; i++)
	{
		fullMerge(a, b, c, degree * 2, a_element, b_element);
	}

	partialMerge(a, b, c, a_element, b_element, a_count, b_count);

}

void sortByDegree(std::string input_name, std::string a_name, std::string b_name, std::string c_name, int degree, bool progress_showcase) {

	divideFile(input_name, a_name, b_name, degree);
	mergeByDegree(a_name, b_name, c_name, degree);

}

void deleteABC() {
	remove((A_NAME + ".bin").c_str());
	remove((B_NAME + ".bin").c_str());
	remove((C_NAME + ".bin").c_str());
}

void sortBin64File(std::string filename, std::string output, bool deleteInter, bool progressShowcase) {
	std::fstream fileToSort(filename, std::fstream::in | std::fstream::binary);
	int fileElementCount = getFileSize(filename)/sizeof(ull);
	int degree = 2;
	int maxDegree = getMaxDegree(fileElementCount);

	sortByDegree(filename, A_NAME + ".bin", B_NAME + ".bin", C_NAME + ".bin", 1, progressShowcase);

	for (degree; degree < maxDegree; degree *= 2)
	{
		sortByDegree(C_NAME + ".bin", A_NAME + ".bin", B_NAME + ".bin", C_NAME + ".bin", 1, progressShowcase);
	}

	sortByDegree(C_NAME + ".bin", A_NAME + ".bin", B_NAME + ".bin", output, 1, progressShowcase);

	if (deleteInter) deleteABC();

	fileToSort.close();
}
