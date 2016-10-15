#include "LapinFemelle.hpp"
#include "Modele.hpp"

LapinFemelle::LapinFemelle() : Lapin(), enGestation_(false), nbPortees_(0) 
{
	setNbPorteesMax();
}

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
	float pourcentageChancesPortees [] = {0.1, 0.1, 0.2, 0.2, 0.2, 0.1, 0.1};
	nbPorteesMax_ = Modele::histogram(7, pourcentageChancesPortees)+1;
}

bool LapinFemelle::isMature()
{
	return (age_ < 3 ? false : true);
}

void LapinFemelle::incrementAge()
{
	++age_;
	if((age_ % 12) == 0)
	{
		setNbPorteesMax();
	}
}

std::string LapinFemelle::toString()
{
	std::ostringstream oss;
	oss << "Femelle :" << std::endl;
	oss << (isMature() ? "Mature" : "") << " duree de vie : " << dureeVie_ << " age : " << age_ << std::endl;
	oss << "Nombre de portées pour l'année : " << nbPorteesMax_ << std::endl;
	oss << std::endl;
	return oss.str();
}


