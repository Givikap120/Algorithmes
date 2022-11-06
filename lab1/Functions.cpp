#include "Header.h"
#include "FileFunc.h"

#include <random>
#include <iostream>
#include <fstream>

typedef unsigned long long ull;

void generateFile(int count, std::string name, ull max)
{
	std::ofstream output(name);

	std::random_device seed;
	std::mt19937 engine(seed());

	std::uniform_int_distribution<size_t> generator(0, max);

	for (size_t i = 0; i < count; i++)
	{
		output << generator(engine) << " ";
	}

	output.close();
}
void generateBinFile16(int count, std::string name, ull max)
{
	std::ofstream output(name, std::fstream::binary);

	std::random_device seed;
	std::mt19937 engine(seed());

	std::uniform_int_distribution<unsigned short> generator(0, max);

	unsigned short n;

	if (max > USHRT_MAX) max = USHRT_MAX;

	for (size_t i = 0; i < count; i++)
	{
		n = generator(engine);
		output.write((char*)&n, sizeof(unsigned short));
	}

	output.close();
}
void generateBinFile32(int count, std::string name, ull max)
{
	std::ofstream output(name, std::fstream::binary);

	std::random_device seed;
	std::mt19937 engine(seed());

	std::uniform_int_distribution<unsigned int> generator(0, max);

	unsigned int n;

	if (max > UINT32_MAX) max = UINT32_MAX;

	for (size_t i = 0; i < count; i++)
	{
		n = generator(engine);
		output.write((char*)&n, sizeof(unsigned int));
	}

	output.close();
}
void generateBinFile64(int count, std::string name, ull max)
{
	std::ofstream output(name, std::fstream::binary);

	std::random_device seed;
	std::mt19937 engine(seed());

	std::uniform_int_distribution<ull> generator(0, max);

	ull n;

	for (size_t i = 0; i < count; i++)
	{
		n = generator(engine);
		output.write((char*)&n, sizeof(ull));
	}

	output.close();
}

void convertBin64toText(std::string bin64name, std::string outputname) {
	std::fstream bin64file(bin64name, std::fstream::in | std::fstream::binary);
	std::fstream textfile(outputname, std::fstream::out | std::fstream::binary);

	int elementsCount = getFileSize(bin64name) / sizeof(ull);
	ull element;

	for (size_t i = 0; i < elementsCount; i++)
	{
		bin64file.read((char*)&element, sizeof(ull));
		textfile << element << " ";
	}

	bin64file.close();
	textfile.close();
}

bool checkFileSortingText(std::string filename)
{
	ull a, b;
	std::ifstream file(filename);
	file >> a;
	while (file >> b) {
		if (b < a) {
			//std::cout << "a = " << a << ", b = " << b << "\n";
			file.close();
			return false;
		}
		a = b;
	}
	return true;
}
bool checkFileSortingBin64(std::string filename)
{
	ull a, b;
	std::ifstream file(filename, std::ifstream::binary);

	int elementCount = getFileSize(filename) / sizeof(ull);
	file.read((char*)&a, sizeof(ull));

	for (size_t i = 1; i < elementCount; i++)
	{
		file.read((char*)&b, sizeof(ull));
		if (b < a) {
			//std::cout << "a = " << a << ", b = " << b << "\n";
			file.close();
			return false;
		}
		a = b;
	}

	return true;
}
