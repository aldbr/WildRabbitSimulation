#include "LapinMale.hpp"
#include "Modele.hpp"


/*!
 * \brief Réponse à la question de la maturité du lapin.
 * \par Principe :
 * S'il a plus de 4 mois, il est mature, sinon il ne l'est pas
 * \return booléen représentant la réponse à sa maturité
 */
bool LapinMale::isMature()
{
	return (age_ < 4 ? false : true);
}

/*!
 * \brief Accouplement du lapin mâle avec une femelle.
 * \par Principe :
 * Si le lapin est mature alors la femelle passe en gestation
 * \param f Lapine
 */
void LapinMale::accoupler(LapinFemelle& f)
{
	if(isMature())
		f.setGestation();
}

/*!
 * \brief Affichage du lapin mâle.
 * \return chaîne de caractères représentant un lapin mâle
 */
std::string LapinMale::toString()
{
	std::ostringstream oss;
	oss << "Male :" << std::endl;
	oss << (isMature() ? "Mature " : "") << "Duree de vie : " << dureeVie_ << " Age : " << age_ << std::endl;
	oss << std::endl;
	return oss.str();
}

/*!
 * \brief Réinitialise la durée de vie et l'âge d'un lapin.
 * \par Principe :
 * Initialise l'âge à 0
 * Calcul aléatoirement une durée de vie normale et une durée de vie de survie
 * Durée de vie du lapin devient la durée minimum entre la normale et la survie
 */
void LapinMale::reinit()
{
	age_ = 0;
	int dureeNormal = Modele::rejectionNormalLaw(3,2) * 12; //la méthode gaussienne est peut être inadapté ici : beaucoup meurent très jeune dans la nature
	
	float pourcentageSurvie [] = {0.8, 0.1, 0.05, 0.025, 0.0125, 0.00625, 0.003125, 0.0015625, 0.00078125, 0.000390625, 0.000195313, 0.000097656, 0.000048828, 0.000024414, 0.00};
	int dureeSurvie = (Modele::histogram(15, pourcentageSurvie))*12;
	
	dureeVie_ = (dureeNormal < dureeSurvie ? dureeNormal : dureeSurvie);
}
