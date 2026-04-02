#include "timer.h"

#include <iostream>
#include <cstdlib>

Timer::Timer()
    : shmid(0), departTimer(0), io(nullptr)
{
}

void Timer::initialiser()
{
    io = acces_memoire(&shmid);

    if (io == nullptr)
    {
        std::cerr << "Acces par le timer refuse" << std::endl;
        std::exit(1);
    }

    departTimer = io->timer_sec;
}

void Timer::raze()
{
    if (io != nullptr)
    {
        departTimer = io->timer_sec;
    }
}

int Timer::valeur() const
{
    if (io == nullptr)
    {
        return 0;
    }

    int tempsPresent = io->timer_sec;
    return (tempsPresent - departTimer);
}

void Timer::delay(int t) const
{
    if (io == nullptr)
    {
        return;
    }

    int finDelay = io->timer_sec + t;

    while (finDelay > io->timer_sec)
    {
    }

    std::cout << "Fin de delay de " << t << "s" << std::endl;
}