#include "FileFunc.h"

int getFileSize(std::string filename) {
	struct stat buf;
	stat(filename.c_str(), &buf);
	return buf.st_size;
}
