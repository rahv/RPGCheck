#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <vector>
#include <QString>

class RpgData;

namespace FileIO
{
	int readCharFile(std::string const& file_name,
	                 RpgData &data);

	std::string getNextLine(std::ifstream &in);
}

#endif //FILEIO_H
