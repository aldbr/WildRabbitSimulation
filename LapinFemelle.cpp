#include "LapinFemelle.hpp"

LapinFemelle::LapinFemelle() : Lapin(), enGestation_(false), nbPortees_(0) {}

bool LapinFemelle::inGestation()
{
	return (enGestation_ ? true : false);
}
	
int LapinFemelle::getNbPortees()
{
	return nbPortees_;
}

void LapinFemelle::incrementNbPortees()
{
	++nbPortees_;
}
	
int LapinFemelle::getNbPorteesMax()
{
	return nbPorteesMax_;
}

void LapinFemelle::setNbPorteesMax()
{
	//Modele::histogram();
}

bool LapinFemelle::isMature()
{
	return (age_ < 3 ? false : true);
}

std::string LapinFemelle::toString()
{
	std::ostringstream oss;
	oss << "Femelle - mature : " << (isMature() ? "oui" : "non") << " duree de vie : " << dureeVie_ << " age : " << age_ << std::endl;
	return oss.str();
}


