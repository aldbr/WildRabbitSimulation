#ifndef MODELE_HPP
#define MODELE_HPP

#include "Lapin.hpp"
#include <vector>

class Modele 
{
	//std::vector<Lapin> lapins_;
	
	int temps_;
	
	static float randomFloat(float a, float b);
	
	public :
	Modele(int temps);
	static int rejectionNormalLaw(int mean , int  stdDev);
	static int histogram(int nbClasses, int * pourcentages);
	void initializeSimulation();
};

#endif
