#pragma once
#include <string>

void generateFile(int count, std::string name, unsigned long long max = ULLONG_MAX);
void generateBinFile16(int count, std::string name, unsigned long long max = USHRT_MAX);
void generateBinFile32(int count, std::string name, unsigned long long max = UINT16_MAX);
void generateBinFile64(int count, std::string name, unsigned long long max = ULLONG_MAX);

void convertBin64toText(std::string bin64name, std::string outputname);

bool checkFileSortingText(std::string filename);
bool checkFileSortingBin64(std::string filename);

void sortFile(std::string fileName);

