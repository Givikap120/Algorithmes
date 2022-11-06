#include "ModSort.h"
#include "FileFunc.h"

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <sys/stat.h>

typedef unsigned long long ull;

const std::string NAME_DIVIDED_BASE = "D", NAME_SORTED_BASE = "S";

int getElementCount(std::fstream& file) {
	int counter = 0;
	ull element;
	file.seekg(0, std::ios_base::beg);
	while (file >> element) counter++;
	file.clear();
	file.seekg(0, std::ios_base::beg);
	return counter;
}

int chooseAdditionalFilesCount(int fileSize, int allowedMemory) {
	float rawCount = (float)fileSize / allowedMemory;
	float binLog = log2(rawCount);
	if (binLog < 0) binLog = 0;
	int exactCount = 1 << (int)ceil(binLog);
	return exactCount;
}
int chooseAdditionalFilesCountAlt(int fileSize, int allowedMemory) {
	float rawCount = (float)fileSize / allowedMemory;
	return ceil(rawCount);
}

void createDivideBin64(std::fstream& file_to_read, int id, int EPF) {
	std::fstream file_to_write;
	ull element;

	file_to_write.open(NAME_DIVIDED_BASE + std::to_string(id) + ".bin", std::fstream::out | std::fstream::binary);

	for (size_t i = 0; i < EPF; i++)
	{
		file_to_read.read((char*)&element, sizeof(ull));
		file_to_write.write((char*)&element, sizeof(ull));
	}
	file_to_write.close();
}
void divideBin64(std::fstream& file, int fileCount, int fileSize) {
	int elementsCount = fileSize / sizeof(ull);
	double rawEPF = elementsCount / fileCount;

	int effectiveEPF = ceil(rawEPF);
	int lastFileEPF = elementsCount - (fileCount - 1) * effectiveEPF;

	for (size_t i = 1; i < fileCount; i++)
	{
		createDivideBin64(file, i, effectiveEPF);
	}
	createDivideBin64(file, fileCount, lastFileEPF);
}

void createDividesortBin64(std::fstream& file_to_read, int id, int seria, int EPF) {
	std::fstream file_to_write;
	ull element;

	file_to_write.open(NAME_SORTED_BASE + std::to_string(seria) + "-" + std::to_string(id) + ".bin", std::fstream::out | std::fstream::binary);

	ull* buffer = new ull[EPF];

	for (size_t i = 0; i < EPF; i++)
	{
		file_to_read.read((char*)&element, sizeof(ull));
		buffer[i] = element;
	}

	std::sort(&(buffer[0]), &(buffer[EPF]));


	for (size_t i = 0; i < EPF; i++)
	{
		file_to_write.write((char*)&(buffer[i]), sizeof(ull));
	}
	
	delete[] buffer;
	file_to_write.close();
}
void dividesortBin64(std::fstream& file, int fileCount, int fileSize) {
	int elementsCount = fileSize / sizeof(ull);
	double rawEPF = (double)elementsCount / fileCount;

	int effectiveEPF = ceil(rawEPF);
	int lastFileEPF = elementsCount - (fileCount - 1) * effectiveEPF;

	for (size_t i = 1; i < fileCount; i++)
	{
		createDividesortBin64(file, i, fileCount, effectiveEPF);
	}
	createDividesortBin64(file, fileCount, fileCount, lastFileEPF);
}

void mergeFilesBin64(std::string file1name, std::string file2name, std::string outputname) {
	std::fstream file1(file1name, std::fstream::in | std::fstream::binary);
	std::fstream file2(file2name, std::fstream::in | std::fstream::binary);
	std::fstream output(outputname, std::fstream::out | std::fstream::binary);

	int file1size = getFileSize(file1name);
	int file2size = getFileSize(file2name);

	int file1count = file1size / sizeof(ull);
	int file2count = file2size / sizeof(ull);

	int file1counter = 0;
	int file2counter = 0;

	ull file1element;
	ull file2element;

	file1.read((char*)&file1element, sizeof(ull));
	file2.read((char*)&file2element, sizeof(ull));

	while (file1counter < file1count and file2counter < file2count) {
		if (file1element >= file2element) {
			output.write((char*)&file2element, sizeof(ull));
			file2.read((char*)&file2element, sizeof(ull));
			file2counter++;
		}
		else {
			output.write((char*)&file1element, sizeof(ull));
			file1.read((char*)&file1element, sizeof(ull));
			file1counter++;
		}
	}

	if (file1counter == file1count) {
		for (file2counter; file2counter < file2count - 1; file2counter++)
		{
			output.write((char*)&file2element, sizeof(ull));
			file2.read((char*)&file2element, sizeof(ull));
		}
		output.write((char*)&file2element, sizeof(ull));
	}
	else if (file2counter == file2count) {
		for (file1counter; file1counter < file1count - 1; file1counter++)
		{
			output.write((char*)&file1element, sizeof(ull));
			file1.read((char*)&file1element, sizeof(ull));
		}
		output.write((char*)&file1element, sizeof(ull));
	}

	file1.close();
	file2.close();
	output.close();
}
void mergePairsBin64(std::string nameBase, int fileCount, std::string output) {
	std::string file1name, file2name, outputname;
	for (size_t i = 0; i < fileCount/2; i++)
	{
		file1name = nameBase + std::to_string(fileCount) + "-" + std::to_string(2*i + 1) + ".bin";
		file2name = nameBase + std::to_string(fileCount) + "-" + std::to_string(2*i + 2) + ".bin";
		if (fileCount <= 2) outputname = output;
		else outputname = nameBase + std::to_string(fileCount / 2) + "-" + std::to_string(i + 1) + ".bin";
		mergeFilesBin64(file1name, file2name, outputname);
	}
}

void deleteSeria(std::string nameBase, int fileCount) {
	std::string nameToDelete;
	for (size_t i = 1; i <= fileCount; i++)
	{
		nameToDelete = nameBase + std::to_string(fileCount) + "-" + std::to_string(i) + ".bin";
		remove(nameToDelete.c_str());
	}
	
}

void sortBin64FileMod(std::string filename, std::string output, int allowedMemory, bool deleteInter)
{
	std::fstream fileToSort(filename, std::fstream::in | std::fstream::binary);
	int fileSize = getFileSize(filename);
	int fileCount = chooseAdditionalFilesCount(fileSize, allowedMemory);
	dividesortBin64(fileToSort, fileCount, fileSize);
	
	for (fileCount; fileCount > 1; fileCount /= 2)
	{
		mergePairsBin64(NAME_SORTED_BASE, fileCount, output);
		if(deleteInter) deleteSeria(NAME_SORTED_BASE, fileCount);
	}

	fileToSort.close();
}

void altMerge(std::string nameBase, int fileCount, std::string outputname) {
	std::vector<std::fstream*> fileArray(fileCount);
	std::vector<ull> currentElementArray(fileCount);

	std::vector<int> fileCounterArray(fileCount, 0);
	std::vector<int> fileElementCountArray(fileCount);

	int readedFileCount = 0;

	std::string filename;


	for (size_t i = 0; i < fileCount; i++)
	{
		filename = nameBase + std::to_string(fileCount) + "-" + std::to_string(i + 1) + ".bin";

		fileArray[i] = new std::fstream(filename, std::fstream::in | std::fstream::binary);

		fileElementCountArray[i] = getFileSize(filename) / sizeof(ull);
		fileArray[i]->read((char*)&(currentElementArray[i]), sizeof(ull));
	}

	std::ofstream outputFile(outputname, std::fstream::out | std::fstream::binary);

	int i;

	while (readedFileCount < fileCount) {
		i = std::distance(currentElementArray.begin(), std::max_element(currentElementArray.begin(), currentElementArray.end()));

		outputFile.write((char*)&(currentElementArray[i]), sizeof(ull));
		fileArray[i]->read((char*)&(currentElementArray[i]), sizeof(ull));
		fileCounterArray[i]++;

		if (fileCounterArray[i] >= fileElementCountArray[i]) {
			delete fileArray[i];
			fileArray.erase(fileArray.begin() + i);
			currentElementArray.erase(currentElementArray.begin() + i);
			fileCounterArray.erase(fileCounterArray.begin() + i);
			fileElementCountArray.erase(fileElementCountArray.begin() + i);

			readedFileCount++;
		}
	}


}

void sortBin64FileAlt(std::string filename, std::string output, int allowedMemory, bool deleteInter)
{
	std::fstream fileToSort(filename, std::fstream::in | std::fstream::binary);
	int fileSize = getFileSize(filename);
	int fileCount = chooseAdditionalFilesCountAlt(fileSize, allowedMemory);
	dividesortBin64(fileToSort, fileCount, fileSize);

	altMerge(NAME_SORTED_BASE, fileCount, output);

	if(deleteInter) deleteSeria(NAME_SORTED_BASE, fileCount);

	fileToSort.close();
}
