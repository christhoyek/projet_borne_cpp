# projet_borne

Logiciel de simulation et de pilotage d'une borne de recharge VE.
Le système propose deux modes:
- mode gestion de la base client
- mode charge

Le projet s'appuie sur un lecteur de carte et une mémoire partagée simulant le matériel
(voyants, boutons, trappe/prise, générateur).

## Fonctionnalités
- Authentification client par carte
- Gestion interactive des clients (ajout, suppression, modification)
- Séquence de charge avec retour visuel (LED) et bouton CHARGE
- Machine à états du générateur (DC/AC, fin de charge, récupération véhicule)

## Structure du projet
- `borne.cpp`: boucle principale, menu et sélection du mode
- `lecteurcarte.cpp`: lecture carte, authentification et orchestration du flux
- `baseclient.cpp`: CRUD des clients dans `baseclient.txt`
- `Generateur_save.cpp`: logique de charge et pilotage tension/contacteur
- `voyant.cpp`: gestion des voyants
- `bouton.cpp`: lecture des boutons via mémoire partagée
- `prise.cpp`: gestion trappe/prise
- `timer.cpp`: fonctions de temporisation

## Prérequis
- Compilateur C++ (`g++`)
- Bibliothèques et headers fournis par la plateforme borne:
	- `memoire_borne`
	- `donnees_borne`
	- `lcarte`
	- `libsmartcard_borne_x64`
	- `pcsclite`

Les chemins d'inclusion et de librairies sont définis dans le Makefile.

## Compilation

```sh
make
```

## Exécution

```sh
./borne
```

## Nettoyage

```sh
make clean
make veryclean
```

## Format de la base client

Le fichier `baseclient.txt` contient une entrée par ligne:

```txt
<numero_carte> <nom> <prenom>
```

## Remarques
- Les sources ont été migrées en C++ (`.cpp`) et compilées avec `g++`.
- Un fichier `.gitignore` est présent pour ignorer les artefacts de build et fichiers temporaires.