#include "LapinFemelle.hpp"
#include "Modele.hpp"
#include <iostream>

LapinFemelle::LapinFemelle() : Lapin(), enGestation_(false), nbPortees_(0) 
{
	setNbPorteesMax();
}

bool LapinFemelle::setGestation()
{
	if(!enGestation_ && nbPortees_ < nbPorteesMax_ && isMature())
	{
			enGestation_ = true;
			++nbPortees_;
	}
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
	nbPortees_ = 0;
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
		setNbPorteesMax(); //12 mois en fonction de l'age du lapin
	}
}

void LapinFemelle::donnerNaissance()
{
	enGestation_ = 0; //incrementAge entre accoupler et donnernaissance
	
}

std::string LapinFemelle::toString()
{
	std::ostringstream oss;
	oss << "Femelle :" << std::endl;
	oss << (isMature() ? "Mature " : "") << "Duree de vie : " << dureeVie_ << " Age : " << age_ << std::endl;
	oss << "En gestation : " << enGestation_ << std::endl;
	oss << "Nombre de portées pour l'année : " << nbPorteesMax_ << std::endl;
	oss << "Nombre de portées effective sur l'année : " << nbPortees_ << std::endl;
	oss << std::endl;
	return oss.str();
}


