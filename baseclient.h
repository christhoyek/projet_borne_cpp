#ifndef BASECLIENT_H
#define BASECLIENT_H

#include <string>
#include <lcarte.h>

class BaseClient
{
private:
    std::string nomFichier;

    void demanderRetraitCarte() const;

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