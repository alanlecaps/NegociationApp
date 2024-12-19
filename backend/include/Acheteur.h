#ifndef _ACHETEUR_H
#define _ACHETEUR_H

#include <string>
#include "Produit.h"
#include <iostream>
#include "BoiteAuLettres.h"
#include <memory>

using namespace std ;

class Acheteur
{
private:
    int acheteur_id ;
    shared_ptr<Produit> produit ; // pour l'instant inutil
    bool enNegociation;
    int strategie;
    float prix_cible;
    vector<shared_ptr<BoiteAuLettres>> boite_au_lettres;


public:

    // Constructeur
    Acheteur(int id,int nombre_vendeur) ;
    ~Acheteur();

    //Setter
    void insertBaL(int placement, shared_ptr<BoiteAuLettres> bal);
    void setProduitVoit(string m,string b,float prx);
    void setProd(shared_ptr<Produit> v);
    void setStrat(int s);
    void setPrix(float prx);

    // Getters
    float getPrix();
    int getId() const;
    int getStrat()const;
    shared_ptr<Produit> getProduit() const ;
    shared_ptr<BoiteAuLettres> getBoiteAuLettres(int id_Vendeur) const;
    vector<shared_ptr<BoiteAuLettres>> getBoiteAuLettresvec() const;
    bool acceptCheck(float& dernierOffre,float& vendeur_offre);

    //Creer des messages
    shared_ptr<Message> creerMessage(  string obj, float offr, string mess, int id_recep);

    //methodes por négociations
    void negocier(int thread_id, int num_threads, vector<shared_ptr<BoiteAuLettres>> &bal_finale);

    //Strategies

    shared_ptr<Message> neg_offre(shared_ptr<Message> dernierMessage,float &prix_cible, float &vendeur_offre_avant,float &vendeur_offre,float &acheteur_offre_avant, float &pasapas ,int &nbr_tours,int &nombre_de_tours_max, int& tours_obligation_acheter);

    shared_ptr<Message> neg_accept(shared_ptr<Message> dernierMessage);

    shared_ptr<Message> neg_breakdown(shared_ptr<Message> dernierMessage);
};


#endif 

