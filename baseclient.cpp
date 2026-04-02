#include "baseclient.h"

#include <iostream>
#include <fstream>
#include <algorithm>
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

std::vector<Client> BaseClient::chargerClients() const
{
    std::vector<Client> clients;
    std::ifstream fichier(nomFichier);

    if (!fichier.is_open())
    {
        return clients;
    }

    Client client;
    while (fichier >> client.numeroCarte >> client.nom >> client.prenom)
    {
        clients.push_back(client);
    }

    return clients;
}

bool BaseClient::sauvegarderClients(const std::vector<Client>& clients) const
{
    std::ofstream fichier(nomFichier, std::ios::trunc);
    if (!fichier.is_open())
    {
        std::perror("Erreur ouverture baseclient.txt");
        return false;
    }

    for (const auto& client : clients)
    {
        fichier << client.numeroCarte << " "
                << client.nom << " "
                << client.prenom << "\n";
    }

    return true;
}

std::vector<Client>::iterator BaseClient::trouverClient(std::vector<Client>& clients, int numcarte) const
{
    return std::find_if(clients.begin(), clients.end(),
        [numcarte](const Client& client)
        {
            return client.numeroCarte == numcarte;
        });
}

std::vector<Client>::const_iterator BaseClient::trouverClient(const std::vector<Client>& clients, int numcarte) const
{
    return std::find_if(clients.begin(), clients.end(),
        [numcarte](const Client& client)
        {
            return client.numeroCarte == numcarte;
        });
}

bool BaseClient::authentifier(int numcarte) const
{
    std::vector<Client> clients = chargerClients();
    return trouverClient(clients, numcarte) != clients.end();
}

bool BaseClient::enregistrer(int numcarte, const std::string& nom, const std::string& prenom)
{
    std::vector<Client> clients = chargerClients();

    if (trouverClient(clients, numcarte) != clients.end())
    {
        return false;
    }

    clients.push_back({numcarte, nom, prenom});
    return sauvegarderClients(clients);
}

bool BaseClient::supprimer(int numcarte)
{
    std::vector<Client> clients = chargerClients();
    auto it = trouverClient(clients, numcarte);

    if (it == clients.end())
    {
        return false;
    }

    clients.erase(it);
    return sauvegarderClients(clients);
}

bool BaseClient::modifier(int numcarte, const std::string& nom, const std::string& prenom)
{
    std::vector<Client> clients = chargerClients();
    auto it = trouverClient(clients, numcarte);

    if (it == clients.end())
    {
        return false;
    }

    it->nom = nom;
    it->prenom = prenom;

    return sauvegarderClients(clients);
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