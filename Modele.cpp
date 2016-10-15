#include "Modele.hpp"
#include "LapinMale.hpp"
#include "LapinFemelle.hpp"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

Modele::Modele(int temps) : temps_(temps)
{
	srand(time(NULL));
}

void Modele::initializeSimulation()
{
	int i = 0;
	LapinMale l;
	LapinFemelle l2;
	while(i < temps_ && l.getAge() < l.getDureeVie())
	{
		std::cout << l.toString() << std::endl;
		std::cout << l2.toString() << std::endl;
		
		l.incrementAge();
		l2.incrementAge();
		
		l.accoupler(l2);
		
		++i;
	}
}

float Modele::randomFloat(float a, float b) {	
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}


int  Modele::rejectionNormalLaw(int mean , int  stdDev)
{
	double   u, v, s, nb1 , nb2;
	
	do
	{
		u = randomFloat (-1.0, 1.0);
		v = randomFloat (-1.0, 1.0);
		s = u * u + v * v;
	}while( (s >= 1.0) || (s == 0.0) );
		
	s = sqrt (-2.0 * log(s) / s);
	nb1 = mean + stdDev * v * s;	
	nb2 = mean + stdDev * u * s;
		
	int choix = rand() % 2;
	int nb = (choix >= 1 ? nb1 : nb2);
	
	return (choix >= 1 ? nb1 : nb2);
}

int Modele::histogram(int nbClasses, float * pourcentages)
{
	int res = -1;
	if(nbClasses > 0)
	{		
		float nb = randomFloat(0,1);
		int i = 0, fin = 0;
		float cumul = 0;
		
		while(i < nbClasses && !fin)
		{			
			
			cumul += pourcentages[i];
			if(nb < cumul)
			{
				res = i; //indice d'un tableau[i] = classe
				fin = 1;
			}
			++i;
		}
	}
	return res;
	
}












