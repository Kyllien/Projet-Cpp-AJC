
#include "fonctionsCSV.h"

// structure table dans dbContacts:
//ID Nom Prenom Sexe Entreprise rue Complement cp Ville mail dtNaissance
//0  1   2      3    4          5   6          7  8     9     10

// entête fichier CSV Pro:
//﻿Identifiant;Nom;Prénom;Sexe;Entreprise;Libellé;Complément;Code Postal;Ville;Mail de Contact

// entête CSV Private
//﻿Identifiant;Nom;Prénom;Sexe;Libellé;Complément;Code Postal;Ville;Date de Naissance



int CSVPROtoDB(ifstream& file)
{
    // lire ligne par ligne
    string line;

    int id;
    string nom,prenom,rue,complement,ville, entreprise, email, dtnaissance;
    char genre;
    int cp;

    // lire et ignorer la 1ère ligne:
    getline(file, line);

    // itérer sur les lignes suivantes pour récupérer les contacts
    while (getline(file, line))
    {
        // split chaque ligne avec un délimiteur  ;
        stringstream ss(line);
        string field;

        int i(0);
        while (getline(ss, field, ';'))
        {

            //cout<<field<<"|";
            switch(i)
            {
                case(0): id=stoi(field); break;
                case(1): nom=field; break;
                case(2): prenom=field; break;
                case(3): genre=field.at(0); break;
                case(4): entreprise=field; break;
                case(5): rue=field; break;
                case(6): complement=field;break;
                case(7): cp=stoi(field); break;
                case(8): ville=field;break;
                case(9): email=field;break;
            }
            i++;
        }

        ContactPro ctmp(id,nom,prenom,genre,entreprise,rue,complement,cp,ville,email);
        addContact(&ctmp);

    }

    return 0;
}


int CSVPRIVEtoDB(ifstream& file)
{

    // lire ligne par ligne
    string line;

    int id;
    string nom,prenom,rue,complement,ville, entreprise, email, dtnaissance;
    char genre;
    int cp;

    // lire et ignorer la 1ère ligne:
    getline(file, line);

    // itérer sur les lignes suivantes pour récupérer les contacts
    while (getline(file, line))
    {


        // split chaque ligne avec un délimiteur  ;
        stringstream ss(line);
        string field;


        int i(0);
        while (getline(ss, field, ';'))
        {

            //cout<<field<<"|";
            switch(i)
            {
                case(0): id=stoi(field); break;
                case(1): nom=field; break;
                case(2): prenom=field; break;
                case(3): genre=field.at(0); break;
                case(4): rue=field; break;
                case(5): complement=field;break;
                case(6): cp=stoi(field); break;
                case(7): ville=field;break;
                case(8): dtnaissance=field;break;
            }
            i++;
        }

        ContactPrive ctmp(id,nom,prenom,genre,rue,complement,cp,ville,dtnaissance);
        addContact(&ctmp);

    }

    return 0;
}
