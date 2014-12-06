
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
		return 0;
	}

	std::string line = getNextLine(in);

	if (line.find("RPGCheck") == std::string::npos)
	{
		Utils::message("Unknown file format.");
		return 0;
	}

	line = getNextLine(in);
	std::size_t found = line.find("nChars=");
	if (found == std::string::npos)
	{
		Utils::message("Unknown file format.");
		return 0;
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
	
	return 1;
}

std::string getNextLine(std::ifstream &in)
{
	std::string line("");
	getline(in, line);
	while (line.compare("") == 0 || line[0] == '#')
		getline(in,line);
	return line;
}

}


