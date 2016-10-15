#include "LapinMale.hpp"


bool LapinMale::isMature()
{
	return (age_ < 4 ? false : true);
}

void LapinMale::accoupler(LapinFemelle& f)
{
	if(isMature())
		f.setGestation();
}

std::string LapinMale::toString()
{
	std::ostringstream oss;
	oss << "Male :" << std::endl;
	oss << (isMature() ? "Mature " : "") << "Duree de vie : " << dureeVie_ << " Age : " << age_ << std::endl;
	oss << std::endl;
	return oss.str();
}
