#include "voyant.h"

#include <iostream>
#include <unistd.h>

Voyant::Voyant()
    : shmid(0), io(nullptr)
{
}

bool Voyant::initialiser()
{
    io = acces_memoire(&shmid);

    if (io == nullptr)
    {
        std::cerr << "Acces par les voyants refuse" << std::endl;
        return false;
    }

    setCharge(OFF);
    setDisponible(VERT);
    setDefaut(OFF);
    setPriseR(OFF);

    return true;
}

void Voyant::setCharge(led etat)
{
    if (io != nullptr)
    {
        io->led_charge = etat;
    }
}

void Voyant::setDisponible(led etat)
{
    if (io != nullptr)
    {
        io->led_dispo = etat;
    }
}

void Voyant::setDefaut(led etat)
{
    if (io != nullptr)
    {
        io->led_defaut = etat;
    }
}

void Voyant::setPriseR(led etat)
{
    if (io != nullptr)
    {
        io->led_prise = etat;
    }
}

void Voyant::setTrappe(led etat)
{
    if (io != nullptr)
    {
        io->led_trappe = etat;
    }
}

void Voyant::toggleCharge()
{
    for (int i = 0; i < 8; ++i)
    {
        setCharge(VERT);
        usleep(500000);
        setCharge(OFF);
        usleep(500000);
    }
}

void Voyant::toggleDefaut()
{
    for (int i = 0; i < 8; ++i)
    {
        setDefaut(ROUGE);
        usleep(500000);
        setDefaut(OFF);
        usleep(500000);
    }
}