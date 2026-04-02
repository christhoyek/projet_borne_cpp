#ifndef VOYANT_H
#define VOYANT_H

#include <donnees_borne.h>
#include <memoire_borne.h>

class Voyant
{
private:
    int shmid;
    entrees* io;

public:
    Voyant();

    bool initialiser();

    void setCharge(led etat);
    void setDisponible(led etat);
    void setDefaut(led etat);
    void setPriseR(led etat);
    void setTrappe(led etat);

    void toggleCharge();
    void toggleDefaut();
};

#endif // VOYANT_H