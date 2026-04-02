#include "prise.h"

#include <iostream>
#include <cstdlib>

Prise::Prise()
    : io(nullptr), shmid(0)
{
}

void Prise::initialiser()
{
    io = acces_memoire(&shmid);

    if (io == nullptr)
    {
        std::cerr << "Acces a la prise refuse" << std::endl;
        std::exit(1);
    }
}

void Prise::deverrouillerTrappe()
{
    if (io != nullptr)
    {
        io->led_trappe = VERT;
    }
}

void Prise::verrouillerTrappe()
{
    if (io != nullptr)
    {
        io->led_trappe = OFF;
    }
}

void Prise::setLedTrappe(led etat)
{
    if (io != nullptr)
    {
        io->led_prise = etat;
    }
}