#ifndef MODELE_HPP
#define MODELE_HPP

#include "Lapin.hpp"
#include <vector>

class Modele 
{
	std::vector<Lapin> lapins_(5000);
	
	int temps_;
	
	static float randomFloat(float a, float b);
	
	public :
	Modele(int temps);
	static int rejectionNormalLaw(int mean , int  stdDev);
	static int histogram(int nbClasses, float * pourcentages);
	void initializeSimulation();
};

#endif
