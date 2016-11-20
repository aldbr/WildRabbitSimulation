#ifndef LAPIN_HPP
#define LAPIN_HPP

#include <string>
#include <sstream>

/*!
 * \brief Classe traitant le lapin de façon générale.
 */
class Lapin
{
	protected :

        /*!
         * \brief Age du lapin.
         */
        short int age_;
        /*!
         * \brief Durée de vie du lapin.
         */
		short int dureeVie_;
		
	public :
        /*!
         * \brief Constructeur de Lapin.
         */
        Lapin();
	
        /*!
         * \brief Getter de l'âge du lapin.
         * \return entier correspondant à l'âge du lapin
         */
		int getAge();
        /*!
         * \brief Incrémente l'âge du lapin.
         */
        void incrementAge();
	
        /*!
         * \brief Getter de la durée de vie du lapin.
         * \return entier correspondant à la durée de vie du lapin
         */
		int getDureeVie();
        /*!
         * \brief Setter de la durée de vie du lapin.
         * \param minAn l'âge minimale en année que doit prendre le lapin
         */
		void setDureeVie(int minAn);
};

#endif
