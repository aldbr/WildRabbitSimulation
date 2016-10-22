#ifndef MODELE_HPP
#define MODELE_HPP

#include "Lapin.hpp"
#include <list>
#include <string>

class Modele 
{
	int temps_;	
	
	public :
	Modele(int temps);
	static float randomFloat(float a, float b);
	static int rejectionNormalLaw(int mean , int  stdDev);
	static int histogram(int nbClasses, float * pourcentages);
	void initializeSimulation();
	std::string toString(int i);
	
	static std::list<Lapin*> lapins_;
};

#endif
