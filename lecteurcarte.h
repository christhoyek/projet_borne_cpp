#ifndef LECTEURCARTE_H
#define LECTEURCARTE_H

#include <lcarte.h>
#include "bouton.h"
#include "baseclient.h"
#include "Generateur_save.h"
#include "mode.h"
#include "voyant.h"

class LecteurCarte
{
private:
    bool voyantsOk;
    Bouton boutonCharge;
    BaseClient& baseClient;
    Generateur& generateur;
    Mode& currentMode;
    Voyant& voyant;

    void attendreRetrait() const;
    bool attendreBoutonCharge();
    bool reauthentifierPourRecuperation();

public:
    LecteurCarte(BaseClient& base, Generateur& gen, Mode& mode, Voyant& v);

    void initialiser();
    int obtenirNumero() const;
    void lireCarte();
};

#endif // LECTEURCARTE_H