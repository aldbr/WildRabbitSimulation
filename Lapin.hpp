#ifndef LAPIN_HPP
#define LAPIN_HPP

#include <string>
#include <sstream>

class Lapin
{
	protected :
	int age_;
	int dureeVie_;
		
	public :
	Lapin(); //duree de vie init ici
	
	int getAge();
	void incrementAge();
	
	int getDureeVie();
	
	virtual bool isMature() = 0;
	
	virtual std::string toString() = 0;
};

#endif
