#ifndef GENERATEUR_SAVE_H
#define GENERATEUR_SAVE_H

#include <memoire_borne.h>
#include <donnees_borne.h>
#include "prise.h"
#include "voyant.h"

class Generateur
{
private:
    entrees* io;
    int shmid;
    bool etatPrise;
    Prise prise;
    Voyant& voyant;

public:
    explicit Generateur(Voyant& v);

    void initialiser();
    void chargementVH();
    void recuperationVH();

    void genererTension(pwm tension);
    int lireTension() const;
    void setACEtat(int etat);
};

#endif // GENERATEUR_SAVE_H