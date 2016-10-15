#ifndef LAPINFEM_HPP
#define LAPINFEM_HPP

#include "Lapin.hpp"

class LapinFemelle : public Lapin
{
	bool enGestation_;
	int nbPortees_;
	int nbPorteesMax_;
	
	
	
	
	public :
	LapinFemelle();
	
	bool inGestation();
	
	int getNbPortees();
	void incrementNbPortees();
	
	int getNbPorteesMax();
	void setNbPorteesMax();
	
	void incrementAge();
	bool isMature();
	
	std::string toString();	
};

#endif

