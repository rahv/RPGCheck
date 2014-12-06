#ifndef DICEGEN_H
#define DICEGEN_H

#include <string>

namespace DiceGen
{

	int makeSave(int mod, std::string const& char_name, std::string const& skill_name);

	int makeSkillCheck(int mod, std::string const& char_name, std::string const& skill_name);

	unsigned rollDice(unsigned number, unsigned max);

}

#endif //DICEGEN_H
