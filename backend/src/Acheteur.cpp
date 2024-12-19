/**
 * \file Acheteur.cpp
 * \brief Implémentation de la classe Acheteur.
 *
 * Ce fichier contient l'implémentation de la classe Acheteur qui gère les négociations
 * d'un acheteur avec les vendeurs, en utilisant différents mécanismes de négociation.
 * Il inclut la gestion des boîtes aux lettres, l'envoi de messages et l'implémentation
 * des stratégies de négociation.
 *
 * \date Décembre 2024
 */

#ifndef ACHETEUR_O
#define ACHETEUR_O
#include "Acheteur.h"
#include "Produit.h"
#include "Voiture.h"
#include "Threads_var.h"
#include <stdlib.h>
#include <thread>
#include <algorithm>


using namespace std;

/**
 * \brief Constructeur de la classe Acheteur.
 *
 * Ce constructeur initialise l'acheteur avec un identifiant unique, un produit associé
 * et une liste de boîtes aux lettres pour gérer les messages avec les vendeurs.
 *
 * \param idx Identifiant unique de l'acheteur.
 * \param nombre_vendeur Nombre de vendeurs avec lesquels l'acheteur peut négocier.
 */
Acheteur::Acheteur(int idx, int nombre_vendeur) {
    acheteur_id = idx;
    produit = nullptr;
    enNegociation = false;
    strategie = 0;
    prix_cible = 0.0;
    boite_au_lettres.resize(nombre_vendeur);
}

/**
 * \brief Destructeur de la classe Acheteur.
 *
 * Le destructeur libère les ressources associées à l'acheteur, notamment la
 * mémoire allouée pour la boîte aux lettres.
 */
Acheteur::~Acheteur() {
    boite_au_lettres.clear();
}

/**
 * \brief Définir le prix cible pour l'acheteur.
 *
 * \param prx Le prix cible que l'acheteur souhaite payer.
 */
void Acheteur::setPrix(float prx) {
    prix_cible = prx;
}

/**
 * \brief Obtenir le prix cible de l'acheteur.
 *
 * \return Le prix cible de l'acheteur.
 */
float Acheteur::getPrix() {
    return prix_cible;
}

/**
 * \brief Insérer une boîte aux lettres à un emplacement donné.
 *
 * \param placement L'emplacement dans le vecteur de boîtes aux lettres.
 * \param bal Pointeur partagé vers la boîte aux lettres à insérer.
 */
void Acheteur::insertBaL(int placement, shared_ptr<BoiteAuLettres> bal) {
    boite_au_lettres[placement] = bal;
}

/**
 * \brief Définir la stratégie de négociation de l'acheteur.
 *
 * \param s La stratégie à appliquer (par exemple, pas-à-pas ou autre).
 */
void Acheteur::setStrat(int s) {
    strategie = s;
}

/**
 * \brief Obtenir l'identifiant de l'acheteur.
 *
 * \return L'identifiant de l'acheteur.
 */
int Acheteur::getId() const {
    return acheteur_id;
}

/**
 * \brief Obtenir la stratégie de négociation de l'acheteur.
 *
 * \return La stratégie de négociation de l'acheteur.
 */
int Acheteur::getStrat() const {
    return strategie;
}

/**
 * \brief Obtenir le produit associé à l'acheteur.
 *
 * \return Le produit de l'acheteur.
 */
shared_ptr<Produit> Acheteur::getProduit() const {
    return this->produit;
}

/**
 * \brief Définir le produit associé à l'acheteur sous forme de voiture.
 *
 * \param m Modèle de la voiture.
 * \param b Marque de la voiture.
 * \param prx Prix de la voiture.
 */
void Acheteur::setProduitVoit(string m, string b, float prx) {
    produit = make_shared<Voiture>(0, "", prx, "Voiture", "", b, m, 0, "", 0, "", 0, 0);
}

/**
 * \brief Définir le produit de l'acheteur.
 *
 * \param v Pointeur partagé vers le produit à définir.
 */
void Acheteur::setProd(shared_ptr<Produit> v) {
    produit = v;
}

/**
 * \brief Obtenir la boîte aux lettres du vendeur spécifié.
 *
 * \param id_Vendeur L'identifiant du vendeur.
 * \return La boîte aux lettres associée au vendeur.
 */
shared_ptr<BoiteAuLettres> Acheteur::getBoiteAuLettres(int id_Vendeur) const {
    return boite_au_lettres[id_Vendeur];
}

/**
 * \brief Créer un message à envoyer à un vendeur.
 *
 * \param obj L'objet du message.
 * \param offr L'offre dans le message.
 * \param mess Le contenu du message.
 * \param id_recep Identifiant du destinataire.
 * \return Un pointeur partagé vers le message créé.
 */
shared_ptr<Message> Acheteur::creerMessage(string obj, float offr, string mess, int id_recep) {
    shared_ptr<Message> m = make_shared<Message>(acheteur_id, id_recep, obj, offr, mess, produit);
    return m;
}

/**
 * \brief Récupérer toutes les boîtes aux lettres.
 *
 * \return Un vecteur de boîtes aux lettres.
 */
vector<shared_ptr<BoiteAuLettres>> Acheteur::getBoiteAuLettresvec() const {
    return boite_au_lettres;
}

/**
 * \brief Négocier avec les vendeurs.
 *
 * Cette méthode implémente la logique de négociation avec les vendeurs.
 * Elle gère les différents tours de négociation en fonction des stratégies définies.
 *
 * \param thread_id L'identifiant du thread d'acheteur.
 * \param num_threads Le nombre total de threads acheteur.
 * \param bal_finale Le vecteur de boîtes aux lettres finales des acheteurs.
 */

//Logique pour negociations

//Logique coeur
void Acheteur::negocier( int thread_id,int num_threads,  vector<shared_ptr<BoiteAuLettres>> &bal_finale){
    float prix=produit->getPrix();
    prix_cible=prix;

    shared_ptr<Message> m=nullptr;
    shared_ptr<Message> dernierMessage=nullptr;

    int id_VendeurEnNegociation=-1;
    vector<int> vendeurs_en_neg={};
    float vendeur_offre=0.0f;
    float vendeur_offre_avant=-1;
    float acheteur_offre=0.0f;
    float acheteur_offre_avant=-1;
    double threshold=prix_cible*0.2;

    vector<int> accepts={};
    vector<int> breakdown={};
    bool notify=true;

    int nbr_tours=0;
    int tours_maximales=0;
    int tours_obligation_acheter=0;
    int negocier_en_meme_temps=0;

    float pas=0.0f; //utilisée que par strategie pas a pas


    //Phase faire appel aux vendeurs
    {
        {
            cout<<"Acheteur "<<thread_id<<"stop (acheteur.cpp 119)"<<endl;        //
            std::unique_lock<std::mutex> lock(mtx);
            child_Achet_cvs[thread_id]->wait(lock, [thread_id] { return child_ready_flags_Achet[thread_id]->load(); });
            cout<<"Acheteur "<<thread_id<<"continue (acheteur.cpp 122)"<<endl;        //
        }

        tours_maximales=boite_au_lettres[0]->getProtocol()->getNbrTours();
        tours_obligation_acheter=boite_au_lettres[0]->getProtocol()->getNbrOblAchet();
        negocier_en_meme_temps=boite_au_lettres[0]->getProtocol()->getNegMemeTemps();


        for (int i = 0; i < boite_au_lettres.size(); i++)
        {

            m = creerMessage("search", 0 , "",i);
            boite_au_lettres[i]->laisserMessage(m);
        }


        if(num_threads>0){
            *child_ready_flags_Vend[0] = true;
            *child_ready_flags_Achet[thread_id] = false;
            child_Vend_cvs[0]->notify_one();
            cout<<"Acheteur"<<thread_id<<"-> Vendeur "<<0<<"notifie (acheteur.cpp 135)"<<endl;


        }
    }

    //Phase choisir le vendeur avec la meilleure offre et faire premiere offre
    {
        {
            cout<<"Acheteur "<<thread_id<<"stop (acheteur.cpp 143)"<<endl;
            std::unique_lock<std::mutex> lock(mtx);
            child_Achet_cvs[thread_id]->wait(lock, [thread_id] { return child_ready_flags_Achet[thread_id]->load(); });
            cout<<"Acheteur "<<thread_id<<"continue (acheteur.cpp 146)"<<endl;
        }

        for (int i = 0; i < boite_au_lettres.size(); i++)
        {
            if(boite_au_lettres[i]->dernierMessage()->getObjet()=="offer" && boite_au_lettres[i]->dernierMessage()->getOffre() != 0)
            {
                vendeurs_en_neg.push_back(i);
            }
        }
        std::sort(vendeurs_en_neg.begin(), vendeurs_en_neg.end(),
                  [this](const int& a, const int& b) {
                      return boite_au_lettres[a]->dernierMessage()->getOffre() < boite_au_lettres[b]->dernierMessage()->getOffre();
                  });

        if(vendeurs_en_neg.size()>negocier_en_meme_temps){
            vendeurs_en_neg.resize(negocier_en_meme_temps);
        }

        for (int i = 0; i < boite_au_lettres.size(); i++)
        {
            if(!std::any_of(vendeurs_en_neg.begin(), vendeurs_en_neg.end(), [i](int val){return val==i;})){
                m=neg_breakdown(boite_au_lettres[i]->dernierMessage());
                boite_au_lettres[i]->laisserMessage(m);
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    *child_ready_flags_Vend[i] = true;
                    child_Vend_cvs[i]->notify_one();
                }
            }
        }

        if(!vendeurs_en_neg.empty()){
            enNegociation=true;
            for(int i=0;i<vendeurs_en_neg.size();i++){
                if(i!=0){
                    {
                        cout<<"Acheteur "<<thread_id<<"stop (acheteur.cpp 183)"<<endl;
                        std::unique_lock<std::mutex> lock(mtx);
                        child_Achet_cvs[thread_id]->wait(lock, [thread_id] { return child_ready_flags_Achet[thread_id]->load(); });
                        cout<<"Acheteur "<<thread_id<<"continue (acheteur.cpp 143)"<<endl;
                    }
                }

                dernierMessage=boite_au_lettres[vendeurs_en_neg[i]]->dernierMessage();
                vendeur_offre=dernierMessage->getOffre();
                m=neg_offre(dernierMessage, prix,vendeur_offre_avant,vendeur_offre,acheteur_offre_avant, pas,nbr_tours,tours_maximales,tours_obligation_acheter);
                boite_au_lettres[vendeurs_en_neg[i]]->laisserMessage(m);

                {
                    std::lock_guard<std::mutex> lock(mtx);
                    *child_ready_flags_Achet[thread_id] = false;
                    *child_ready_flags_Vend[vendeurs_en_neg[i]] = true;
                    child_Vend_cvs[vendeurs_en_neg[i]]->notify_one();
                    cout<<"Acheteur"<<thread_id<<"-> Vendeur "<<vendeurs_en_neg[i]<<"notifie (acheteur.cpp 175)"<<endl;        //

                }

            }
        }

        nbr_tours++;
    }

    while (enNegociation)
    {

        nbr_tours++;

        for(int i=0;i<vendeurs_en_neg.size();i++){
            //logique

            {
                cout<<"Acheteur "<<thread_id<<"stop (acheteur.cpp 183)"<<endl;
                std::unique_lock<std::mutex> lock(mtx);
                child_Achet_cvs[thread_id]->wait(lock, [thread_id] { return child_ready_flags_Achet[thread_id]->load(); });
                cout<<"Acheteur "<<thread_id<<"continue (acheteur.cpp 143)"<<endl;
            }

            dernierMessage=boite_au_lettres[vendeurs_en_neg[i]]->dernierMessage();
            vendeur_offre=dernierMessage->getOffre();


            if(dernierMessage->getObjet()=="offer"&&vendeur_offre_avant!=vendeur_offre&&nbr_tours<tours_maximales&&(nbr_tours+1)==tours_obligation_acheter&&abs(vendeur_offre-prix_cible)>threshold){
                cout<<"Acheteur "<<thread_id<<" offer obligation ->"<<vendeurs_en_neg[i]<<endl;
                m=neg_breakdown(dernierMessage);
                breakdown.push_back(vendeurs_en_neg[i]);
                boite_au_lettres[vendeurs_en_neg[i]]->laisserMessage(m);
            }else if (dernierMessage->getObjet()=="offer"&&vendeur_offre_avant!=vendeur_offre&&nbr_tours<tours_maximales&&dernierMessage->getOffre()>prix_cible)
            {
                cout<<"Acheteur "<<thread_id<<" offer "<<vendeurs_en_neg[i]<<endl;

                m=neg_offre(dernierMessage,prix,vendeur_offre_avant,vendeur_offre,acheteur_offre_avant,pas,nbr_tours,tours_maximales,tours_obligation_acheter);
                boite_au_lettres[vendeurs_en_neg[i]]->laisserMessage(m);

            }
            else if (dernierMessage->getObjet()=="accept"||nbr_tours>=tours_maximales&&nbr_tours>=tours_obligation_acheter||dernierMessage->getOffre()<=prix_cible&&acceptCheck(acheteur_offre_avant,vendeur_offre)&&dernierMessage->getObjet()=="offer")
            {
                cout<<"Acheteur "<<thread_id<<" accept "<<vendeurs_en_neg[i]<<endl;
                accepts.push_back(vendeurs_en_neg[i]);
                notify=false;
                //m=neg_accept(dernierMessage);
            }
            else if (dernierMessage->getObjet()=="break-down"||dernierMessage->getObjet()=="offer"&&vendeur_offre_avant==vendeur_offre||nbr_tours>=tours_maximales&&nbr_tours<tours_obligation_acheter)
            {
                cout<<"Acheteur "<<thread_id<<" break down"<<vendeurs_en_neg[i]<<endl;
                m=neg_breakdown(dernierMessage);
                breakdown.push_back(vendeurs_en_neg[i]);
                boite_au_lettres[vendeurs_en_neg[i]]->laisserMessage(m);
            }
            if(notify){
                {
                    std::lock_guard<std::mutex> lock(mtx);

                    *child_ready_flags_Achet[thread_id] = false;
                    *child_ready_flags_Vend[vendeurs_en_neg[i]] = true;
                    cout<<"Acheteur"<<thread_id<<"-> Vendeur "<<vendeurs_en_neg[i]<<"notifie (acheteur.cpp 280)"<<endl;
                    child_Vend_cvs[vendeurs_en_neg[i]]->notify_one();
                }
            }
            notify=true;
        }

        vendeurs_en_neg.erase(std::remove_if(vendeurs_en_neg.begin(), vendeurs_en_neg.end(),
                                             [&breakdown](int x) {
                                                 return std::find(breakdown.begin(), breakdown.end(), x) != breakdown.end();
                                             }), vendeurs_en_neg.end());
        vendeurs_en_neg.erase(std::remove_if(vendeurs_en_neg.begin(), vendeurs_en_neg.end(),
                                             [&accepts](int x) {
                                                 return std::find(accepts.begin(), accepts.end(), x) != accepts.end();
                                             }), vendeurs_en_neg.end());
        if(vendeurs_en_neg.empty()){
            enNegociation=false;
        }
    }

    accepts.erase(std::remove_if(accepts.begin(), accepts.end(),
                                         [&breakdown](int x) {
                                             return std::find(breakdown.begin(), breakdown.end(), x) != breakdown.end();
                                         }), accepts.end());

    {
        cout<<"Acheteur "<<thread_id<<"stop dehors (acheteur.cpp 226)"<<endl;
        std::unique_lock<std::mutex> lock(mtx);
        child_Achet_cvs[thread_id]->wait(lock, [thread_id] { return child_ready_flags_Achet[thread_id]->load(); });
        cout<<"Acheteur "<<thread_id<<"continue (acheteur.cpp 229)"<<endl;
    }

    if(!accepts.empty()){

        std::sort(accepts.begin(), accepts.end(),
                  [this](const int& a, const int& b) {
                      return boite_au_lettres[a]->dernierMessage()->getOffre() < boite_au_lettres[b]->dernierMessage()->getOffre();
                  });

        for (int i = 0; i < accepts.size(); ++i) {
            {
                cout<<"Acheteur "<<thread_id<<"stop dehors (acheteur.cpp 226)"<<endl;
                std::unique_lock<std::mutex> lock(mtx);
                child_Achet_cvs[thread_id]->wait(lock, [thread_id] { return child_ready_flags_Achet[thread_id]->load(); });
                cout<<"Acheteur "<<thread_id<<"continue (acheteur.cpp 229)"<<endl;
            }

            if(i==0){
                m= neg_accept(boite_au_lettres[accepts[i]]->dernierMessage());
            }else{
                m=neg_breakdown(boite_au_lettres[accepts[i]]->dernierMessage());

            }
            boite_au_lettres[accepts[i]]->laisserMessage(m);

            {
                std::lock_guard<std::mutex> lock(mtx);

                *child_ready_flags_Achet[thread_id] = false;
                *child_ready_flags_Vend[accepts[i]] = true;
                cout<<"Acheteur"<<thread_id<<"-> Vendeur "<<accepts[i]<<"notifie (acheteur.cpp 333)"<<endl;
                child_Vend_cvs[accepts[i]]->notify_one();
            }
        }

        {
            cout<<"Acheteur "<<thread_id<<"stop dehors (acheteur.cpp 226)"<<endl;
            std::unique_lock<std::mutex> lock(mtx);
            child_Achet_cvs[thread_id]->wait(lock, [thread_id] { return child_ready_flags_Achet[thread_id]->load(); });
            cout<<"Acheteur "<<thread_id<<"continue (acheteur.cpp 229)"<<endl;
        }
        bal_finale[thread_id]=boite_au_lettres[accepts[0]];
        setProd(bal_finale[thread_id]->getMessage(1)->getProduit());
        getProduit()->setPrix(bal_finale[thread_id]->dernierMessage()->getOffre());
    }else{
        getProduit()->setPrix(0.0);

    }
    cout<<"===========Acheteur ID"<<thread_id<<"termine============================================================================================="<<endl;

    {
        std::lock_guard<std::mutex> lock(mtx);
        thread_id++;
        if(thread_id<num_threads){
            *child_ready_flags_Achet[thread_id] = true;
            cout<<"Achet "<<thread_id<<"notifie (acheteur.cpp 358)"<<endl;
            child_Achet_cvs[thread_id]->notify_one();
        }
    }

}

/**
 * \brief Réponse de l'acheteur à une offre de vendeur.
 *
 * Cette méthode calcule la nouvelle offre de l'acheteur en fonction des messages
 * reçus et de la stratégie choisie.
 *
 * \param dernierMessage Le dernier message reçu du vendeur.
 * \param prix_cible Le prix cible de l'acheteur.
 * \param vendeur_offre_avant Offre précédente du vendeur.
 * \param vendeur_offre Offre actuelle du vendeur.
 * \param acheteur_offre_avant Offre précédente de l'acheteur.
 * \param pasapas Stratégie pas-à-pas.
 * \param nbrtours Nombre actuel de tours de négociation.
 * \param nombre_tours_max Nombre maximal de tours.
 * \param tours_obligation_acheter Nombre de tours obligatoires pour acheter.
 * \return Le message de l'acheteur en réponse à l'offre du vendeur.
 */

//Methodes reponses
shared_ptr<Message> Acheteur::neg_offre(shared_ptr<Message> dernierMessage,float &prix_cible, float &vendeur_offre_avant,float &vendeur_offre,float &acheteur_offre_avant, float &pasapas, int &nbrtours,int &nombre_tours_max, int& tours_obligation_acheter){
    std::lock_guard<std::mutex> lock(mtx); // Automatisch freigeben
    float offre_nouvelle=0.0f;
    string objet="";
    int min=0,max=0;
    float comm=0.0f;

    if(acheteur_offre_avant==-1){   //Premier offre du acheteur

        objet="offer";

        switch (strategie)
        {
        case 1: //Pas a pas strategie
            //contre "offer"
            min=60;
            max=80;
            comm= static_cast<float>((rand() % (max - min + 1)) + min)/100 ;
            offre_nouvelle=prix_cible*comm;
            pasapas=(prix_cible-offre_nouvelle)/nombre_tours_max;
            break;

        case 2: //strategie compromis

            min=70;
            max=50;
            comm= static_cast<float>((rand() % (max - min + 1)) + min)/100 ;
            offre_nouvelle=prix_cible*comm;
            break;

        case 3: //strategie aggressive

            min=10;
            max=20;
            comm= static_cast<float>((rand() % (max - min + 1)) + min)/100 ;
            offre_nouvelle=prix_cible*comm;

            break;

        case 4: //strategie mirroire

            min=60;
            max=80;
            comm= static_cast<float>((rand() % (max - min + 1)) + min)/100 ;
            offre_nouvelle=prix_cible*comm;
            break;

        case 5: //strategie ultimatum

            min=80;
            max=95;
            comm= static_cast<float>((rand() % (max - min + 1)) + min)/100 ;
            offre_nouvelle=prix_cible*comm;

            break;

        default:
            break;
        }





    }else{      //A partir du premier offre


        objet="offer";

        switch (strategie)
        {
        case 1: //Pas a pas strategie
            //contre "offer"
            offre_nouvelle=acheteur_offre_avant+pasapas;

            break;

        case 2: //strategie compromis

            offre_nouvelle=acheteur_offre_avant+((vendeur_offre-acheteur_offre_avant)/2);

            break;

        case 3: //strategie aggressive

            min=105;
            max=110;
            comm= static_cast<float>((rand() % (max - min + 1)) + min)/100 ;
            offre_nouvelle=acheteur_offre_avant*comm;

            break;

        case 4: //strategie mirroire
        {
            float a=vendeur_offre_avant;
            float b=vendeur_offre;
            float pourcentage=a/b;
            offre_nouvelle=pourcentage*vendeur_offre;
            offre_nouvelle=pourcentage*acheteur_offre_avant;
        }
        break;

        case 5: //strategie ultimatum

            offre_nouvelle=acheteur_offre_avant;

            break;

        default:
            break;

        }


    }
    if(offre_nouvelle>prix_cible){
        offre_nouvelle=prix_cible;
    }
    vendeur_offre_avant=vendeur_offre;
    acheteur_offre_avant=offre_nouvelle;
    return creerMessage(objet,offre_nouvelle,"",dernierMessage->getIdEmmeteur());

}

shared_ptr<Message> Acheteur::neg_accept(shared_ptr<Message> dernierMessage){
    std::lock_guard<std::mutex> lock(mtx); // Automatisch freigeben
    enNegociation=false;
    setProd(dernierMessage->getProduit());
    getProduit()->setPrix(dernierMessage->getOffre());
    return creerMessage("accept",dernierMessage->getOffre(),"",dernierMessage->getIdEmmeteur());
}

shared_ptr<Message> Acheteur::neg_breakdown(shared_ptr<Message> dernierMessage){
    std::lock_guard<std::mutex> lock(mtx); // Automatisch freigeben
    return creerMessage("break-down",0,"",dernierMessage->getIdEmmeteur());
}

bool Acheteur::acceptCheck(float& dernierOffre,float& vendeur_offre){
    float x=vendeur_offre/dernierOffre;
    if(vendeur_offre<=prix_cible&1.2>x){
        return true;
    }else{
        return false;
    }
}

#endif
