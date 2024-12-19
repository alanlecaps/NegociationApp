/**
 * @file back_end_main.cpp
 * @brief Initialise les variables nécessaires et demande à l'utilisateur les entrées de configuration.
 * @param num_thr_vend Nombre de threads de vendeurs
 * @param num_thr_achet Nombre de threads d'acheteurs
 * @param nombre_prod_ven Nombre de produits par vendeur
 * @param strategie_vendeurs Stratégie des vendeurs
 * @param nombre_de_tours_max Nombre maximal de tours de négociation
 */

#include <iostream>
#include <thread>
#include <string>
#include <cstdlib>
#include <vector>
#include <barrier>
#include <fstream>
#include <memory>
#include <iostream>
#include <sstream>
#include "Vendeur.h"
#include "Acheteur.h"
#include "BoiteAuLettres.h"
#include "Threads_var.h"
#include "Protocol.h"
#include <math.h>
#include "back_end_main.h"
#include <QApplication>
#include <QMainWindow>

using namespace std;




void affichage_Initialisation(int& num_thr_vend, int& num_thr_achet, int& nombre_prod_ven, int &strategie_vendeurs, int &nombre_de_tours_max);

/**
 * @brief Initialise la liste des acheteurs en créant des objets Acheteur.
 * @param acheteur Vecteur des acheteurs
 * @param num_thr_achet Nombre de threads d'acheteurs
 * @param num_thr_vend Nombre de threads de vendeurs
 */
void acheteur_Initialisation(vector<Acheteur>& acheteur, int& num_thr_achet, int& num_thr_vend);

/**
 * @brief Initialise la liste des vendeurs en fonction des paramètres.
 * @param vendeur Vecteur des vendeurs
 * @param param_vendeurs Paramètres spécifiques pour chaque vendeur
 */
void vendeur_Initialisation(vector<Vendeur>&vender , vector<vector<int>> &param_vendeurs);

/**
 * @brief Initialise les boîtes aux lettres pour chaque acheteur et vendeur.
 * @param num_thr_vend Nombre de threads de vendeurs
 * @param num_thr_achet Nombre de threads d'acheteurs
 * @param vendeur Vecteur des vendeurs
 * @param acheteur Vecteur des acheteurs
 * @param p Protocole de négociation
 */
void bal_Initialisation(int& num_thr_vend, int& num_thr_achet, vector<Vendeur>&vender, vector<Acheteur>& acheteur , shared_ptr<Protocol> p);

/**
 * @brief Récupère tous les produits disponibles auprès des vendeurs et les stocke dans un vecteur.
 * @param p_d Vecteur de produits disponibles
 * @param vendeurs Vecteur des vendeurs
 */
void recuperer_tous_produits(vector<Produits_dispos> &p_d, vector<Vendeur> &vendeurs);

/**
 * @brief Affiche les produits disponibles et permet à l'acheteur de faire son choix.
 * @param p_d Liste des produits disponibles
 * @param num_Achet Nombre d'acheteurs
 * @param acheteur Liste des acheteurs
 */
void affichage_choix_Produits_dispos(vector<Produits_dispos> &p_d, int &num_Achet, vector<Acheteur> &acheteur);

/**
 * @brief Affiche les résultats finaux de la négociation, y compris les offres acceptées et rejetées.
 * @param bal Liste des boîtes aux lettres contenant les messages de négociation
 */
void affichage_finales(vector<shared_ptr<BoiteAuLettres>> bal);

/**
 * @brief Fonction principale de gestion de la négociation entre acheteurs et vendeurs utilisant des threads.
 * @param acheteur Liste des acheteurs
 * @param vendeur Liste des vendeurs
 * @param voit Liste des voitures achetées
 * @return Liste des boîtes aux lettres contenant les messages de négociation
 */
vector<shared_ptr<BoiteAuLettres>> start_negocier(vector<Acheteur>& acheteur, vector<Vendeur>& vendeur, vector<shared_ptr<Voiture>>& voit);

/**
 * @brief Lit une ligne spécifique d'un fichier CSV.
 * @param filename Nom du fichier CSV
 * @param lineNumber Numéro de la ligne à lire
 * @return Vecteur des valeurs de la ligne lue
 */
vector<string> readLineFromCSV(const string& filename, int lineNumber);

void niveau();

/**
 * @brief Fonction d'initialisation pour les acheteurs et les vendeurs.
 * @param acheteur Liste des acheteurs
 * @param num_threads_achet Nombre de threads d'acheteurs
 * @param num_threads_ven Nombre de threads de vendeurs
 */
void acheteur_Initialisation(vector<Acheteur> &acheteur, int &num_threads_achet, int &num_threads_ven);

/**
 * @brief Initialise les vendeurs avec des produits aléatoires et leurs informations.
 * @param vendeur Liste des vendeurs
 * @param param_vendeurs Paramètres d'initialisation des vendeurs
 */
void vendeur_Initialisation(vector<Vendeur>&vendeur, vector<vector<int>> &param_vendeurs);

/**
 * @brief Initialise les boîtes aux lettres pour la communication entre acheteurs et vendeurs.
 * @param num_threads_ven Nombre de threads de vendeurs
 * @param num_threads_achet Nombre de threads d'acheteurs
 * @param vendeur Liste des vendeurs
 * @param acheteur Liste des acheteurs
 * @param p Protocole de négociation
 */
void bal_Initialisation(int& num_threads_ven, int& num_threads_achet, vector<Vendeur>& vendeur, vector<Acheteur>& acheteur, shared_ptr<Protocol> p);

/**
 * @brief Récupère tous les produits de tous les vendeurs.
 * @param p_d Vecteur des produits disponibles
 * @param vendeurs Liste des vendeurs
 */
void recuperer_tous_produits(vector<Produits_dispos> &p_d, vector<Vendeur> &vendeurs);

/**
 * @brief Affiche les produits disponibles et permet à chaque acheteur de faire un choix de produit.
 * @param p_d Liste des produits disponibles
 * @param num_achet Nombre d'acheteurs
 * @param achet Liste des acheteurs
 */
void affichage_choix_Produits_dispos(vector<Produits_dispos>& p_d, int& num_achet, vector<Acheteur>& achet);

/**
 * @brief Affiche le résultat des négociations entre acheteurs et vendeurs.
 * @param bal Liste des boîtes aux lettres contenant les offres et contre-offres
 */
void affichage_finales(vector<shared_ptr<BoiteAuLettres>> bal);


/*Cette fonction gère la logique multi-threadée pour démarrer et coordonner les négociations entre plusieurs acheteurs et vendeurs,
tout en collectant les résultats des négociations dans un vecteur de voitures achetées (voit).*/
vector<shared_ptr<BoiteAuLettres>> start_negocier(vector<Acheteur>& acheteur,vector<Vendeur>& vendeur, vector<shared_ptr<Voiture>>& voit){
    int num_threads_achet= acheteur.size();
    int num_threads_ven= vendeur.size();

    init_shared_resources_Acheteur(num_threads_achet);
    init_shared_resources_Vendeur(num_threads_ven);

    vector<thread> vendeur_threads;
    vector<thread> acheteur_threads;
    vector<shared_ptr<BoiteAuLettres>> boite_au_lettres_finales(num_threads_achet);

    for (int i = 0; i < num_threads_achet; i++)
    {
        acheteur_threads.emplace_back(&Acheteur::negocier, &acheteur[i],i,num_threads_achet,ref(boite_au_lettres_finales));
    }
    for (int z = 0; z < num_threads_ven; z++)
    {
        vendeur_threads.emplace_back(&Vendeur::negocier, &vendeur[z],z,num_threads_ven);
    }


        *child_ready_flags_Achet[0]=true;
        child_Achet_cvs[0]->notify_one();
        cout<<"Acheteur "<<0<<"notifie (main)";


    for (auto& t : acheteur_threads) {
        t.join();
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        termination_flag->store(true);
        for (int i = 0; i < vendeur_threads.size(); i++)
        {
            *child_ready_flags_Vend[i]=true;
            child_Vend_cvs[i]->notify_one();
        }
    }

    for (auto& t : vendeur_threads) {
        t.join();
    }



    for (int var = 0; var < acheteur.size(); ++var) {
        if(acheteur[var].getProduit()->getPrix()!=0){
        auto produit_ptr = acheteur[var].getProduit();
        if (auto voiture_ptr = std::dynamic_pointer_cast<Voiture>(produit_ptr)) {
            voit.push_back(voiture_ptr);
        }
        }
    }


    return boite_au_lettres_finales;
}

//n'est plus utilise
void affichage_Initialisation(int &num_threads_ven,int &num_threads_achet,int &nombre_prod_par_vend, int &strategie_vendeurs, int &nombre_de_tours_max){



    cout<<"Combien de vendeurs voulez vous?"<<endl;
    cin>> num_threads_ven;

    cout<<"Combien de acheteurs voulez vous?"<<endl;
    cin>> num_threads_achet;

    cout<<"Combien de Produits par Vendeurs voulez vous?"<<endl;
    cin>> nombre_prod_par_vend;

    cout<<"Quelle strategie voulez vous pour TOUS les vendeurs?"<<endl;
    cin>>strategie_vendeurs;

    cout<<"Combien de tours doit durer les negociation au maximal"<<endl;
    cin>>nombre_de_tours_max;

}

void acheteur_Initialisation(vector<Acheteur> &acheteur,int &num_threads_achet,int &num_threads_ven){
    for (size_t z = 0; z < num_threads_achet; z++)
    {
    Acheteur achet(z,num_threads_ven);
    acheteur.push_back(achet);
    }
}

void vendeur_Initialisation(vector<Vendeur>&vendeur  , vector<vector<int>> &param_vendeurs)
{
    string categorie_adress="";
    string cat_name="";
    vector<string> data;
    int nbr_lignes=0;
    int ligne_choisi=0;
    int cat=0,ligne=0;
    int id=0;
    srand(time(NULL));

    for (size_t i = 0; i < param_vendeurs.size(); i++) {
        Vendeur ven(i, 1);
        ven.setStyle_negociacion(param_vendeurs[i][0]);
        ven.set_tKarma(param_vendeurs[i][2]);
        vendeur.push_back(ven);
        for (size_t y = 0; y < param_vendeurs[i][1]; y++) {

            cat=rand()%9;
            switch (cat)
            {
            case 0:
                categorie_adress="../../data/audi.csv";
                cat_name="Audi";
                nbr_lignes=10660;
                break;
            case 1:
                categorie_adress="../../data/bmw.csv";
                cat_name="BMW";
                nbr_lignes=10780;
                break;
            case 2:

                categorie_adress="../../data/ford.csv";
                nbr_lignes=17960;

                cat_name="Ford";
                break;
            case 3:
                categorie_adress="../../data/hyundi.csv";
                cat_name="Hyundai";
                nbr_lignes=4860;
                break;
            case 4:

                categorie_adress="../../data/merc.csv";
                nbr_lignes=13110;
                cat_name="Mercedes";
                break;
            case 5:
                categorie_adress="../../data/skoda.csv";
                cat_name="Skoda";
                nbr_lignes=6260;
                break;
            case 6:
                categorie_adress="../../data/toyota.csv";
                cat_name="Toyota";
                nbr_lignes=6730;
                break;
            case 7:
                categorie_adress="../../data/vauxhall.csv";
                cat_name="Vauxhall";
                nbr_lignes=13630;
                break;
            case 8:
                categorie_adress="../../data/vw.csv";
                cat_name="VW";
                nbr_lignes=15150;
                break;

            default:
                break;

            }
            ligne_choisi = (rand() % nbr_lignes) + 2;
            data = readLineFromCSV(categorie_adress, ligne_choisi);
            id = ((cat + 1) * 1000) + ligne_choisi;

            vendeur.back().addVoiture(id, "pas de description", stof(data[2]), "Voiture", "pas d'image", cat_name,
                                      data[0], stoi(data[1]), data[3], stoi(data[4]), data[5], stoi(data[7]), stoi(data[8]));

            float min_prix = (rand() % 5000) + 5000;  // Prix min entre 5000 et 10000
            float max_prix = min_prix + (rand() % 10000) + 5000;  // Max supérieur de 5000 à 15000
            vendeur.back().setFourchettePrix(min_prix, max_prix);
        }
    }
}

void bal_Initialisation(int& num_threads_ven,int& num_threads_achet,vector<Vendeur>&vendeur, vector<Acheteur>& acheteur ,  shared_ptr<Protocol> p){


        for (size_t u = 0; u < num_threads_ven; u++)
        {
            vendeur[u].setBalSize(num_threads_achet);
        }
     for (size_t y = 0; y < num_threads_achet; y++)
        {
            for (size_t u = 0; u < num_threads_ven; u++)
            {
                shared_ptr<BoiteAuLettres> bal=make_shared<BoiteAuLettres>(p);
                acheteur[y].insertBaL(u,bal);
                vendeur[u].insertBaL(y,bal);
            }

        }

}

vector<string> readLineFromCSV(const string& filename, int lineNumber) {
    ifstream file(filename);
    string line;
    int currentLine = 0;

    if (!file.is_open()) {
        cerr << "Fehler beim Öffnen der Datei!" << endl;
        return {};
    }


    while (getline(file, line)) {
        if (currentLine == lineNumber) {
            file.close();
            stringstream ss(line);
            string cell;
            vector<string> row;
             while (getline(ss, cell, ',')) {
                row.push_back(cell);  // Jede Zelle zur aktuellen Zeile hinzufügen
        }
            return row;
        }
        currentLine++;
    }

    cout<<"ligne existe pas"<<endl;
    cout<<filename<<endl;
    file.close();

    return {};
}

void recuperer_tous_produits(vector<Produits_dispos> &p_d, vector<Vendeur> &vendeurs) {
    string m = "", b = "";
    p_d.clear();
    int ID;
    int prx = 0;
    vector<shared_ptr<Produit>> temp;
    bool est_dedans = false;

    // Parcours des vendeurs
    for (int i = 0; i < vendeurs.size(); i++) {
        temp = vendeurs[i].getProduits();
        for (int y = 0; y < temp.size(); y++) {
            auto voit = dynamic_pointer_cast<Voiture>(temp[y]);
            ID = voit->getId();
            m = voit->getModel();
            b = voit->getBrand();
            prx = voit->getPrix();

            // Vérification si le produit est déjà dans la liste
            est_dedans = false;
            for (int n = 0; n < p_d.size(); n++) {
                if (p_d[n].est_egale(m, b)) {
                    p_d[n].nbr++;                // Compte le nombre d'occurrences
                    p_d[n].prix_min = std::min(p_d[n].prix_min, static_cast<float>(prx));
                    p_d[n].prix_max = std::max(static_cast<float>(p_d[n].prix_max), static_cast<float>(prx));  // Mise à jour du prix maximal
                    est_dedans = true;
                    break;
                }
            }

            // Si le produit n'est pas encore dans la liste, on l'ajoute
            if (!est_dedans) {
                p_d.push_back(Produits_dispos(b, m, prx)); // Création avec prix initial
                p_d.back().prix_min = prx;  // Initialisation de la fourchette de prix
                p_d.back().prix_max = prx;  // Initialisation de la fourchette de prix
                p_d.back().nbr = 1;         // Une première occurrence
            }
        }
    }

    }

//N'est plus utilise
void affichage_choix_Produits_dispos(vector<Produits_dispos>& p_d, int& num_achet, vector<Acheteur>& achet) {
    for (int n = 0; n < p_d.size(); n++) {
        cout << "ID: " << n << "\nMarque: " << p_d[n].marque << "\nModele: " << p_d[n].modele
             << "\nFourchette de prix: " << p_d[n].prix_min << " € - " << p_d[n].prix_max << " €" << endl;
    }

    string m = "", b = "";
    float prx = 0.0f;
    int id = 0;
    int strat = 0;

    for (size_t i = 0; i < num_achet; i++) {
        cout << "Choisissez votre " << i << ". produit" << endl;
        cin >> id;

        cout << "Le produit choisi se situe entre " << p_d[id].prix_min << " € et " << p_d[id].prix_max << " €." << endl;

        cout << "Quel prix êtes-vous prêt à payer ? (Entre " << p_d[id].prix_min << " et " << p_d[id].prix_max << ")" << endl;
        do {
            cin >> prx;
            if (prx < p_d[id].prix_min || prx > p_d[id].prix_max) {
                cout << "Veuillez entrer un prix dans la fourchette spécifiée." << endl;
            }
        } while (prx < p_d[id].prix_min || prx > p_d[id].prix_max);

        cout << "Quelle stratégie voulez-vous utiliser ?" << endl;
        cin >> strat;

        b = p_d[id].marque;
        m = p_d[id].modele;
        achet[i].setStrat(strat);
        achet[i].setProduitVoit(m, b, prx);
    }
}

//N'est plus utilise
void affichage_finales(vector<shared_ptr<BoiteAuLettres>> bal) {
    for (int i = 0; i < bal.size(); i++) {
        if (bal[i]->dernierMessage()->getOffre() == 0) {
            cout << "Désolée, les négociations n'ont pas terminé avec un accord.\nVoici le protocole des messages : \n";
        } else {
            float prix_offre = bal[i]->dernierMessage()->getOffre();
            shared_ptr<Produit> produit = bal[i]->dernierMessage()->getProduit();

            if (prix_offre >= produit->getPrixMin() && prix_offre <= produit->getPrixMax()) {
                cout << "Bravo !! Vous avez acheté le produit pour " << prix_offre << " €.\nVoici le protocole des messages : \n";
            } else {
                cout << "Le prix final " << prix_offre << " € ne respecte pas la fourchette ("
                     << produit->getPrixMin() << " - " << produit->getPrixMax() << " €).\n";
            }
        }
    }
}
