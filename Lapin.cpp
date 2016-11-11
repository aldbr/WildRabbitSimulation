#include "Lapin.hpp"
#include "Modele.hpp"
#include <sstream>
#include <iostream>

/*!
 * \brief Constructeur de Lapin.
 * \par Principe :
 * Initialise l'âge à 0
 * Calcul aléatoirement une durée de vie normale et une durée de vie de survie
 * Durée de vie du lapin devient la durée minimum entre la normale et la survie
 */
Lapin::Lapin() : age_(0)
{
	int dureeNormal = Modele::rejectionNormalLaw(3,2) * 12; //la méthode gaussienne est peut être inadapté ici : beaucoup meurent très jeune dans la nature
	
	float pourcentageSurvie [] = {0.8, 0.1, 0.05, 0.025, 0.0125, 0.00625, 0.003125, 0.0015625, 0.00078125, 0.000390625, 0.000195313, 0.000097656, 0.000048828, 0.000024414, 0.00};
	int dureeSurvie = (Modele::histogram(15, pourcentageSurvie))*12;
	
	dureeVie_ = (dureeNormal < dureeSurvie ? dureeNormal : dureeSurvie);
}

/*!
 * \brief Getter de l'âge du lapin.
 * \return entier correspondant à l'âge du lapin
 */
int Lapin::getAge()
{ 
	return age_;
}

/*!
 * \brief Incrémente l'âge du lapin.
 */
void Lapin::incrementAge()
{
	++age_;
}
	
/*!
 * \brief Getter de la durée de vie du lapin.
 * \return entier correspondant à la durée de vie du lapin
 */
int Lapin::getDureeVie()
{
	return dureeVie_;
}

/*!
 * \brief Setter de la durée de vie du lapin.
 * \par Principe :
 * Si minAn est entre 0 et 15 et que la durée de vie courante du lapin est à 0, alors on la passe à minAn en mois
 * \param minAn l'âge minimale en année que doit prendre le lapin
 */
void Lapin::setDureeVie(int minAn)
{
	if(minAn >= 0 && minAn <= 15)
	{
		if(dureeVie_ == 0)
			dureeVie_ = minAn*12 ;
	}
}


