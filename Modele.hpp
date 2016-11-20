#ifndef MODELE_HPP
#define MODELE_HPP

#include "LapinMale.hpp"
#include "LapinFemelle.hpp"

#include <list>
#include <string>

const int TMAX = 50000000;

/*!
 * \brief Classe traitant le modèle de simulation.
 * \par Principe :
 * Elle comprend :
 * -toutes les fonctions qui gèrent les lapins à grande echelle
 * -les fonctions qui gère l'aléatoire utilisé pour les attributs des lapins
 */
class Modele 
{

        /*!
         * \brief Temps que dure la simulation en mois.
         */
        int temps_;
	
        /*!
         * \brief Tableau de lapins mâles.
         */
		LapinMale *lapinsMale_;
        /*!
         * \brief Taille logique du tableau de mâles.
         */
		static int tLogiqueMale;
	
        /*!
         * \brief Tableau de lapins femelles.
         */
		LapinFemelle *lapinsFemelle_;
        /*!
         * \brief Taille logique du tableau de femelle.
         */
		static int tLogiqueFemelle;
	
	

        /*!
         * \brief Vérification de la survie des lapins.
         */
		int verifierEtatLapins();
        /*!
         * \brief Accouplement des mâles avec toutes les femelles disponibles.
         */
		void accouplement();
        /*!
         * \brief Incrément de l'âge de tous les lapins.
         */
		void incrementerAge();
        /*!
         * \brief Naissance des lapereaux par toutes les femelles en gestation.
         */
		int naissance();
	
	public :

        /*!
         * \brief Constructeur de Modèle.
         * \param temps
         */
        Modele(int temps);
        /*!
         * \brief Destructeur du modèle.
         */
        ~Modele();
        
        /*!
         * \brief Génération uniforme d'un nombre pseudo-aléatoire entre deux bornes.
         * \param a borne minimal
         * \param b borne maximal
         * \return réel représentant un nombre aléatoire
         */
        static float randomFloat(float a, float b);
        /*!
         * \brief Génération d'un nombre aléatoire suivant une distribution exponentielle négative.
         * \param mean moyenne de la loi exponentielle
         * \param stdDev ecart type de la moyenne
         * \return réel représentant un nombre aléatoire
         */
        static int rejectionNormalLaw(int mean , int stdDev);

        /*!
         * \brief Génération d'un nombre aléatoire suivant une loi discrète.
         * \param nbClasses entier représentant le nombre de classes utilisés
         * \param pourcentages tableaux de réels représentant des pourcentages des classes
         * \return réel représentant la classe résultat
         */
        static int histogram(int nbClasses, float * pourcentages);

        /*!
         * \brief Lancement de la simulation.
         * \return entier représentant le nombre de lapins mâles et femelles vivant
         */
        int initializeSimulation(std::string filename);

        /*!
         * \brief Affichage du modèle.
         * \param i entier représentant le mois courant
         * \param nb entier représentant le nombre de lapins total
         * \return chaîne de caractères représentant le modèle.
         */
        std::string toString(int i, int nb);
		
        /*!
         * \brief Getter de la taille physique des tableaux de lapins.
         * \return entier représentant la taille maximal des tableaux
         */
        static int getTMax();
		
        /*!
         * \brief Getter de la taille logique du tableau de lapins mâles.
         * \return entier représentant la taille logique du tableau mâle
         */
        static int getTLogiqueMale();
        /*!
         * \brief Setter de la taille logique du tableau de lapins mâles.
         * \param entier représentant un nombre de lapins en plus dans le tableau mâle
         */
        static void setTLogiqueMale(int nb);

        /*!
         * \brief Getter de la taille logique du tableau de lapins femelles.
         * \return entier représentant la taille logique du tableau femelle
         */
        static int getTLogiqueFemelle();
        /*!
         * \brief Setter de la taille logique du tableau de lapins femelles.
         * \param entier représentant un nombre de lapins en plus dans le tableau femelle
         */
        static void setTLogiqueFemelle(int nb);

		/*!
		 * \brief Getter du nombre de lapins mâles matures
		 * \return entier représentant le nombre de lapins mâles matures
		 */
		int getNbMalesMatures();
        
		 /*!
		 * \brief Getter du nombre de lapines matures
		 * \return entier représentant le nombre de lapins matures
		 */
        int getNbFemellesMatures();
        
        
        /*!
         * \brief Liste de pointeurs sur lapins mâles morts.
         */
        static std::list<LapinMale *> lapinsMortsMale_;
        /*!
         * \brief Liste de pointeurs sur lapins femelles mortes.
         */
        static std::list<LapinFemelle *> lapinsMortsFemelle_;
};

#endif
