
#include "DiceGen.h"

#include <random>
#include <iostream>

namespace DiceGen
{

int makeSave(int mod, std::string const& char_name, std::string const& skill_name)
{
	int const result = static_cast<int>(rollDice(1,20));
	std::cout << "    " << char_name << " rolled " << result+mod << " (" << result << " + " << mod << ")\n";
	return (result+mod);
}

int makeSkillCheck(int mod, std::string const& char_name, std::string const& skill_name)
{
	int const result = static_cast<int>(rollDice(3,6));
	std::cout << "    " <<char_name << " rolled " << result+mod << " (" << result << " + " << mod << ").\n";
	return (result+mod);
}

unsigned rollDice(unsigned number, unsigned max)
{
	std::random_device rd;
	std::mt19937 e2(rd()); // engine

	std::uniform_int_distribution<> dist(1, max);

	unsigned result(0);
	for (unsigned i=0; i<number; ++i)
		result += dist(e2);

	return result;
}

}
