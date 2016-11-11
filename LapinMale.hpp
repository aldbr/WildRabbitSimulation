#ifndef LAPINMALE_HPP
#define LAPINMALE_HPP

#include "Lapin.hpp"
#include "LapinFemelle.hpp"

/*!
 * \brief Classe traitant le lapin mâle.
 * \par Principe :
 * Elle contient les fonctions gèrant les actions du lapin mâle, elle dérive de la classe Lapin
 */
class LapinMale : public Lapin
{
	public :
        /*!
         * \brief Réponse à la question de la maturité du lapin.
         * \return booléen représentant la réponse à sa maturité
         */
	bool isMature();
	
        /*!
         * \brief Accouplement du lapin mâle avec une femelle.
         * \param f Lapine
         */
	void accoupler(LapinFemelle& f);
	
        /*!
         * \brief Affichage du lapin mâle.
         * \return chaîne de caractères représentant un lapin mâle
         */
	std::string toString();
	
        /*!
         * \brief Réinitialise la durée de vie et l'âge d'un lapin.
         */
	void reinit();	

};

#endif
