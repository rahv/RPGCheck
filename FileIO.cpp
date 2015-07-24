
#include "FileIO.h"

#include <iostream>
#include <fstream>

#include "RpgData.h"
#include "Utils.h"

namespace FileIO
{

int readCharFile(std::string const& file_name,
                 RpgData &data)
{
	std::ifstream in( file_name.c_str() );
	if (!in.is_open())
	{
		Utils::message("Error reading file.");
		return 1;
	}

	std::string line = getNextLine(in);

	if (line.find("RPGCheck") == std::string::npos)
	{
		Utils::message("Unknown file format.");
		return 2;
	}

	line = getNextLine(in);
	std::size_t found = line.find("nChars=");
	if (found == std::string::npos)
	{
		Utils::message("Unknown file format.");
		return 3;
	}
	unsigned const n_chars = static_cast<unsigned>(std::atoi(line.substr(found+7, 2).c_str()));
	
	line = getNextLine(in);
	std::list<std::string> names = Utils::splitString(line, '\t');
	auto it = names.cbegin(); ++it;
	for (it; it != names.cend(); ++it)
		data.char_names.push_back(*it);

	while ( getline(in, line) )
	{
		if (line.compare("") == 0 || line[0] == '#')
			continue;

		names = Utils::splitString(line, '\t');
		it = names.cbegin(); 
		data.skill_names.push_back(*it);
		++it;
		std::vector<int> skill;
		for (it; it != names.cend(); ++it)
			skill.push_back(atoi((*it).c_str()));

		data.skill_mods.push_back(skill);
	}
	
	return 0;
}

std::string getNextLine(std::ifstream &in)
{
	std::string line("");
	getline(in, line);
	while (line.compare("") == 0 || line[0] == '#')
		getline(in,line);
	return line;
}

int readStatistics(std::vector<unsigned> &n_rolls, std::vector<double> &average)
{
	std::ifstream in( "stats.nfo" );
	if (!in.is_open())
	{
		std::cout << "Statistics not found...\n";
		n_rolls = std::vector<unsigned>(9,0);
		average = std::vector<double>(9,0);
		return 1;
	}
	std::cout << "Loading statistics...\n";
	unsigned n;
	double a;
	std::string labels[9] = { "D2", "D3", "D4", "D6", "D8", "D10", "D12", "D20", "D100" };
	for (std::size_t i=0; i<9; ++i)
	{
		in >> n >> a;
		n_rolls.push_back(n);
		average.push_back(a);
		std::cout << "Average for " << labels[i] << " is " << average[i] << " on " << n_rolls[i] << " rolls.\n";
	}
	in.close();
	return 0;
}

int writeStatistics(std::vector<unsigned> const& n_rolls, std::vector<double> const& average)
{
	std::ofstream out( "stats.nfo" );
	std::cout << "Updating statistics...\n";
	for (std::size_t i=0; i<9; ++i)
		out << n_rolls[i] << "\t" << average[i] << "\n";
	out.close();
	return 0;
}

}


