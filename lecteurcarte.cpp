#include "lecteurcarte.h"

#include <iostream>
#include <unistd.h>
#include <ctime>

#include <donnees_borne.h>

LecteurCarte::LecteurCarte(BaseClient& base, Generateur& gen, Mode& mode, Voyant& v)
    : voyantsOk(false), baseClient(base), generateur(gen), currentMode(mode), voyant(v)
{
}

void LecteurCarte::initialiser()
{
    initialisations_ports();
    voyantsOk = voyant.initialiser();
    boutonCharge.initialiser();
}

int LecteurCarte::obtenirNumero() const
{
    attente_insertion_carte();
    return lecture_numero_carte();
}

void LecteurCarte::attendreRetrait() const
{
    std::cout << "Veuillez retirer votre carte." << std::endl;
    attente_retrait_carte();
    std::cout << "Carte retiree." << std::endl;
}

bool LecteurCarte::attendreBoutonCharge()
{
    std::cout << "En attente du bouton CHARGE..." << std::endl;

    time_t t0 = time(nullptr);

    while (true)
    {
        int etat = boutonCharge.lireBoutonCharge();
        std::cout << "Etat du bouton CHARGE : " << etat << std::endl;

        if (etat)
        {
            voyant.setDisponible(OFF);
            return true;
        }

        if (time(nullptr) - t0 >= 60)
        {
            std::cout << "Erreur : delai d'une minute depasse, retour au mode initial." << std::endl;
            voyant.setDisponible(VERT);
            voyant.setCharge(OFF);
            return false;
        }

        usleep(100000);
    }
}

bool LecteurCarte::reauthentifierPourRecuperation()
{
    while (true)
    {
        std::cout << "Charge terminee ou arretee. Inserez votre carte pour recuperer le vehicule..." << std::endl;
        attente_insertion_carte();
        int numRecup = lecture_numero_carte();

        std::cout << "Numero carte (reprise) : " << numRecup << std::endl;

        if (numRecup > 0 && baseClient.authentifier(numRecup))
        {
            std::cout << "Carte reconnue. Vous pouvez recuperer le vehicule." << std::endl;
            voyant.setDisponible(VERT);
            return true;
        }

        std::cout << "Carte non reconnue. Veuillez reessayer." << std::endl;
        voyant.setDisponible(ROUGE);
    }
}

void LecteurCarte::lireCarte()
{
    attente_insertion_carte();
    std::cout << "Carte inseree." << std::endl;

    int numero = lecture_numero_carte();
    std::cout << "Votre numero de carte : " << numero << std::endl;

    if (numero <= 0)
    {
        voyant.setDisponible(ROUGE);
        std::cout << "Erreur de lecture de carte." << std::endl;
        attendreRetrait();
        return;
    }

    voyant.setDisponible(VERT);

    bool auth = baseClient.authentifier(numero);
    std::cout << "Authentification " << (auth ? "reussie" : "echouee") << std::endl;

    if (auth)
    {
        if (currentMode == Mode::Charge)
        {
            std::cout << "Carte reconnue. Clignotement du voyant de charge..." << std::endl;
            voyant.toggleCharge();

            std::cout << "Veuillez retirer votre carte avant d'appuyer sur le bouton CHARGE." << std::endl;
            attendreRetrait();

            voyant.setDisponible(VERT);

            if (!attendreBoutonCharge())
            {
                return;
            }

            std::cout << "Bouton CHARGE enfonce. Demarrage de la charge..." << std::endl;

            generateur.chargementVH();

            if (reauthentifierPourRecuperation())
            {
                generateur.recuperationVH();
                std::cout << "Vehicule recupere. Merci et a bientot !" << std::endl;
                attendreRetrait();
            }
        }
        else if (currentMode == Mode::Gestion)
        {
            std::cout << "Mode gestion base client actif. Carte reconnue." << std::endl;
            attendreRetrait();
        }
    }
    else
    {
        if (currentMode == Mode::Gestion)
        {
            baseClient.interactiveEnregistrer(numero);
        }
        else if (currentMode == Mode::Charge)
        {
            voyant.toggleDefaut();
            std::cout << "Acces refuse. Veuillez contacter le support." << std::endl;
            attendreRetrait();
        }
    }
}