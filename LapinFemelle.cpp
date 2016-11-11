#include "LapinFemelle.hpp"
#include "LapinMale.hpp"
#include "Modele.hpp"
#include <iostream>

/*!
 * \brief Constructeur de LapinFemelle.
 * \par Principe :
 * Initialise un nombre de portées maximal pour sa première année
 */
LapinFemelle::LapinFemelle() : Lapin(), enGestation_(false), nbPortees_(0) 
{
	setNbPorteesMax();
}

/*!
 * \brief Setter du booléen de gestation.
 * \par Principe :
 * Si le lapin n'est pas en gestation, qu'il est mature et que son nombre de portées maximal n'est pas atteint alors
 *  Le lapin passe en gestation, son nombre de portées courant augmente
 */
void LapinFemelle::setGestation()
{
	if(!enGestation_ && nbPortees_ < nbPorteesMax_ && isMature())
	{
			enGestation_ = true;
			++nbPortees_;
	}
}
	
/*!
 * \brief Getter du nombre de portées.
 * \return entier correspondant au nombre de portées de la lapine
 */
int LapinFemelle::getNbPortees()
{
	return nbPortees_;
}

/*!
 * \brief Incrément du nombre de portées courant.
 */
void LapinFemelle::incrementNbPortees()
{
	++nbPortees_;
}
	
/*!
 * \brief Getter du nombre de portées maximal.
 * \return le nombre de portées maximal de la lapine pour une année de sa vie
 */
int LapinFemelle::getNbPorteesMax()
{
	return nbPorteesMax_;
}

/*!
 * \brief Setter du nombre de portées maximal.
 * \par Principe :
 * Tirage pseudo-aléatoire suivant une distribution discrète pour trouver un nombre de portées maximal
 * Initialisation du nombre de portées courant à 0
 */
void LapinFemelle::setNbPorteesMax()
{
	float pourcentageChancesPortees [] = {0.1, 0.1, 0.2, 0.2, 0.2, 0.1, 0.1};
	nbPorteesMax_ = Modele::histogram(7, pourcentageChancesPortees)+1;
	nbPortees_ = 0;
}

/*!
 * \brief Réponse à la question de la maturité du lapin.
 * \par Principe :
 * S'il a plus de 3 mois, il est mature, sinon il ne l'est pas
 * \return booléen représentant la réponse à sa maturité
 */
bool LapinFemelle::isMature()
{
	return (age_ < 3 ? false : true);
}

/*!
 * \brief Incrément de l'âge de la lapine.
 * \par Principe :
 * Incrément de l'âge
 * Si la lapine à pris 1 an alors
 *  On réinitialise le nombre de portées maximal
 */
void LapinFemelle::incrementAge()
{
	++age_;
	if((age_ % 12) == 0)
	{
                setNbPorteesMax();
	}
}

/*!
 * \brief Donne naissance aux lapereaux.
 * \par Principe :
 * Tirage aléatoire suivant une loi discrète d'un nombre d'enfants à avoir entre 3 et 6
 * Pour ce nombre de lapereaux faire
 *  Tirage aléatoire pour connaître le sexe du nouveau lapereau
 *  Selon le sexe faire
 *      Si la liste de lapins morts du même sexe n'est pas vide alors
 *          on prend un lapin mort et on le réinitialise
 *          on l'enlève de la liste de lapins morts
 *      Sinon Si on est pas à la limite de la taille physique du tableau de lapins du même sexe alors
 *          on augmente la taille logique du tableau
 *            Fsi
 *      Fsi
 * Fait
 * Fait
 * On indique que la période de gestation est terminé
 * \return entier représentant le nombre de nouveaux nés
 */
int LapinFemelle::donnerNaissance()
{
	int nbLapins = 0;
	
	if(enGestation_)
	{
		//float pourcentageChancesNbEnfants [] = {0.025, 0.025, 0.025, 0.2, 0.2, 0.2, 0.175, 0.025, 0.025, 0.025, 0.025, 0.025, 0.025};
		//nbLapins = Modele::histogram(13, pourcentageChancesNbEnfants);
		float pourcentageChancesNbEnfants [] = {0.25,0.25,0.25,0.25};		
		int nbLapins = Modele::histogram(4, pourcentageChancesNbEnfants)+3;
		float sexe;
		
		for(int i=0; i<nbLapins;++i)
		{
			sexe = Modele::randomFloat(0,2);
			if(sexe <= 1)
			{
				if(!Modele::lapinsMortsMale_.empty())
				{
					LapinMale * l = Modele::lapinsMortsMale_.front();
					l->reinit();
					Modele::lapinsMortsMale_.pop_front();
				}
				else 
				{
					if(Modele::getTMax() > Modele::getTLogiqueMale())
						Modele::setTLogiqueMale(1);
				}
			}
			else
			{
				if(!Modele::lapinsMortsFemelle_.empty())
				{
					LapinFemelle * l = Modele::lapinsMortsFemelle_.front();
					l->reinit();
					Modele::lapinsMortsFemelle_.pop_front();
				}
				else 
				{
					if(Modele::getTMax() > Modele::getTLogiqueFemelle())
						Modele::setTLogiqueFemelle(1);
				}
			}
		}
	}
        enGestation_ = 0;
	return nbLapins;
	
}

/*!
 * \brief Affichage du lapin femelle.
 * \return chaîne de caractères représentant un lapin femelle
 */
std::string LapinFemelle::toString()
{
	std::ostringstream oss;
	oss << "Femelle :" << std::endl;
	oss << (isMature() ? "Mature " : "") << "Duree de vie : " << dureeVie_ << " Age : " << age_ << std::endl;
	oss << "En gestation : " << enGestation_ << std::endl;
	oss << "Nombre de portées pour l'année : " << nbPorteesMax_ << std::endl;
	oss << "Nombre de portées effective sur l'année : " << nbPortees_ << std::endl;
	oss << std::endl;
	return oss.str();
}

/*!
 * \brief Réinitialise la durée de vie et l'âge d'un lapin ainsi que son nombre de portées.
 * \par Principe :
 * Initialise l'âge à 0, la gestation à false et le nombre de portées courante à 0
 * Calcul aléatoirement un nouveau nombre de portées pour l'année
 * Calcul aléatoirement une durée de vie normale et une durée de vie de survie
 * Durée de vie du lapin devient la durée minimum entre la normale et la survie
 */
void LapinFemelle::reinit()
{
	age_ = 0;
	enGestation_ = false;
	nbPortees_ = 0;
	setNbPorteesMax();
	
	int dureeNormal = Modele::rejectionNormalLaw(3,2) * 12; //la méthode gaussienne est peut être inadapté ici : beaucoup meurent très jeune dans la nature
	
	float pourcentageSurvie [] = {0.8, 0.1, 0.05, 0.025, 0.0125, 0.00625, 0.003125, 0.0015625, 0.00078125, 0.000390625, 0.000195313, 0.000097656, 0.000048828, 0.000024414, 0.00};
	int dureeSurvie = (Modele::histogram(15, pourcentageSurvie))*12;
	
	dureeVie_ = (dureeNormal < dureeSurvie ? dureeNormal : dureeSurvie);
}


