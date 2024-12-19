/**
 * @file Vendeur.cpp
 * @brief Implémentation de la classe Vendeur qui gère les opérations liées à un vendeur dans un système de négociation.
 *
 * Cette classe permet de gérer les produits d'un vendeur, les offres de négociation, et les interactions avec les acheteurs.
 * Elle inclut des fonctions pour ajouter, supprimer des produits, ajuster les prix, et gérer les messages de négociation.
 */

#include "Vendeur.h"
#include <stdlib.h>
#include "Produit.h"
#include "Message.h"
#include "Threads_var.h"
#include <thread>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * @brief Constructeur de la classe Vendeur.
 *
 * Initialise les attributs du vendeur, y compris la liste des produits, la boîte aux lettres des acheteurs, et d'autres paramètres liés à la négociation.
 *
 * @param id L'identifiant du vendeur.
 * @param nombre_acheteur Le nombre d'acheteurs avec lesquels le vendeur peut entrer en négociation.
 */
Vendeur::Vendeur(int id, int nombre_acheteur)
{
    produits={};
    vendeur_id=id;
    style_negociacion=0;
    boite_au_lettres.resize(nombre_acheteur);
    produits_possibles={};
    tour_karma=0;
    prix_cible=0;

}

/**
 * @brief Destructeur de la classe Vendeur.
 *
 * Libère la mémoire allouée pour les produits du vendeur.
 */

Vendeur::~Vendeur()
{

        produits.clear();

}

/**
 * @brief Ajouter un produit au vecteur des produits.
 *
 * Cette fonction permet d'ajouter un produit spécifique (par exemple, une voiture) au vendeur.
 *
 * @param id L'identifiant du produit.
 * @param description La description du produit.
 * @param prix Le prix du produit.
 * @param categorie La catégorie du produit.
 * @param image L'image associée au produit.
 * @param br La marque du produit.
 * @param mod Le modèle du produit.
 * @param year L'année de fabrication du produit.
 * @param bdv La boîte de vitesse du produit.
 * @param km Le kilométrage du produit.
 * @param essen Le type de carburant du produit.
 * @param mpg La consommation de carburant du produit.
 * @param te La taille du moteur du produit.
 */

//ajouter un produit au vecteur
void Vendeur::addVoiture(int id,string description,float prix,string categorie,string image,string br, string mod,int year, string bdv, int km, string essen,float mpg, float te){

    int x=produits.size();
    if (x>0){
     x--;
    x=produits[x]->getId();
    x++;
    }

    shared_ptr<Produit> p=make_shared<Voiture>( id,description, prix, categorie, image, br, mod, year,  bdv, km,  essen, mpg, te);
    produits.push_back(p);

}
/**
 * @file Vendeur.cpp
 * @brief Implémentation de la classe Vendeur qui gère les opérations liées à un vendeur dans un système de négociation.
 *
 * Cette classe permet de gérer les produits d'un vendeur, les offres de négociation, et les interactions avec les acheteurs.
 * Elle inclut des fonctions pour ajouter, supprimer des produits, ajuster les prix, et gérer les messages de négociation.
 */



/**
 * @brief Supprimer un produit du vecteur des produits.
 *
 * Cette fonction permet de supprimer un produit en fonction de son identifiant.
 *
 * @param id L'identifiant du produit à supprimer.
 */

//supprimer un produit au vecteur
void Vendeur::deleteProduits(int id){
    for (int i = 0; i < produits.size(); i++)
    {
        if (produits[i]->getId()==id)
        {
            for (int x = i; x < produits.size()-1; x++)
            {
                produits[x]=produits[x+1];

            }
             produits.pop_back();
              break;
        }

    }

}

/**
 * @brief Augmenter le prix de tous les produits du vendeur.
 *
 * Cette fonction permet d'augmenter le prix de tous les produits d'un pourcentage donné.
 *
 * @param pourcentage Le pourcentage d'augmentation du prix.
 */
void Vendeur::augmenterTousPrix(int pourcentage){
    for(int i=0; produits.size()>i; i++){
        double nouveauPrix=produits[i]->getPrix()*((pourcentage/100)+1);
        produits[i]->setPrix(nouveauPrix);
    }
}



/**
 * @brief Modifier le prix cible du vendeur.
 *
 * Cette fonction permet de définir le prix cible du vendeur pour les négociations.
 *
 * @param prx Le prix cible du vendeur.
 */

//Set le style pour le vendeur
void Vendeur::setPrix(float prx){
    prix_cible=prx;
}


/**
 * @brief Modifier le style de négociation du vendeur.
 *
 * Cette fonction permet de définir le style de négociation du vendeur (par exemple, agressif, passif, etc.).
 *
 * @param num Le style de négociation à appliquer.
 */

void Vendeur::setStyle_negociacion(int num){
    style_negociacion=num;
}



/**
 * @brief Redimensionner la boîte aux lettres du vendeur.
 *
 * Cette fonction permet de redimensionner le tableau des boîtes aux lettres en fonction du nombre d'acheteurs.
 *
 * @param size La nouvelle taille du tableau des boîtes aux lettres.
 */


void Vendeur::setBalSize(int size){
    boite_au_lettres.resize(size);
}


/**
 * @brief Insérer une boîte aux lettres à un emplacement donné.
 *
 * Cette fonction permet d'insérer une boîte aux lettres à une position spécifique dans le tableau des boîtes aux lettres du vendeur.
 *
 * @param placement L'indice où la boîte aux lettres doit être insérée.
 * @param bal La boîte aux lettres à insérer.
 */

 void Vendeur::insertBaL(int placement, shared_ptr<BoiteAuLettres> bal){
    boite_au_lettres[placement]=bal;
 }

 void Vendeur::set_tKarma(int i){
     tour_karma=i;
 }

 //getteurs
 int Vendeur::get_tKarma(){
     return tour_karma;
 }


 /**
 * @brief Récupérer la boîte aux lettres spécifiée par son identifiant.
 *
 * Cette fonction permet de récupérer une boîte aux lettres spécifique d'un acheteur, identifiée par son ID.
 *
 * @param id L'identifiant de la boîte aux lettres à récupérer.
 * @return La boîte aux lettres de l'acheteur correspondant.
 */
vector<shared_ptr<Produit>> Vendeur::getProduits(){
    return produits;
}

int Vendeur::getVendeur_id()const{
    return vendeur_id;
}

int Vendeur::getStyle_negociacion(){
        return style_negociacion;

}

float Vendeur::getPrix(){
    return prix_cible;
}

vector<shared_ptr<BoiteAuLettres>> Vendeur::getBoiteAuLettresvec() const{
    return boite_au_lettres;
}

//retourne une bal specifique
shared_ptr<BoiteAuLettres> Vendeur::getBoiteAuLettres(int id) const {
    return boite_au_lettres[id];
}


/**
 * @brief Afficher les produits du vendeur.
 *
 * Cette fonction permet d'afficher les détails de tous les produits du vendeur.
 */

void Vendeur::afficherProduits()const{
    for (int i = 0; i < produits.size(); i++)
    {
        produits[i]->afficherTout();
    }

}

shared_ptr<Message> Vendeur::creerMessage( string obj, float offr, string mess,shared_ptr<Produit> prod,int id_achet)
{
    string str="vender"+to_string(vendeur_id);
    shared_ptr<Message> m=make_shared<Message>(vendeur_id, id_achet , obj, offr, mess,prod);
    return m;
}

shared_ptr<Produit> Vendeur::chercherProduit(shared_ptr<Produit> prod){
    shared_ptr<Voiture> p1=dynamic_pointer_cast<Voiture>(prod);
    shared_ptr<Voiture> p2=nullptr;
    produits_possibles.clear();
    produits_possibles.shrink_to_fit();
    for (int i = 0; i < produits.size(); i++)
    {
        if(prod->getId()==produits[i]->getId()){
            produits_possibles.push_back(produits[i]);
            return produits[i];
        }
        
        p2=dynamic_pointer_cast<Voiture>(produits[i]);

        if(p1->getCategorie()==p2->getCategorie()||p1->getCategorie()==""){
            if(p1->getBrand()==p2->getBrand()||p1->getBrand()==""){
                if(p1->getModel()==p2->getModel()||p1->getModel()==""){
                    if(p1->getYear()<=p2->getYear()){
                        if(p1->getBoiteDeVitesse()==p2->getBoiteDeVitesse()||p1->getBoiteDeVitesse()==""){
                            if(p1->getKilometres()>=p2->getKilometres()||p1->getKilometres()==0){
                                if(p1->getEssence()==p2->getEssence()||p1->getEssence()==""){
                                    if(p1->getMPG()<=p2->getMPG()||p1->getMPG()==0){
                                        if(p1->getTailleEngin()<=p2->getTailleEngin()||p1->getTailleEngin()==0){
                                            produits_possibles.push_back(produits[i]);
                                        }
                                    }
                                }
                            }   
                        }
                    }
                }
            }
        }
    }

    if(produits_possibles.empty()){
        return nullptr;
    }else{
        std::sort(produits_possibles.begin(), produits_possibles.end(),
                  [](const std::shared_ptr<Produit>& a, const std::shared_ptr<Produit>& b) {
                      auto voitureA = std::dynamic_pointer_cast<Voiture>(a);
                      auto voitureB = std::dynamic_pointer_cast<Voiture>(b);

                      if (voitureA && voitureB) {
                          return voitureA->getPrix() < voitureB->getPrix();
                      }

                      return false;
                  });

        return produits_possibles[0];
    }
}


void Vendeur::negocier(int thread_id, int num_threads){

    bool enNegociation=true;

    shared_ptr<Message> dernierMessage=nullptr;
    shared_ptr<Message> m=nullptr;

    int id_acheteur_en_negociation=-1;

    shared_ptr<Produit> prod;
    float acheteur_offre=0.0f;
    float acheteur_offre_avant=-1;
    float vendeur_offre=0.0f;
    float prix_minimale=0.0f;
    int id_next_Vendeur=-1;
    bool chain_vendeur=false;
    int nombre_de_tours_max=0;
    float pas=0.0f;
    num_threads--; 
    

    while (enNegociation)
    {
        
        {
            cout<<"Vendeur "<<thread_id<<"stop (vendeur.cpp 151)"<<endl;
            std::unique_lock<std::mutex> lock(mtx);
            child_Vend_cvs[thread_id]->wait(lock, [thread_id] { return child_ready_flags_Vend[thread_id]->load(); });
            cout<<"Vendeur "<<thread_id<<"continue (vendeur.cpp 154)"<<endl;
        }



        //logique
        if(termination_flag->load()){
            return;
        }
        //Extraction du dernier message
        if(id_acheteur_en_negociation==-1){
            for (int i = 0; i < boite_au_lettres.size(); i++)
            {
                if(!boite_au_lettres[i]->estVide()&& boite_au_lettres[i]->dernierMessage()->getObjet()=="search"){
                    dernierMessage=boite_au_lettres[i]->dernierMessage();
                    acheteur_offre=dernierMessage->getOffre();
                    id_acheteur_en_negociation=i;
                    nombre_de_tours_max=boite_au_lettres[i]->getProtocol()->getNbrTours();
                    //cout<<"dernier message extrait"<<endl;

                }
            }

        }else{
            dernierMessage=boite_au_lettres[id_acheteur_en_negociation]->dernierMessage();
            acheteur_offre=dernierMessage->getOffre();
        }

        //Logique dependante du objet du message
        if(dernierMessage->getObjet()=="search"){
           // cout<<"Vendeur "<<thread_id<<" search"<<endl;

            m=neg_search(dernierMessage,enNegociation,prix_minimale, prod);
            if(thread_id<num_threads){

                    id_next_Vendeur=thread_id;
                    id_next_Vendeur++;
                    chain_vendeur=true;
            }

        }else if(dernierMessage->getObjet()=="offer"&&acheteur_offre_avant!=acheteur_offre){
             //cout<<"Vendeur "<<thread_id<<" offer"<<endl;
            m=neg_offre(dernierMessage,prix_minimale,vendeur_offre,acheteur_offre,acheteur_offre_avant,pas,enNegociation,nombre_de_tours_max);
        }else if(dernierMessage->getObjet()=="offer"&&acheteur_offre_avant==acheteur_offre){
             cout<<"Vendeur "<<thread_id<<" breakdown"<<endl;
            m=neg_breakdown(dernierMessage, enNegociation, id_acheteur_en_negociation);
        }

        if(dernierMessage->getObjet()=="break-down"){
             //cout<<"Vendeur "<<thread_id<<" fin breakdown"<<endl;
            if((boite_au_lettres[id_acheteur_en_negociation]->getSize()/2)>=tour_karma){
               // cout<<"Karma !!! Les prix augmentent"<<endl;
                augmenterTousPrix(boite_au_lettres[id_acheteur_en_negociation]->getProtocol()->getPenalite());
            }
            int id_temp=id_acheteur_en_negociation;
            dernierMessage=nullptr;
            m=nullptr;
            id_acheteur_en_negociation=-1;
            prod=nullptr;
            acheteur_offre=0.0f;
            acheteur_offre_avant=-1;
            vendeur_offre=0.0f;
            prix_minimale=0.0f;
            pas=0.0f;
            {
                std::lock_guard<std::mutex> lock(mtx);
                *child_ready_flags_Vend[thread_id] = false;
                if(boite_au_lettres[id_temp]->getSize()>3){
                    *child_ready_flags_Achet[id_temp] = true;
                    child_Achet_cvs[id_temp]->notify_one();
                    cout<<"Vendeur"<<thread_id<<"-> Acheteur "<<id_temp<<"notifie (vendeur.cpp 213)"<<endl;
                }
            }
        }else if(dernierMessage->getObjet()=="accept"){
             //cout<<"Vendeur "<<thread_id<<" fin accept"<<endl;
            int id_temp=id_acheteur_en_negociation;
            dernierMessage=nullptr;
            m=nullptr;
            id_acheteur_en_negociation=-1;
            prod=nullptr;
            acheteur_offre=0.0f;
            acheteur_offre_avant=-1;
            vendeur_offre=0.0f;
            prix_minimale=0.0f;
            pas=0.0f;
            {
                std::lock_guard<std::mutex> lock(mtx);
                *child_ready_flags_Vend[thread_id] = false;
                *child_ready_flags_Achet[id_temp] = true;
                child_Achet_cvs[id_temp]->notify_one();
                cout<<"Vendeur"<<thread_id<<"-> Acheteur "<<id_temp<<"notifie (vendeur.cpp 213)"<<endl;
            }


        }else{
        boite_au_lettres[id_acheteur_en_negociation]->laisserMessage(m);
        vendeur_offre=m->getOffre();
        //cout<<"message laissee"<<endl;

        {
            std::lock_guard<std::mutex> lock(mtx);
            *child_ready_flags_Vend[thread_id] = false;  
            if(chain_vendeur){
                *child_ready_flags_Vend[id_next_Vendeur] = true; 
            }else{
                
                *child_ready_flags_Achet[id_acheteur_en_negociation] = true;  
            }



         if(chain_vendeur){
            child_Vend_cvs[id_next_Vendeur]->notify_one();
            cout<<"Vendeur"<<thread_id<<"-> Vendeur "<<id_next_Vendeur<<"notifie (vendeur.cpp 210)"<<endl;
         }else{
            child_Achet_cvs[id_acheteur_en_negociation]->notify_one();
            cout<<"Vendeur"<<thread_id<<"-> Acheteur "<<id_acheteur_en_negociation<<"notifie (vendeur.cpp 213)"<<endl;
        }
        chain_vendeur=false;
        }

        }

    }
    
    cout<<"Vendeur"<<thread_id<<"termine";
}

shared_ptr<Message> Vendeur::neg_search(shared_ptr<Message> dernierMessage, bool &enNegociation, float &prix_minimale,shared_ptr<Produit> &prod){
        std::lock_guard<std::mutex> lock(mtx); // Automatisch freigeben

    prod=chercherProduit(dernierMessage->getProduit());

            shared_ptr<Message> m=nullptr;
            if(prod!=nullptr){

                //calculer prix de depart
                int min,max; //min & max du pourcentage du prix du depart  

                switch (style_negociacion)
                {
                case 1:
                    min= 1200;
                    max= 1400;
                    break;
                case 2:
                    min=1300;
                    max=1500;
                    break;
                case 3:
                    min= 1800;
                    max= 2200;
                    break;
                case 5:
                    min= 1050;
                    max= 1200;
                    break;
                
                default:
                    min= 1200;
                    max= 1400;
                    break;
                }
                float comm= static_cast<float>((rand() % (max - min + 1)) + min)/1000 ;
                prix_minimale=prod->getPrix();
                setPrix(prix_minimale);
                int vendeur_offre=prix_minimale*comm;
                m=creerMessage("offer",vendeur_offre,"",prod,dernierMessage->getIdEmmeteur());


            }else{
                prod=dernierMessage->getProduit();

                m=creerMessage("break-down",0,"",prod,dernierMessage->getIdEmmeteur());
                //enNegociation=false;
            }

            return m;
}

shared_ptr<Message> Vendeur::neg_accept(shared_ptr<Message> dernierMessage, bool &enNegociation){
        std::lock_guard<std::mutex> lock(mtx); //
    //enNegociation=false;
    return creerMessage("accept",dernierMessage->getOffre(),"",dernierMessage->getProduit(),dernierMessage->getIdEmmeteur());
}

shared_ptr<Message> Vendeur::neg_breakdown(shared_ptr<Message> dernierMessage, bool &enNegociation, int &id_acheteur_en_Negociation){

        std::lock_guard<std::mutex> lock(mtx); //


    return creerMessage("break-down",0,"",dernierMessage->getProduit(),dernierMessage->getIdEmmeteur());
}

shared_ptr<Message> Vendeur::neg_offre(shared_ptr<Message> dernierMessage,float &prix_cible, float &vendeur_offre,float &acheteur_offre,float &acheteur_offre_avant, float &pasapas, bool &enNegociation, int &nombre_de_tours){
    std::lock_guard<std::mutex> lock(mtx); // Automatisch freigeben
float offre_nouvelle=0.0f;
string objet="";
int min=0,max=0;
float comm=0.0f;

        if(dernierMessage->getOffre()>=prix_cible){ //"accept"
                objet="accept";
                offre_nouvelle=dernierMessage->getOffre();
                //enNegociation=false;
        }else{

            objet="offer";

            switch (style_negociacion)
            {
            case 1: //Pas a pas strategie
            //contre "offer"
                    if(acheteur_offre_avant==-1){
                        float temp=vendeur_offre-prix_cible;
                        pasapas=(temp/nombre_de_tours); 
                    }
                    offre_nouvelle=vendeur_offre-pasapas;
                    
                
                break;

            case 2: //strategie compromis

                offre_nouvelle=vendeur_offre-((vendeur_offre-acheteur_offre)/2);
                
                break;

            case 3: //strategie aggressive
                
                    min=90;
                    max=95;
                    comm= static_cast<float>((rand() % (max - min + 1)) + min)/100 ;
                    offre_nouvelle=vendeur_offre*comm;
                
                break;

            case 4: //strategie mirroire
                if(acheteur_offre_avant==-1){
                    offre_nouvelle=vendeur_offre*0.95;
                }else{
                    float a=acheteur_offre_avant;
                    float b=acheteur_offre;
                    float pourcentage=a/b;
                    offre_nouvelle=pourcentage*vendeur_offre;
                }
                
                break;

            case 5: //strategie ultimatum
            
                    offre_nouvelle=vendeur_offre;
                
                break;  

            default:
                break;
            }
        }


    if(offre_nouvelle<prix_cible){
        offre_nouvelle=prix_cible;
    }

    
    acheteur_offre_avant=acheteur_offre;
    vendeur_offre=offre_nouvelle;
    return creerMessage(objet,offre_nouvelle,"",dernierMessage->getProduit(),dernierMessage->getIdEmmeteur());

}

