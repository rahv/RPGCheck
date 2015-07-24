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

	int readStatistics(std::vector<unsigned> &n_rolls, std::vector<double> &average);

	int writeStatistics(std::vector<unsigned> const& n_rolls, std::vector<double> const& average);
}

#endif //FILEIO_H
