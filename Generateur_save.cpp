#include "Generateur_save.h"

#include <iostream>
#include <cstdlib>
#include <unistd.h>

Generateur::Generateur(Voyant& v)
    : io(nullptr), shmid(0), etatPrise(false), prise(), voyant(v)
{
}

void Generateur::initialiser()
{
    prise.initialiser();

    io = acces_memoire(&shmid);
    if (io == nullptr)
    {
        std::cerr << "Acces au bouton refuse" << std::endl;
        std::exit(1);
    }

    io->bouton_stop = 0;
}

void Generateur::genererTension(pwm tension)
{
    if (io != nullptr)
    {
        io->gene_pwm = tension;
    }
}

int Generateur::lireTension() const
{
    if (io == nullptr)
    {
        return 0;
    }
    return io->gene_u;
}

void Generateur::setACEtat(int etat)
{
    if (io != nullptr)
    {
        io->contacteur_AC = etat;
    }
}

void Generateur::chargementVH()
{
    int etatS2 = 1;
    int etat = 2;
    bool batteriePleine = false;

    voyant.setCharge(ROUGE);
    genererTension(DC);
    prise.deverrouillerTrappe();

    std::cout << "Brancher la prise pour commencer le chargement" << std::endl;

    while (!etatPrise)
    {
        usleep(1000);
        if (lireTension() == 9)
        {
            etatPrise = true;
        }
    }

    while (etatPrise && !(io->bouton_stop) && !batteriePleine)
    {
        switch (etat)
        {
            case 2:
                prise.verrouillerTrappe();
                voyant.setPriseR(VERT);
                genererTension(AC_1K);
                etat = 3;
                break;

            case 3:
                setACEtat(1);
                if (lireTension() == 6)
                {
                    etat = 4;
                }
                break;

            case 4:
                genererTension(AC_CL);
                if (lireTension() == 9)
                {
                    std::cout << "Batterie pleine" << std::endl;
                    batteriePleine = true;
                }
                break;

            default:
                std::cout << "Etat " << etat << std::endl;
                break;
        }
    }

    io->bouton_stop = 0;
    genererTension(DC);

    while (etatS2)
    {
        usleep(1000);
        if (lireTension() == 9)
        {
            etatS2 = 0;
        }
    }

    setACEtat(0);
    voyant.setCharge(VERT);
    std::cout << "Fin de chargement" << std::endl;
}

void Generateur::recuperationVH()
{
    prise.deverrouillerTrappe();

    while (etatPrise)
    {
        usleep(1000);
        if (lireTension() == 12)
        {
            etatPrise = false;
        }
    }

    prise.verrouillerTrappe();
    voyant.setPriseR(OFF);
    voyant.setCharge(OFF);
    genererTension(STOP);
}