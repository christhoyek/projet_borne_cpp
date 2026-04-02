#ifndef TIMER_H
#define TIMER_H

#include "donnees_borne.h"
#include "mem_sh.h"

class Timer
{
private:
    int shmid;
    int departTimer;
    entrees* io;

public:
    Timer();

    void initialiser();
    void raze();
    int valeur() const;
    void delay(int t) const;
};

#endif // TIMER_H