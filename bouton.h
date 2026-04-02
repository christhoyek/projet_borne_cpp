#ifndef BOUTON_H
#define BOUTON_H

#include "donnees_borne.h"
#include "memoire_borne.h"
#include <cstdlib>
#include <unistd.h>

class Bouton
{
private:
    entrees* bio;
    int bshmid;

public:
    Bouton();

    void initialiser();
    int lireBoutonCharge() const;
    int lireBoutonStop() const;
};

#endif // BOUTON_H 