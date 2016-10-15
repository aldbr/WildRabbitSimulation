#include "LapinMale.hpp"

bool LapinMale::isMature()
{
	return (age_ < 4 ? false : true);
}

std::string LapinMale::toString()
{
	std::ostringstream oss;
	oss << "Male- mature : " << (isMature() ? "oui" : "non") << " duree de vie : " << dureeVie_ << " age : " << age_ << std::endl;
	return oss.str();
}
