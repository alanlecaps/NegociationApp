#ifndef BACK_END_MAIN_H
#define BACK_END_MAIN_H

#include <vector>
#include <string>
#include <memory>
#include "Acheteur.h"
#include "Vendeur.h"

struct Produits_dispos{
    string marque="";
    string modele="";
    float prix=0.0f;
    float prix_min;
    float prix_max;
    int nbr=0;

    Produits_dispos(string x,string y,float pr):marque(x),modele(y),prix_min(pr),prix_max(pr),nbr(1){};


    // Méthode pour vérifier si deux produits sont identiques (même modèle et même marque)
    bool est_egale(string m, string b) {
        return (m == modele && b == marque);
    }
};

void niveau();
void affichage_Initialisation(int &param1, int &param2, int &param3, int &param4, int &param5);
void acheteur_Initialisation(std::vector<Acheteur> &acheteurs, int &param1, int &param2);
void vendeur_Initialisation(vector<Vendeur>&vendeur  , vector<vector<int>> &param_vendeurs);
void bal_Initialisation(int& num_threads_ven,int& num_threads_achet,vector<Vendeur>&vendeur, vector<Acheteur>& acheteur ,  shared_ptr<Protocol> p);
void recuperer_tous_produits(std::vector<Produits_dispos> &produits, std::vector<Vendeur> &vendeurs);
void affichage_choix_Produits_dispos(std::vector<Produits_dispos> &produits, int &param, std::vector<Acheteur> &acheteurs);
void affichage_finales(std::vector<std::shared_ptr<BoiteAuLettres>> boites);
vector<string> readLineFromCSV(const string& filename, int lineNumber) ;
vector<shared_ptr<BoiteAuLettres>> start_negocier(vector<Acheteur>& acheteur,vector<Vendeur>& vendeur,vector<shared_ptr<Voiture>>& voit);


#endif // BACK_END_MAIN_H
