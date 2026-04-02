#ifndef PRISE_H
#define PRISE_H

#include <memoire_borne.h>
#include <donnees_borne.h>

class Prise
{
private:
    entrees* io;
    int shmid;

public:
    Prise();

    void initialiser();
    void deverrouillerTrappe();
    void verrouillerTrappe();
    void setLedTrappe(led etat);
};

#endif // PRISE_H