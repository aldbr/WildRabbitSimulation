#ifndef LAPINFEM_HPP
#define LAPINFEM_HPP

#include "Lapin.hpp"

class LapinFemelle : public Lapin
{
	bool enGestation_;
	short int nbPortees_;
	short int nbPorteesMax_;
	
	public :
	LapinFemelle();
	
	bool setGestation();
	
	int getNbPortees();
	void incrementNbPortees();
	
	int getNbPorteesMax();
	void setNbPorteesMax();
	
	void incrementAge();
	bool isMature();
	
	int donnerNaissance();
	
	std::string toString();
	
	void reinit();	
};

#endif

