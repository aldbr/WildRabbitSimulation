#ifndef LAPIN_HPP
#define LAPIN_HPP

#include <string>
#include <sstream>

class Lapin
{
	protected :
	short int age_;
	short int dureeVie_;
		
	public :
	Lapin(); //duree de vie init ici
	
	int getAge();
	void incrementAge();
	
	int getDureeVie();
	void setDureeVie(int minAn);
};

#endif
