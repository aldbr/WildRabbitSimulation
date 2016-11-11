#include "Lapin.hpp"
#include "Modele.hpp"
#include <sstream>
#include <iostream>

Lapin::Lapin() : age_(0)
{
	int dureeNormal = Modele::rejectionNormalLaw(3,2) * 12; //la méthode gaussienne est peut être inadapté ici : beaucoup meurent très jeune dans la nature
	
	float pourcentageSurvie [] = {0.8, 0.1, 0.05, 0.025, 0.0125, 0.00625, 0.003125, 0.0015625, 0.00078125, 0.000390625, 0.000195313, 0.000097656, 0.000048828, 0.000024414, 0.00};
	int dureeSurvie = (Modele::histogram(15, pourcentageSurvie))*12;
	
	dureeVie_ = (dureeNormal < dureeSurvie ? dureeNormal : dureeSurvie);
}

int Lapin::getAge()
{ 
	return age_;
}

void Lapin::incrementAge()
{
	++age_;
}
	
int Lapin::getDureeVie()
{
	return dureeVie_;
}

void Lapin::setDureeVie(int minAn)
{
	if(minAn >= 0 && minAn <= 15)
	{
		if(dureeVie_ == 0)
			dureeVie_ = minAn*12 ;
	}
}


