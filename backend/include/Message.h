#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <string>
#include <iostream>
#include <memory>
#include "Message.h"
#include "Produit.h"
#include "Voiture.h"


using namespace std ;

class Message
{
    private:
        int id_emmeteur;
        int id_recepteur;
        string objet; //Objet de la lettre
        shared_ptr<Produit> produit;
        float offre;    //Offre avec la lettre (s'il y a)
        string message; //Infos supplementaires

    public:
        Message( int id_e,  int id_r, string obj, float offr, string mess,shared_ptr<Produit> prod);
        ~Message();

        //setters
        void setIdEmmeteur(int emmet);
        void setIdRecep(int recep);
        void setObjet(string obj);
        void setOffre(float offr);
        void setMessage(string mess);
        void setProduit( shared_ptr<Produit> prod);

        //getters
        int getIdEmmeteur();
        int getIdRecep();
        string getObjet();
        float getOffre();
        string getMessage();
        shared_ptr<Produit> getProduit();


        void afficherMessage(); //Affiche tous les parties du message au terminal
};
#endif