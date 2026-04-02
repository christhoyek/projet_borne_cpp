#ifndef BASECLIENT_H
#define BASECLIENT_H

#include <string>
#include <vector>
#include <lcarte.h>

struct Client
{
    int numeroCarte;
    std::string nom;
    std::string prenom;
};

class BaseClient
{
private:
    std::string nomFichier;

    void demanderRetraitCarte() const;

    std::vector<Client> chargerClients() const;
    bool sauvegarderClients(const std::vector<Client>& clients) const;
    std::vector<Client>::iterator trouverClient(std::vector<Client>& clients, int numcarte) const;
    std::vector<Client>::const_iterator trouverClient(const std::vector<Client>& clients, int numcarte) const;

public:
    explicit BaseClient(const std::string& fichier = "baseclient.txt");

    bool authentifier(int numcarte) const;
    bool enregistrer(int numcarte, const std::string& nom = "", const std::string& prenom = "");
    bool supprimer(int numcarte);
    bool modifier(int numcarte, const std::string& nom, const std::string& prenom);

    bool interactiveEnregistrer(int numcarte);
    bool interactiveSupprimer(int numcarte);
    bool interactiveModifier(int numcarte);
};

#endif // BASECLIENT_H