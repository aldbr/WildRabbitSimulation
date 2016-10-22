#ifndef MODELE_HPP
#define MODELE_HPP

#include "LapinMale.hpp"
#include "LapinFemelle.hpp"

#include <list>
#include <string>

class Modele 
{
	int temps_;	
	
	void verifierEtatLapins();
	void detruireModele();
	void accouplement();
	void incrementerAge();
	void naissance();
	
	public :
	Modele(int temps);
	static float randomFloat(float a, float b);
	static int rejectionNormalLaw(int mean , int  stdDev);
	static int histogram(int nbClasses, float * pourcentages);
	void initializeSimulation();
	std::string toString(int i);
	
	static std::list<LapinMale*> lapinsMale_;
	static std::list<LapinFemelle*> lapinsFemelle_;
};

#endif
