#include "LapinMale.hpp"
#include "Modele.hpp"


bool LapinMale::isMature()
{
	return (age_ < 4 ? false : true);
}

void LapinMale::accoupler(LapinFemelle& f)
{
	if(isMature())
		f.setGestation();
}

std::string LapinMale::toString()
{
	std::ostringstream oss;
	oss << "Male :" << std::endl;
	oss << (isMature() ? "Mature " : "") << "Duree de vie : " << dureeVie_ << " Age : " << age_ << std::endl;
	oss << std::endl;
	return oss.str();
}

void LapinMale::reinit()
{
	age_ = 0;
	int dureeNormal = Modele::rejectionNormalLaw(3,2) * 12; //la méthode gaussienne est peut être inadapté ici : beaucoup meurent très jeune dans la nature
	
	float pourcentageSurvie [] = {0.8, 0.1, 0.05, 0.025, 0.0125, 0.00625, 0.003125, 0.0015625, 0.00078125, 0.000390625, 0.000195313, 0.000097656, 0.000048828, 0.000024414, 0.00};
	int dureeSurvie = (Modele::histogram(15, pourcentageSurvie))*12;
	
	dureeVie_ = (dureeNormal < dureeSurvie ? dureeNormal : dureeSurvie);
}
