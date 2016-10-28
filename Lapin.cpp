#include "Lapin.hpp"
#include "Modele.hpp"
#include <sstream>


Lapin::Lapin() : age_(0)
{
	//dureeVie_ = Modele::rejectionNormalLaw(3,2) * 12; //la méthode gaussienne est peut être inadapté ici : beaucoup meurent très jeune dans la nature
	float pourcentageSurvie [] = {0.1, 0.075, 0.075, 0.025, 0.025, 0.05, 0.075, 0.125, 0.15, 0.125, 0.075, 0.05, 0.025, 0.025, 0.00};
	dureeVie_ = (Modele::histogram(15, pourcentageSurvie)+1)*12 ;

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


