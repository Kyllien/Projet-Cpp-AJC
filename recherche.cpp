#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <climits>


#include "Contact.h"
#include "ContactPro.h"
#include "ContactPrive.h"
#include "fonctionsDB.h"
#include "fonctionsInterface.h"



using namespace std;


int main()
{
    // Declaration Variables
    bool quit = false;
    bool quit1;
    bool quit2;
    bool quit3;
    bool quitComplement;
    int choice1;
    int choice2;
    int choice3;
    int choicePro;
    int choiceComp;
    string nom;
    string ville;
    string prenom;
    char sexe;
    string entreprise;
    string libelle;
    string complement = "";
    int codeP;
    string mail;
    tm date;
    string str_date;
    stringstream ss;
    bool bool_date;
    bool bool_sexe;
    int idSup;

    // MENU
    while (!quit)
    {
        std::cout << "\n1. Lister les contacts" << std::endl;
        std::cout << "2. Rechercher a partir de certains criteres (nom ou ville)" << std::endl;
        std::cout << "3. Ajouter un contact" << std::endl;
        std::cout << "4. Supprimer un contact" << std::endl;
        std::cout << "5. Quitter" << std::endl;

        int choice;
        std::cout << "Choisissez une option (1|2|3|4|5) : ";
        fflush(stdin);
        std::cin >> choice;

        switch (choice)
        {
            // Liste les contacts
            case 1:
                do
                {
                    std::cout << "\n1. Afficher tous les contacts" << std::endl;
                    std::cout << "2. Afficher les contacts pro " << std::endl;
                    std::cout << "3. Afficher les contacts prive " << std::endl;

                    std::cout << "Choisissez une option (1|2|3) : ";
                    std::cin >> choice1;
                    quit1 = false;
                    if (choice1 == 1)
                    {
                        const char *sql = "SELECT * FROM contacts";
                        get_table(sql);

                        quit1 = true;
                    }
                    else if (choice1 == 2)
                    {
                        const char *sql = "SELECT * FROM contacts WHERE entreprise not null";
                        get_table(sql);
                        quit1 = true;
                    }
                    else if (choice1 == 3)
                    {
                        const char *sql = "SELECT * FROM contacts WHERE entreprise is null";
                        get_table(sql);
                        quit1 = true;
                    }

                }while(!quit1);

                break;

            // Recherche � partir de crit�res
            case 2:
                do
                {
                    quit2 = false;
                    std::cout << "\n1. Rechercher par nom" << std::endl;
                    std::cout << "2. Rechercher par ville" << std::endl;


                    std::cout << "Choisissez une option (1|2) : ";
                    std::cin.clear(); // r�initialise les indicateurs d'erreur de cin
                    std::cin.ignore(INT_MAX, '\n'); // ignore la ligne entr�e
                    std::cin >> choice2;

                    // Recherche par le nom
                    if (choice2 == 1)
                    {
                        std::cout << "Quel est le nom que vous souhaiter rechercher ?\n" ;
                        std::cin >> nom;
                        nom = to_upper(nom);
                        const char *msg = "SELECT * FROM contacts WHERE nom='";
                        const char *sql = strdup((msg + nom + "'").c_str());
                        get_table(sql);
                        quit2 = true;
                    }
                    // Recherche par la ville
                    else if (choice2 == 2)
                    {
                        std::cout << "Quelle est la ville que vous souhaiter rechercher ?\n" ;
                        std::cin >> ville;
                        ville = to_upper(ville);
                        const char *msg = "SELECT * FROM contacts WHERE ville='";
                        const char *sql = strdup((msg + ville + "'").c_str());
                        get_table(sql);
                        quit2 = true;
                    }
                    // Exceptions
                    else
                    {
                        std::cout << "L'option choisie n'est pas la bonne" << std::endl;
                    }

                }while(!quit2);
                break;

            case 3:
                std::cout << "Entrez un nom : ";
                std::cin >> nom;
                nom = to_upper(nom);

                std::cout << "Entrez un prenom : ";
                std::cin >> prenom;
                prenom = capitalize(prenom);

                // Gestion exceptions pour le sexe
                do
                {
                    std::cout << "Entrez le sexe (M/F) : ";
                    std::cin >> sexe;
                    sexe = toupper(sexe);
                    if (sexe == 'M' | sexe == 'F')
                    {
                        bool_sexe = false;
                    }
                    else
                    {
                        std::cerr << "Erreur dans le format du sexe\n" << std::endl;
                        bool_sexe = true;
                    }
                }while(bool_sexe);


                std::cout << "Entrez le libelle de rue : ";
                std::cin.clear(); // r�initialise les indicateurs d'erreur de cin
                std::cin.ignore(INT_MAX, '\n'); // ignore la ligne entr�e
                std::getline(cin,libelle);

                // Gestion exception Complement d'adresse
                do
                {
                    quitComplement = true;
                    std::cout << "Il y a t il un complement d adresse (1 = Oui / 2 = Non) ? ";
                    std::cin >> choiceComp;
                    if (choiceComp == 1)
                    {
                        quitComplement = false;
                        std::cout << "Entrez un complement d adresse : ";
                        std::cin.clear(); // r�initialise les indicateurs d'erreur de cin
                        std::cin.ignore(INT_MAX, '\n'); // ignore la ligne entr�e
                        std::getline(cin,complement);
                    }
                    else if (choiceComp == 2)
                    {
                        quitComplement = false;
                    }
                }while(quitComplement);



                // A FAIRE : gestion du bon format pour code postal
                std::cout << "Entrez un code postal : ";
                std::cin >> codeP;

                std::cout << "Entrez une ville : ";
                std::cin.clear(); // r�initialise les indicateurs d'erreur de cin
                std::cin.ignore(INT_MAX, '\n'); // ignore la ligne entr�e
                std::getline(cin,ville);
                ville = to_upper(ville);

                // COmpte pro ou priv�
                do
                {
                    quit3 = true;
                    std::cout << "Compte pro ou prive (1/2) ?  ";
                    std::cin >> choicePro;
                    if (choicePro == 1)
                    {
                        quit3 = false;
                        std::cout << "Entrez un mail : ";
                        std::cin >> mail;

                        std::cout << "Entrez une entreprise : ";
                        std::cin.clear(); // r�initialise les indicateurs d'erreur de cin
                        std::cin.ignore(INT_MAX, '\n'); // ignore la ligne entr�e
                        std::getline(cin,entreprise);
                        entreprise = to_upper(entreprise);

                        // cr�ation instances de contacts:
                        ContactPro* pro1 = new ContactPro(1,nom,prenom,sexe,entreprise,libelle,complement,codeP,ville,
                        mail);

                        addContact(pro1);
                        delete pro1;

                    }
                    else if (choicePro == 2)
                    {
                        quit3 = false;
                        // Gestion de la date au bon format
                        do
                        {
                            bool_date = true;
                            std::cout << "Entrez une date de naissance au format dd/mm/yyyy : ";
                            std::cin >> std::get_time(&date, "%d/%m/%Y"); // utilisation de get_time pour lire la date au format sp�cifi�
                            if (std::cin.fail())
                            {
                                std::cerr << "Erreur dans le format de la date\n" << std::endl;
                                std::cin.clear(); // r�initialise les indicateurs d'erreur de cin
                                std::cin.ignore(INT_MAX, '\n'); // ignore la ligne entr�e
                                bool_date = false;
                            }
                        }while(!bool_date);
                        ss << put_time(&date, "%d/%m/%Y");
                        str_date = ss.str();

                        ContactPrive prive1(2,nom,prenom,sexe,libelle,complement,codeP,ville,str_date);

                        addContact(&prive1);

                    }
                }while(quit3);

                break;

            // Suppression d'un contact via son id
            case 4:
                cout << "Quel est l'identifiant du contact que vous voulez supprimer : ";
                cin >> idSup;
                supprimerElement(idSup);
                cout << "Suppression effectu�\n" << endl;
                break;

            case 5:
                std::cout << "Vous quittez l'interface" << std::endl;
                quit = true;
                break;

            default:
                std::cout << "Vous avez mal entre l'option choisie" << std::endl;
                break;
        }
    }
    return 0;
}