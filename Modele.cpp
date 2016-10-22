#include "Modele.hpp"
#include "LapinMale.hpp"
#include "LapinFemelle.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include <typeinfo>

Modele::Modele(int temps) : temps_(temps)
{
	srand(time(NULL));
	
}


void Modele::verifierEtatLapins()
{
	
	for (std::list<LapinMale *>::iterator it=lapinsMale_.begin(); it != lapinsMale_.end(); ++it)
		if((*it)->getAge() == (*it)->getDureeVie())
		{
			delete (*it);
			lapinsMale_.erase(it);
		}
	
	for (std::list<LapinFemelle *>::iterator it=lapinsFemelle_.begin(); it != lapinsFemelle_.end(); ++it)
		if((*it)->getAge() == (*it)->getDureeVie())
		{
			delete (*it);
			lapinsFemelle_.erase(it);
		}
		
}

void Modele::detruireModele()
{
	while(!lapinsFemelle_.empty())
	{
		delete lapinsFemelle_.front();
		lapinsFemelle_.pop_front();
	}
	while(!lapinsMale_.empty())
	{
		delete lapinsMale_.front();
		lapinsMale_.pop_front();
	}	
}

void Modele::accouplement()
{
	for (std::list<LapinFemelle *>::iterator it=lapinsFemelle_.begin(); it != lapinsFemelle_.end(); ++it)
	{
		lapinsMale_.back()->accoupler(**it);
	}	
}

void Modele::incrementerAge()
{
	for (std::list<LapinFemelle *>::iterator it=lapinsFemelle_.begin(); it != lapinsFemelle_.end(); ++it)
	{
		(*it)->incrementAge();
	}	
	for (std::list<LapinMale *>::iterator it=lapinsMale_.begin(); it != lapinsMale_.end(); ++it)
	{
		(*it)->incrementAge();
	}	
}

void Modele::naissance()
{
	for (std::list<LapinFemelle *>::iterator it=lapinsFemelle_.begin(); it != lapinsFemelle_.end(); ++it)
	{
		(*it)->donnerNaissance();
	}	
}


void Modele::initializeSimulation()
{
	int i = 0;
		
	lapinsMale_.push_front(new LapinMale);
	lapinsFemelle_.push_front(new LapinFemelle);
	
	while(i < temps_)
	{		
		accouplement();
		
		std::cout << toString(i);
		
		incrementerAge();
		
		naissance();
		
		//verifierEtatLapins();
		
		++i;
	}
	detruireModele();
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

std::string Modele::toString(int i)
{
	std::ostringstream oss;
	oss << "Mois " <<  i << " : " << lapinsFemelle_.size() + lapinsMale_.size() << std::endl;
	for (std::list<LapinMale *>::iterator it=lapinsMale_.begin(); it != lapinsMale_.end(); ++it)
		oss << (*it)->toString();
	for (std::list<LapinFemelle *>::iterator it=lapinsFemelle_.begin(); it != lapinsFemelle_.end(); ++it)
		oss << (*it)->toString();
	return oss.str();
}

std::list<LapinMale *> Modele::lapinsMale_;
std::list<LapinFemelle *> Modele::lapinsFemelle_;








/* si on avait eu une liste regroupant lapin male et femelle : algos de recherche du type dans la liste
const LapinMale* Modele::rechercheMale()
{
	LapinMale  *l = 0;
	for (std::list<Lapin *>::iterator it=lapins_.begin(); it != lapins_.end(); ++it)
		if(typeid(**it).name() == "9LapinMale")
		{
			l = (*it); 
		}
	return l;
		
}

const LapinFemelle* Modele::rechercheFemelle()
{
	LapinFemelle  *l = 0;
	for (std::list<Lapin *>::iterator it=lapins_.begin(); it != lapins_.end(); ++it)
		if(typeid(**it).name() == "12LapinFemelle")
		{
			l = (*it); 
		}
	return l;	
}
*/












