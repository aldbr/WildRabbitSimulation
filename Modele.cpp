#include "Modele.hpp"
#include "LapinMale.hpp"
#include "LapinFemelle.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "LapinMale.hpp"
#include "LapinFemelle.hpp"
#include <typeinfo>


/*!
 * \brief Constructeur de Modèle.
 * \par Principe :
 * Initialisation des tableaux de lapins mâles et femelles
 * \param temps
 */
Modele::Modele(int temps) : temps_(temps)
{
	lapinsMale_ = new LapinMale[TMAX];
	lapinsFemelle_ = new LapinFemelle[TMAX];
}

/*!
 * \brief Destructeur du modèle.
 * \par Principe :
 * Destruction des tableaux de mâles et femelles
 * Réinitialisation à 0 des listes de lapins mâles et femelles morts
 * Réinitialisation de la taille logique des tableaux des lapins
 */
Modele::~Modele()
{
	delete [] lapinsMale_;
	delete [] lapinsFemelle_;
	
	lapinsMortsMale_.clear();
	lapinsMortsFemelle_.clear();
	tLogiqueFemelle = 1;
	tLogiqueMale = 1;
}

/*!
 * \brief Vérification de la survie des lapins.
 * \par Principe :
 * Parcours des deux tableaux de lapins
 * Si l'age du lapin courant est égal à sa durée de vie alors
 *  Adjonction de ce lapin dans la liste de lapins morts
 */
int Modele::verifierEtatLapins()
{
	int cpt = 0;
	for (int i=0; i<tLogiqueMale;++i)
	{
		if(lapinsMale_[i].getAge() == lapinsMale_[i].getDureeVie())
		{
			lapinsMortsMale_.push_front(&lapinsMale_[i]);
			++cpt;
		}
	}
	for (int i=0; i<tLogiqueFemelle;++i)
	{
		if(lapinsFemelle_[i].getAge() == lapinsFemelle_[i].getDureeVie())
		{
			lapinsMortsFemelle_.push_front(&lapinsFemelle_[i]);
			++cpt;
		}
	}
	return cpt;
}

/*!
 * \brief Accouplement des mâles avec toutes les femelles disponibles.
 * \par Principe :
 * Recherche d'un lapin male vivant et mature
 * Si ce lapin à été trouvé alors
 *  Pour tous les lapins femelles vivante faire
 *      le lapin mâle désigné s'accouple avec la femelle courante
 */
void Modele::accouplement()
{
	int j=0;
	bool fin = false;
		
	while(j<tLogiqueMale && !fin)
	{
		if(lapinsMale_[j].getAge() < lapinsMale_[j].getDureeVie() && lapinsMale_[j].isMature())
		{
			fin = true;
		} 
		else 
		{
			j++;
		}
	}
	if(j != tLogiqueMale)
	{
		for(int i=0; i<tLogiqueFemelle; ++i)
		{
			if(lapinsFemelle_[i].getAge() < lapinsFemelle_[i].getDureeVie())
				lapinsMale_[j].accoupler(lapinsFemelle_[i]);
		}
	}	
}

/*!
 * \brief Incrément de l'âge de tous les lapins.
 * \par Principe :
 * Parcours des deux tableaux de lapins jusqu'au tailles logiques
 *  Incrément de l'âge du lapin courant
 */
void Modele::incrementerAge()
{
	for(int i=0;i<tLogiqueMale;++i)
	{
		lapinsMale_[i].incrementAge();
	}	
	for(int i=0;i<tLogiqueFemelle;++i)
	{
		lapinsFemelle_[i].incrementAge();
	}	
}

/*!
 * \brief Naissance des lapereaux par toutes les femelles en gestation.
 * \par Principe :
 * Parcours du tableau de lapins femelles
 *  La lapine courant donne naissance si elle le peut
 */
int Modele::naissance()
{
	int cpt = 0;
	for(int i=0;i<tLogiqueFemelle;++i)
	{
		cpt += lapinsFemelle_[i].donnerNaissance();
	}
	return cpt;
}

/*!
 * \brief Lancement de la simulation.
 * \par Principe :
 * Initialisation de la durée de vie des deux premiers lapins à 9 ans (l'âge moyen)
 * Tant que le temps n'est pas arrivé à terme faire
 *  Ecriture du nombre de lapins mâles, femelles et total dans un fichier simulation.csv
 *  Naissance des lapereaux
 *  Vérification de l'état des lapins
 *  Accouplement des lapins
 *  Incrément de l'âge et du mois
 * Fait
 * Ecriture du dernier nombre de lapins dans le fichier csv
 * \return entier représentant le nombre de lapins mâles et femelles vivant
 */
int Modele::initializeSimulation()
{
	int i = 0,
		cptNaissances = 0,
		cptDeces = 0,
		sizeM = 0,
		sizeF = 0,
		totalLapins = 0,
		malesMatures = 0,
		femellesMatures = 0,
		totalLapinsMatures = 0;
		
		
	std::ofstream fichier("simulation.csv");
	if (!fichier.fail()) {
				
		lapinsMale_[0].setDureeVie(9);
		lapinsFemelle_[0].setDureeVie(9);
		fichier << "Mois;" << "Nb males début du mois;" << "Nb femelles début du mois;" << "Total lapins début du mois;" << "Nb lapins matures;" << "Nb lapereaux;" << "Naissances;" << "Décès;" <<std::endl;
		
		while(i < temps_)
		{		
			sizeM = tLogiqueMale - lapinsMortsMale_.size();
			sizeF = tLogiqueFemelle - lapinsMortsFemelle_.size();
			totalLapins = sizeM+sizeF;
			
			malesMatures = getNbMalesMatures();
			femellesMatures = getNbFemellesMatures();
			totalLapinsMatures = malesMatures + femellesMatures;
			
			
			//std::cout << toString(i, sizeF+sizeM); 
			std::cout << "Mois " << i << " : " << std::endl;
			std::cout << sizeM << " male(s), " << sizeF << " femelle(s),  total = " << totalLapins << " lapin(s)" << std::endl;
			std::cout << "    (" << malesMatures << "|" <<femellesMatures << ") lapin(s) mature(s), (" << sizeM - malesMatures << "|" << sizeF - femellesMatures << ") lapereaux" << std::endl;			
			fichier << i << ";" << sizeM << ";" << sizeF << ";" << totalLapins << ";" << totalLapinsMatures << ";" << totalLapins - totalLapinsMatures << ";";
			
			//Evolution de l'environnement
			cptNaissances = naissance();			
			cptDeces = verifierEtatLapins();
			accouplement();						
			incrementerAge();
						
			std::cout << "    " << cptNaissances << " lapins sont nés" << std::endl;
			std::cout << "    " << cptDeces << " lapin(s) mort(s)" << std::endl;		
			std::cout << "-----------------------------------------------------"  << std::endl;
			fichier << cptNaissances << ";" << cptDeces << ";" << std::endl;
			
			++i;	
		}
		fichier.close();
	}
	sizeM = tLogiqueMale - lapinsMortsMale_.size();
	sizeF = tLogiqueFemelle - lapinsMortsFemelle_.size();
	//std::cout << toString(i, sizeF+sizeM); 
	//std::cout << i << "; " << sizeM << "; " << sizeF << "; " << sizeF+sizeM << std::endl;
	fichier << i << "; " << sizeM << "; " << sizeF << "; " << sizeF+sizeM << std::endl;
	
	return sizeF+sizeM;
}

/*!
 * \brief Génération uniforme d'un nombre pseudo-aléatoire entre deux bornes.
 * \par Principe :
 * Récupération d’un nombre pseudo-aléatoire à l’aide de rand()
 * Division par le randmax pour le ramener entre 0 et 1
 * Multiplication par la longueur entre la borne a et b
 * \param a borne minimal
 * \param b borne maximal
 * \return réel représentant un nombre aléatoire
 */
float Modele::randomFloat(float a, float b) {	
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

/*!
 * \brief Génération d'un nombre aléatoire suivant une distribution exponentielle négative.
 * \param mean moyenne de la loi exponentielle
 * \param stdDev ecart type de la moyenne
 * \return réel représentant un nombre aléatoire
 */
int Modele::rejectionNormalLaw(int mean , int  stdDev)
{
	double   u, v, s, nb1 , nb2;
	
	do
	{
		u = randomFloat (-1.0, 1.0);
		v = randomFloat (-1.0, 1.0);
		s = u * u + v * v;
	}while( (s >= 1.0) || (s == 0.0) );
		
	s = sqrt (-2.0 * log(s) / s);
	nb1 = mean + stdDev * v * s;	
	nb2 = mean + stdDev * u * s;
		
	int choix = rand() % 2;
	
	return (choix >= 1 ? nb1 : nb2);
}

/*!
 * \brief Génération d'un nombre aléatoire suivant une loi discrète.
 * \par Principe :
 * Tirage d’un nombre pseudo-aléatoire entre 0 et 1
 * Initialisation d’un cumul de pourcentage à 0
 * Tant que on a pas trouvé la classe du nombre faire
 * Ajout d’un pourcentage au cumul selon le nombre d’observations / la somme
 * Si le nombre est inférieur au cumul de pourcentages alors
 * Stockage de la classe résultat
 * Fsi
 * \param nbClasses entier représentant le nombre de classes utilisés
 * \param pourcentages tableaux de réels représentant des pourcentages des classes
 * \return réel représentant la classe résultat
 */
int Modele::histogram(int nbClasses, float * pourcentages)
{
	int res = -1;
	if(nbClasses > 0)
	{		
		float nb = randomFloat(0,1);
		int i = 0, fin = 0;
		float cumul = 0;
		
		while(i < nbClasses && !fin)
		{			
			
			cumul += pourcentages[i];
			if(nb < cumul)
			{
				res = i; //indice d'un tableau[i] = classe
				fin = 1;
			}
			++i;
		}
	}
	return res;
	
}

/*!
 * \brief Affichage du modèle.
 * \par Principe :
 * Parcours des deux tableaux de lapins
 *  Si le lapin sont vivants alors on affiche les informations du lapin courant
 * \param i entier représentant le mois courant
 * \param nb entier représentant le nombre de lapins total
 * \return chaîne de caractères représentant le modèle.
 */
std::string Modele::toString(int i, int nb)
{
	std::ostringstream oss;
	oss << "Mois " <<  i << " : " << nb << std::endl;
	for (int i=0;i<tLogiqueMale;++i)
	{
		if(lapinsMale_[i].getAge() <= lapinsMale_[i].getDureeVie())
		{
			oss << i << " - " << lapinsMale_[i].toString();
		}
	}
	for (int i=0;i<tLogiqueFemelle;++i)
	{
		if(lapinsFemelle_[i].getAge() <= lapinsFemelle_[i].getDureeVie())
		{
			oss << i << " - " << lapinsFemelle_[i].toString();
		}		
	}
	return oss.str();
}

/*!
 * \brief Getter de la taille physique des tableaux de lapins.
 * \return entier représentant la taille maximal des tableaux
 */
int Modele::getTMax()
{
	return TMAX;
}

/*!
 * \brief Getter de la taille logique du tableau de lapins mâles.
 * \return entier représentant la taille logique du tableau mâle
 */
int Modele::getTLogiqueMale()
{
	return tLogiqueMale;
}

/*!
 * \brief Setter de la taille logique du tableau de lapins mâles.
 * \param entier représentant un nombre de lapins en plus dans le tableau mâle
 */
void Modele::setTLogiqueMale(int nb)
{
	tLogiqueMale += nb;
}

/*!
 * \brief Getter de la taille logique du tableau de lapins femelles.
 * \return entier représentant la taille logique du tableau femelle
 */
int Modele::getTLogiqueFemelle()
{
	return tLogiqueFemelle;
}

/*!
 * \brief Setter de la taille logique du tableau de lapins femelles.
 * \param entier représentant un nombre de lapins en plus dans le tableau femelle
 */
void Modele::setTLogiqueFemelle(int nb)
{
	tLogiqueFemelle += nb;
}

/*!
 * \brief Getter du nombre de lapins mâles matures
 * \return entier représentant le nombre de lapins mâles matures
 */
int Modele::getNbMalesMatures()
{
	int cpt = 0;
	for(int i=0;i<tLogiqueMale;++i)
	{
		if(lapinsMale_[i].getAge() < lapinsMale_[i].getDureeVie() && lapinsMale_[i].isMature())
		{
			++cpt;
		}
	}
	return cpt;
}

/*!
 * \brief Getter du nombre de lapines matures
 * \return entier représentant le nombre de lapins matures
 */
int Modele::getNbFemellesMatures()
{
	int cpt = 0;
	for(int i=0;i<tLogiqueFemelle;++i)
	{
		if(lapinsFemelle_[i].getAge() < lapinsFemelle_[i].getDureeVie() && lapinsFemelle_[i].isMature())
		{
			++cpt;
		}
	}
	return cpt;
}


std::list<LapinMale *> Modele::lapinsMortsMale_;
std::list<LapinFemelle *> Modele::lapinsMortsFemelle_;

/*!
 * \brief Initialisation de la taille logique du tableau de lapins mâles
 */
int Modele::tLogiqueMale = 1;

/*!
 * \brief Initialisation de la taille logique du tableau de lapins femelles
 */
int Modele::tLogiqueFemelle = 1;













