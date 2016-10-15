#include "Lapin.hpp"
#include "Modele.hpp"
#include <sstream>


Lapin::Lapin() : age_(0)
{
	dureeVie_ = Modele::rejectionNormalLaw(9,2) * 12; //la méthode gaussienne est peut être inadapté ici : beaucoup meurent très jeune dans la nature
	
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


