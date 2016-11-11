#include "Modele.hpp"
#include "LapinMale.hpp"
#include "LapinFemelle.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "LapinMale.hpp"
#include "LapinFemelle.hpp"
#include <typeinfo>


Modele::Modele(int temps) : temps_(temps)
{
	std::cout << "constructeur" << std::endl;
	srand(time(NULL));
	lapinsMale_ = new LapinMale[TMAX];
	lapinsFemelle_ = new LapinFemelle[TMAX];
}

Modele::~Modele()
{
	std::cout << "destructeur" << std::endl;
	delete [] lapinsMale_;
	delete [] lapinsFemelle_;
	
	lapinsMortsMale_.clear();
	lapinsMortsFemelle_.clear();
	tLogiqueFemelle = 1;
	tLogiqueMale = 1;
}

void Modele::verifierEtatLapins()
{
	int cpt = 0;
	for (int i=0; i<tLogiqueMale;++i)
		if(lapinsMale_[i].getAge() == lapinsMale_[i].getDureeVie())
		{
			lapinsMortsMale_.push_front(&lapinsMale_[i]);
			++cpt;
		}
	
	for (int i=0; i<tLogiqueFemelle;++i)
		if(lapinsFemelle_[i].getAge() == lapinsFemelle_[i].getDureeVie())
		{
			lapinsMortsFemelle_.push_front(&lapinsFemelle_[i]);
			++cpt;
		}
	std::cout << "Mort = " << cpt << std::endl;
}

void Modele::detruireModele()
{
	while(!lapinsMortsMale_.empty())
	{
		delete lapinsMortsMale_.front();
		lapinsMortsMale_.pop_front();
	}
	while(!lapinsMortsFemelle_.empty())
	{
		delete lapinsMortsFemelle_.front();
		lapinsMortsFemelle_.pop_front();
	}
}

void Modele::accouplement()
{
	int j=0;
	bool fin = false;
		
	while(j<tLogiqueMale && !fin)
	{
		if(lapinsMale_[j].getAge() < lapinsMale_[j].getDureeVie())
		{
			fin = true;
		} 
		else 
		{
			j++;
		}
	}
	if(j != tLogiqueMale)
	{
		for(int i=0; i<tLogiqueFemelle; ++i)
		{
			if(lapinsFemelle_[i].getAge() < lapinsFemelle_[i].getDureeVie())
				lapinsMale_[j].accoupler(lapinsFemelle_[i]);
		}
	}	
}

void Modele::incrementerAge()
{
	for(int i=0;i<tLogiqueMale;++i)
	{
		lapinsMale_[i].incrementAge();
	}	
	for(int i=0;i<tLogiqueFemelle;++i)
	{
		lapinsFemelle_[i].incrementAge();
	}	
}

void Modele::naissance()
{
	int cpt = 0;
	for(int i=0;i<tLogiqueFemelle;++i)
	{
		cpt += lapinsFemelle_[i].donnerNaissance();
	}
}


int Modele::initializeSimulation()
{
	int i = 0;
		
	std::ofstream fichier("simulation.csv");
	if (!fichier.fail()) {
				
		lapinsMale_[0].setDureeVie(9);
		lapinsFemelle_[0].setDureeVie(9);
		
		while(i < temps_)
		{		
			int sizeM = tLogiqueMale - lapinsMortsMale_.size();
			int sizeF = tLogiqueFemelle - lapinsMortsFemelle_.size();
			
			//std::cout << toString(i, sizeF+sizeM); 
			std::cout << i << "; " << sizeM << "; " << sizeF << "; " << sizeF+sizeM << std::endl;
			fichier << i << "; " << sizeM << "; " << sizeF << "; " << sizeF+sizeM << std::endl;
			
			naissance();			
			verifierEtatLapins();
			accouplement();
						
			incrementerAge();
			++i;	
		}
		fichier.close();
	}
	int sizeM = tLogiqueMale - lapinsMortsMale_.size();
	int sizeF = tLogiqueFemelle - lapinsMortsFemelle_.size();
	//std::cout << toString(i, sizeF+sizeM); 
	std::cout << i << "; " << sizeM << "; " << sizeF << "; " << sizeF+sizeM << std::endl;
	fichier << i << "; " << sizeM << "; " << sizeF << "; " << sizeF+sizeM << std::endl;
	std::cout << "Nombre de males : "<< sizeM << std::endl;
	std::cout << "Nombre de femelles : "<< sizeF << std::endl;
	
	return sizeF+sizeM;
	
	
	//detruireModele();
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

std::string Modele::toString(int i, int nb)
{
	std::ostringstream oss;
	oss << "Mois " <<  i << " : " << nb << std::endl;
	for (int i=0;i<tLogiqueMale;++i)
	{
		if(lapinsMale_[i].getAge() <= lapinsMale_[i].getDureeVie())
		{
			oss << i << " - " << lapinsMale_[i].toString();
		}
	}
	for (int i=0;i<tLogiqueFemelle;++i)
	{
		if(lapinsFemelle_[i].getAge() <= lapinsFemelle_[i].getDureeVie())
		{
			oss << i << " - " << lapinsFemelle_[i].toString();
		}		
	}
	return oss.str();
}

int Modele::getTMax()
{
	return TMAX;
}

int Modele::getTLogiqueMale()
{
	return tLogiqueMale;
}

void Modele::setTLogiqueMale(int nb)
{
	tLogiqueMale += nb;
}

int Modele::getTLogiqueFemelle()
{
	return tLogiqueFemelle;
}

void Modele::setTLogiqueFemelle(int nb)
{
	tLogiqueFemelle += nb;
}

std::list<LapinMale *> Modele::lapinsMortsMale_;
std::list<LapinFemelle *> Modele::lapinsMortsFemelle_;
int Modele::tLogiqueMale = 1;
int Modele::tLogiqueFemelle = 1;













