#ifndef RPGDATA_H
#define RPGDATA_H

#include <vector>
#include <string>

class RpgData
{
public:
	RpgData() {};
	~RpgData() {};

	std::vector<std::string> char_names;
	std::vector<std::string> skill_names;
	std::vector<std::vector<int>> skill_mods;
};

#endif //RPGDATA_H
