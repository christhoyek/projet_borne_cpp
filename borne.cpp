#include <iostream>
#include <string>
#include <cstdlib>

#include <memoire_borne.h>
#include <donnees_borne.h>
#include <unistd.h>

#include "lecteurcarte.h"
#include "voyant.h"
#include "Generateur_save.h"
#include "baseclient.h"
#include "prise.h"
#include "mode.h"

class Borne
{
private:
    Mode currentMode;
    BaseClient baseClient;
    Voyant voyant;
    Generateur generateur;
    LecteurCarte lecteurCarte;

    void initialiserComposants()
    {
        generateur.initialiser();
        lecteurCarte.initialiser();
    }

    int lireChoix()
    {
        std::string buffer;
        std::getline(std::cin, buffer);

        try
        {
            return std::stoi(buffer);
        }
        catch (...)
        {
            return -1;
        }
    }

    void afficherMenuPrincipal()
    {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1 - Gerer la base client\n";
        std::cout << "2 - Charger\n";
        std::cout << "Choix : ";
    }

    void executerModeCharge()
    {
        std::cout << "Mode charge selectionne. Inserez la carte..." << std::endl;
        lecteurCarte.lireCarte();
    }

    void executerModeGestion()
    {
        bool gestionActive = true;

        while (gestionActive)
        {
            std::cout << "\n-- Gestion Base Client --\n";
            std::cout << "1 - Ajouter\n";
            std::cout << "2 - Supprimer\n";
            std::cout << "3 - Modifier\n";
            std::cout << "4 - Exit\n";
            std::cout << "Choix : ";

            int sousChoix = lireChoix();

            if (sousChoix == 4)
            {
                gestionActive = false;
                break;
            }

            if (sousChoix < 1 || sousChoix > 4)
            {
                std::cout << "Choix invalide." << std::endl;
                continue;
            }

            std::cout << "Inserez la carte pour l'operation..." << std::endl;
            int num = lecteurCarte.obtenirNumero();

            if (num <= 0)
            {
                std::cout << "Lecture invalide ou annulee." << std::endl;
                continue;
            }

            switch (sousChoix)
            {
                case 1:
                    baseClient.interactiveEnregistrer(num);
                    break;
                case 2:
                    baseClient.interactiveSupprimer(num);
                    break;
                case 3:
                    baseClient.interactiveModifier(num);
                    break;
                default:
                    break;
            }
        }
    }

public:
    Borne()
        : currentMode(Mode::Charge),
          baseClient("baseclient.txt"),
          voyant(),
          generateur(voyant),
          lecteurCarte(baseClient, generateur, currentMode, voyant)
    {
        initialiserComposants();
    }

    void executer()
    {
        while (true)
        {
            afficherMenuPrincipal();
            int choix = lireChoix();

            if (choix == 1)
            {
                currentMode = Mode::Gestion;
            }
            else if (choix == 2)
            {
                currentMode = Mode::Charge;
            }
            else
            {
                std::cout << "Choix invalide, maintien du mode actuel ("
                          << (currentMode == Mode::Gestion ? "Gestion" : "Charge")
                          << ")." << std::endl;
            }

            if (currentMode == Mode::Charge)
            {
                executerModeCharge();
            }
            else
            {
                executerModeGestion();
            }
        }
    }
};

int main()
{
    Borne borne;
    borne.executer();
    return 0;
}