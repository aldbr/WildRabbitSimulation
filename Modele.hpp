#ifndef MODELE_HPP
#define MODELE_HPP

#include "LapinMale.hpp"
#include "LapinFemelle.hpp"

#include <list>
#include <string>

#define TMAX 2000000

class Modele 
{
	int temps_;	
	
	LapinMale *lapinsMale_;
	static int tLogiqueMale;
	
	LapinFemelle *lapinsFemelle_;
	static int tLogiqueFemelle;
	
	

	void verifierEtatLapins();
	void detruireModele();
	void accouplement();
	void incrementerAge();
	void naissance();
	
	public :
		Modele(int temps);
		~Modele();
		static float randomFloat(float a, float b);
		static int rejectionNormalLaw(int mean , int  stdDev);
		static int histogram(int nbClasses, float * pourcentages);
		int initializeSimulation();
		std::string toString(int i, int nb);
		
		static int getTMax();
		
		static int getTLogiqueMale();
		static void setTLogiqueMale(int nb);
		
		static int getTLogiqueFemelle();
		static void setTLogiqueFemelle(int nb);
		
		static std::list<LapinMale *> lapinsMortsMale_;
		static std::list<LapinFemelle *> lapinsMortsFemelle_;
	
};

#endif
