#ifndef LAPINMALE_HPP
#define LAPINMALE_HPP

#include "Lapin.hpp"
#include "LapinFemelle.hpp"

class LapinMale : public Lapin
{
	public :
	bool isMature();
	
	void accoupler(LapinFemelle& f);
	
	std::string toString();
	
	void reinit();	

};

#endif
