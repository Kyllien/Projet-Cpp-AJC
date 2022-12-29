#include "Contact.h"

Contact::Contact(int id,char* nom, char* prenom,char genre,char* rue, char* complement, int cp, char* ville)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->genre=genre;
    this->rue=rue;
    this->complement=complement;
    this->cp=cp;
    this->ville=ville;

}

Contact::~Contact()
{
    cout<<"suppression contact "<<this->nom<<endl;
    //dtor
}



ostream& operator<<(ostream& sortie, Contact& p)
{

    sortie << p.infos() ;
    return sortie;
}

char* Contact::Getgenre()
{
    char* cstr = new char[2];
    cstr[0] = this->genre;
    cstr[1] = '\0';
    return cstr;
}

