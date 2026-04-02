#include "baseclient.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

BaseClient::BaseClient(const std::string& fichier)
    : nomFichier(fichier)
{
}

void BaseClient::demanderRetraitCarte() const
{
    std::cout << "Veuillez retirer votre carte." << std::endl;
    attente_retrait_carte();
    std::cout << "Carte retiree." << std::endl;
}

bool BaseClient::authentifier(int numcarte) const
{
    std::ifstream fichier(nomFichier);
    if (!fichier.is_open())
    {
        return false;
    }

    int numero;
    std::string nom, prenom;

    while (fichier >> numero >> nom >> prenom)
    {
        if (numero == numcarte)
        {
            return true;
        }
    }

    return false;
}

bool BaseClient::enregistrer(int numcarte, const std::string& nom, const std::string& prenom)
{
    if (authentifier(numcarte))
    {
        return false;
    }

    std::ofstream fichier(nomFichier, std::ios::app);
    if (!fichier.is_open())
    {
        std::perror("Erreur ouverture baseclient.txt");
        return false;
    }

    fichier << numcarte << " " << nom << " " << prenom << "\n";
    return true;
}

bool BaseClient::interactiveEnregistrer(int numcarte)
{
    if (authentifier(numcarte))
    {
        std::cout << "Client existe deja dans la base. Veuillez retirer votre carte." << std::endl;
        demanderRetraitCarte();
        return false;
    }

    std::string nom, prenom;

    std::cout << "Carte non identifiee. Entrez le nom : ";
    std::getline(std::cin, nom);

    std::cout << "Entrez le prenom : ";
    std::getline(std::cin, prenom);

    if (nom.empty() && prenom.empty())
    {
        std::cout << "Nom et prenom vides - annulation." << std::endl;
        demanderRetraitCarte();
        return false;
    }

    if (enregistrer(numcarte, nom, prenom))
    {
        std::cout << "Client enregistre : " << numcarte << " " << nom << " " << prenom << std::endl;
        demanderRetraitCarte();
        return true;
    }

    std::cout << "Echec enregistrement (deja present ou erreur)." << std::endl;
    demanderRetraitCarte();
    return false;
}

bool BaseClient::supprimer(int numcarte)
{
    std::ifstream in(nomFichier);
    if (!in.is_open())
    {
        return false;
    }

    std::ofstream out("baseclient.tmp");
    if (!out.is_open())
    {
        return false;
    }

    int numero;
    std::string nom, prenom;
    bool removed = false;

    while (in >> numero >> nom >> prenom)
    {
        if (numero == numcarte)
        {
            removed = true;
            continue;
        }

        out << numero << " " << nom << " " << prenom << "\n";
    }

    in.close();
    out.close();

    if (removed)
    {
        if (std::remove(nomFichier.c_str()) != 0)
        {
            std::remove("baseclient.tmp");
            return false;
        }

        if (std::rename("baseclient.tmp", nomFichier.c_str()) != 0)
        {
            return false;
        }

        return true;
    }

    std::remove("baseclient.tmp");
    return false;
}

bool BaseClient::modifier(int numcarte, const std::string& nom, const std::string& prenom)
{
    std::ifstream in(nomFichier);
    if (!in.is_open())
    {
        return false;
    }

    std::ofstream out("baseclient.tmp");
    if (!out.is_open())
    {
        return false;
    }

    int numero;
    std::string ancienNom, ancienPrenom;
    bool modified = false;

    while (in >> numero >> ancienNom >> ancienPrenom)
    {
        if (numero == numcarte)
        {
            out << numcarte << " " << nom << " " << prenom << "\n";
            modified = true;
        }
        else
        {
            out << numero << " " << ancienNom << " " << ancienPrenom << "\n";
        }
    }

    in.close();
    out.close();

    if (modified)
    {
        if (std::remove(nomFichier.c_str()) != 0)
        {
            std::remove("baseclient.tmp");
            return false;
        }

        if (std::rename("baseclient.tmp", nomFichier.c_str()) != 0)
        {
            return false;
        }

        return true;
    }

    std::remove("baseclient.tmp");
    return false;
}

bool BaseClient::interactiveSupprimer(int numcarte)
{
    std::string reponse;

    std::cout << "Supprimer la carte " << numcarte << " ? (o/n) : ";
    std::getline(std::cin, reponse);

    if (!reponse.empty() &&
        (reponse[0] == 'o' || reponse[0] == 'O' || reponse[0] == 'y' || reponse[0] == 'Y'))
    {
        if (supprimer(numcarte))
        {
            std::cout << "Carte " << numcarte << " supprimee." << std::endl;
            demanderRetraitCarte();
            return true;
        }
        else
        {
            std::cout << "Carte " << numcarte << " introuvable ou erreur." << std::endl;
            demanderRetraitCarte();
            return false;
        }
    }

    std::cout << "Annule." << std::endl;
    demanderRetraitCarte();
    return false;
}

bool BaseClient::interactiveModifier(int numcarte)
{
    std::string nom, prenom;

    std::cout << "Entrez le nouveau nom : ";
    std::getline(std::cin, nom);

    std::cout << "Entrez le nouveau prenom : ";
    std::getline(std::cin, prenom);

    if (modifier(numcarte, nom, prenom))
    {
        std::cout << "Carte " << numcarte << " modifiee en : " << nom << " " << prenom << std::endl;
        demanderRetraitCarte();
        return true;
    }
    else
    {
        std::cout << "Carte " << numcarte << " introuvable ou erreur." << std::endl;
        demanderRetraitCarte();
        return false;
    }
}

