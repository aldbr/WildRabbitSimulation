#include "Lapin.hpp"
#include "Modele.hpp"
#include <ctime>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "LapinMale.hpp"
#include "LapinFemelle.hpp"

using namespace std;

void simuDixAns()
{
	printf("simulation sur une période de 10 ans\n");
	Modele *m = new Modele(120);
	m->initializeSimulation("simulation10ans3.csv");
	delete m;
	Modele *m2 = new Modele(120);
	m->initializeSimulation("simulation10ans4.csv");
	delete m2;
}

float getValTab(int n)
{
	float o = 0;
	float tab [120] = {0.006194, 0.108, 0.296, 0.519, 0.756, 1.002, 1.252, 1.502, 1.759, 2.015, 2.271, 2.527, 2.786, 3.043, 3.303, 3.560, 3.818, 4.078, 4.337, 
		4.596, 4.854, 5.115, 5.373, 5.634, 5.891, 6.151, 6.412, 6.676, 6.934, 7.195, 9.973, 20.0, 30.609};
	
	if(n < 40)
	{
		o = tab[n-1];
	}
	else 
	{	if(n >= 40 && n < 80)
		{
			o = tab[30];
		}
		else 
		{
			if(n >= 80 && n <120)
			{
				o = tab[31];
			}
			else 
			{
				if(n == 120)
				{
					o = tab[32];
				}
				else 
				{
					o = n*0.260;
				}
			}
		}
	}
	return o;
}

void calculMoyenneRayon()
{
	int somme = 0, moyenne, tab[100];
	float sn, r;
	
	std::ofstream fichier("resultat.csv");
	if (!fichier.fail()) {			
		fichier << "r,res" << std::endl;
		for(int i=0; i<100; ++i)
		{
			Modele m(60);
			tab[i] = m.initializeSimulation("lastSimu.csv");
			fichier << i << "," << tab[i] << std::endl;
			somme += tab[i];
		}
		fichier.close();
	}
	moyenne = somme/100;
	std::cout << "moyenne :" << moyenne << std::endl;
	
	somme = 0;
	for(int i=0; i<100; ++i)
	{
		somme += pow(tab[i] - moyenne, 2);
	}
	sn = (float)somme/(float)(99);
	std::cout << "estimateur sans biais :" << sn << std::endl;
	
	r = 1.990 * sqrt(sn/100);
	std::cout << "rayon de confiance :" << r << std::endl;
}

int main(void)
{
	srand(364);
	

	std::cout << "Prévision du nombre de réplication minimale à réaliser pour obtenir le même résultat : " << std::endl;
	std::cout << "Précision à 0.300203" << std::endl;
	
	
	bool fin = 0;
	int n = 3, m, moyenne,  tab[1000], sommeMoy=0, sommeVar=0, nbRepPlus;
	float p = 0.300203, sn, r, f=0.5, o;
	
	//moyenne
	for(int i=0; i<n; ++i)
	{
		Modele m(60);
		tab[i] = m.initializeSimulation("lastSimu.csv");
		sommeMoy += tab[i];
	}
	moyenne = sommeMoy/n;
	std::cout << "moyenne :" << moyenne << std::endl;
	
	//sn
	for(int i=0; i<n; ++i)
	{
		sommeVar += pow(tab[i] - moyenne, 2);
	}
	sn = (float)sommeVar/(float)(n-1);
	std::cout << "estimateur sans biais :" << sn << std::endl;
	
	//rayon
	r = 2 * sqrt(sn/100);
	std::cout << "rayon de confiance :" << r << std::endl;
	
	
	while(!fin)
	{
		o = getValTab(n);
		if(o > sn/(pow(p*moyenne,2)))
		{
			fin = 1;
		}
		std::cout << "o : " << o << " sn/..." << sn/(pow(p*moyenne,2)) << std::endl;
		std::cin.get();
		
		m = n;
		while(o < sn/(pow(p*moyenne,2)) && !fin)
		{
			++m;
			o = getValTab(m);
			std::cout << "m :" << m << std::endl;
		}
		std::cin.get();
		nbRepPlus=f*(m-n);
		std::cout << "nb rep en plus : " << nbRepPlus << std::endl;
		
		//moyenne
		for(int i=0; i<nbRepPlus; ++i)
		{
			Modele m(60);
			tab[i+n] = m.initializeSimulation("lastSimu.csv");
			sommeMoy += tab[i+n];
		}
		moyenne = sommeMoy/(n+nbRepPlus);
		std::cout << "moyenne :" << moyenne << std::endl;
		
		
		//sn
		for(int i=0; i<nbRepPlus; ++i)
		{
			sommeVar += pow(tab[i+n] - moyenne, 2);
		}
		sn = (float)sommeVar/(float)((n+nbRepPlus)-1);
		std::cout << "estimateur sans biais :" << sn << std::endl;
		
		//rayon
		r = 2 * sqrt(sn/100);
		std::cout << "rayon de confiance :" << r << std::endl;
		
		n = n+nbRepPlus;
		std::cin.get();
	}
	std::cout << "moyenne :" << moyenne << std::endl;
	std::cout << "estimateur sans biais :" << sn << std::endl;
	std::cout << "rayon de confiance :" << r << std::endl;
	std::cout << "n :" << n << std::endl;
	
	return 0;
}
