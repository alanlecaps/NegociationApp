#ifndef VENDEUR_H
#define VENDEUR_H


#include "Voiture.h"
#include "Produit.h"
#include "BoiteAuLettres.h"
#include <vector>
#include <memory>

class Vendeur
{
private:
    float prix_min;
    float prix_max;
    vector<shared_ptr<Produit>> produits; //Vecteurs des Produits
    int vendeur_id;
    int style_negociacion;
    int tour_karma;
    float prix_cible;
    vector<shared_ptr<Produit>> produits_possibles;
    vector<shared_ptr<BoiteAuLettres>> boite_au_lettres; //Moyen de communication avec le acheteur
public:
    Vendeur(int id,int nombre_acheteur);
    ~Vendeur();

    //Vector handlers
    void addVoiture(int id,string description,float prix,string categorie,string image,string br, string mod,int year, string bdv, int km, string essen,float mpg, float te);
    void deleteProduits(int id);
    vector<shared_ptr<Produit>> getProduits(); //retourne le vecteur de produits
    void augmenterTousPrix(int pourcentage);
    //setters
    void setPrix(float prx);
    void set_tours(int tours);
    void setStyle_negociacion(int num); //setter pour le style
    void setBalSize(int);
    void set_tKarma(int);
    
    //getters
    float getPrix();
    int get_tKarma();
    int getVendeur_id() const;
    int getStyle_negociacion();
    int get_tours();
    shared_ptr<BoiteAuLettres> getBoiteAuLettres(int id) const;
    void afficherProduits()const;
     vector<shared_ptr<BoiteAuLettres>> getBoiteAuLettresvec() const;
      void insertBaL(int placement, shared_ptr<BoiteAuLettres> bal);
     float getPrixMin() const { return prix_min; }
     float getPrixMax() const { return prix_max; }

    //methodes pour negociations
    shared_ptr<Message> creerMessage(string obj, float offr, string mess,shared_ptr<Produit> prod,int id_achet);
    shared_ptr<Produit> chercherProduit(shared_ptr<Produit> prod);
    void negocier(int thread_id, int num_threads);

    //pour la fourchette de prix
    void setFourchettePrix(float min, float max) {
        prix_min = min;
        prix_max = max;
    }
    //Strategies
    shared_ptr<Message> neg_search(shared_ptr<Message> dernierMessage, bool &enNegociation, float &prix_minimale,shared_ptr<Produit> &prod);
    shared_ptr<Message> neg_accept(shared_ptr<Message> dernierMessage, bool &enNegociation);
    shared_ptr<Message> neg_breakdown(shared_ptr<Message> dernierMessage, bool &enNegociation,int &id_acheteur_en_Negociation);
    shared_ptr<Message> neg_offre(shared_ptr<Message> dernierMessage,float &prix_cible, float &vendeur_offre_avant,float &acheteur_offre,float &acheteur_offre_avant, float &pasapas, bool &enNegociation, int &nombre_de_tours_max);

};

#endif
