#include "bouton.h"
#include <iostream>
#include <cstdlib>

Bouton::Bouton() : bio(nullptr), bshmid(0)
{
}

void Bouton::initialiser()
{
    // Accès à la mémoire partagée contenant les boutons
    bio = acces_memoire(&bshmid);

    if (bio == nullptr)
    {
        std::cerr << "Erreur : pas de memoire partagee" << std::endl;
        std::exit(1);
    }

    // Initialisation des états des boutons
    bio->bouton_charge = 0;
    bio->bouton_stop = 0;
}

int Bouton::lireBoutonCharge() const
{
    if (bio == nullptr)
    {
        return 0;
    }
    return bio->bouton_charge;
}

int Bouton::lireBoutonStop() const
{
    if (bio == nullptr)
    {
        return 0;
    }
    return bio->bouton_stop;
}