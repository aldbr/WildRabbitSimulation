#ifndef LAPINFEM_HPP
#define LAPINFEM_HPP

#include "Lapin.hpp"

/*!
 * \brief Classe traitant les lapins femelles.
 * \par Principe :
 * Elle contient les fonctions gèrant les actions du lapin femelle, elle dérive de la classe Lapin
 */
class LapinFemelle : public Lapin
{
        /*!
         * \brief booléen pour savoir si la femelle est en gestation ou non.
         */
        bool enGestation_;
        /*!
         * \brief nombre de portées courant de la femelle.
         */
		short int nbPortees_;
        /*!
         * \brief nombre de portées maximal de la femelle pour une année de sa vie.
         */
		short int nbPorteesMax_;
	
	public :
        /*!
         * \brief Constructeur de LapinFemelle.
         */
        LapinFemelle();
	
        /*!
         * \brief Setter du booléen de gestation.
         */
        void setGestation();
	

        /*!
         * \brief Getter du nombre de portées.
         * \return entier correspondant au nombre de portées de la lapine
         */
		int getNbPortees();
        /*!
         * \brief Incrément du nombre de portées courant.
         */
		void incrementNbPortees();
	
        /*!
         * \brief Getter du nombre de portées maximal.
         * \return le nombre de portées maximal de la lapine pour une année de sa vie
         */
		int getNbPorteesMax();

        /*!
         * \brief Setter du nombre de portées maximal.
         */
		void setNbPorteesMax();
	
        /*!
         * \brief Réponse à la question de la maturité du lapin.
         * \return booléen représentant la réponse à sa maturité
         */
		void incrementAge();
        /*!
         * \brief Incrément de l'âge de la lapine.
         */
		bool isMature();
	

        /*!
         * \brief Donne naissance aux lapereaux.
         * \return entier représentant le nombre de nouveaux nés
         */
		int donnerNaissance();
	
        /*!
         * \brief Affichage du lapin femelle.
         * \return chaîne de caractères représentant un lapin femelle
         */
		std::string toString();
	
        /*!
         * \brief Réinitialise la durée de vie et l'âge d'un lapin ainsi que son nombre de portées.
         */
		void reinit();	
};

#endif

