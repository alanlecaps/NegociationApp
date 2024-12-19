/**
 * @file BoiteAuLettres.cpp
 * @brief Implementation de la classe BoiteAuLettres.
 */

#include <vector>
#include <iostream>
#include "Message.h"
#include "BoiteAuLettres.h"
#include <mutex>

using namespace std ;

/**
 * @class BoiteAuLettres
 * @brief Représente une boîte aux lettres contenant des messages.
 *
 * La classe gère l'ajout, l'affichage et la récupération de messages.
 * Elle assure également la sécurité des accès concurrents via un verrou mutex.
 */
BoiteAuLettres::BoiteAuLettres(shared_ptr<Protocol> prot){
    this->boiteAuLettres = {};
    this->protocol = prot;
}

/**
 * @brief Destructeur de la classe BoiteAuLettres.
 *
 * Le destructeur vide la boîte aux lettres.
 */
BoiteAuLettres::~BoiteAuLettres(){
    boiteAuLettres.clear();
}

/**
 * @brief Récupère le protocole associé à la boîte aux lettres.
 * @return Le protocole utilisé.
 */
shared_ptr<Protocol> BoiteAuLettres::getProtocol() const{
    return protocol;
}

/**
 * @brief Définit un nouveau protocole pour la boîte aux lettres.
 * @param prot Le nouveau protocole.
 */
void BoiteAuLettres::setProtocol(shared_ptr<Protocol> prot){
    protocol = prot;
}

/**
 * @brief Ajoute un message dans la boîte aux lettres.
 *
 * Cette méthode protège l'accès concurrent à la boîte aux lettres via un mutex.
 * @param m Le message à ajouter.
 * @return La taille de la boîte aux lettres après l'ajout.
 */
int BoiteAuLettres::laisserMessage(shared_ptr<Message> m){
    lock_guard<std::mutex> guard(mtx);
    boiteAuLettres.push_back(m);
    return boiteAuLettres.size();
}

/**
 * @brief Récupère le dernier message de la boîte aux lettres.
 *
 * Si la boîte aux lettres est vide, affiche un message d'erreur et retourne un pointeur nul.
 * @return Le dernier message ou nullptr si la boîte est vide.
 */
shared_ptr<Message> BoiteAuLettres::dernierMessage(){
    lock_guard<std::mutex> guard(mtx);
    int index = boiteAuLettres.size();
    if(index == 0){
        cout << "Boite au lettres vide!" << endl;
        return nullptr;
    } else {
        index--;
        return boiteAuLettres[index];
    }
}

/**
 * @brief Affiche tous les messages dans la boîte aux lettres.
 *
 * Chaque message est affiché dans l'ordre d'ajout.
 */
void BoiteAuLettres::afficherDiscussion(){
    lock_guard<std::mutex> guard(mtx);
    int index = boiteAuLettres.size();
    for (int i = 0; i < index; i++){
        boiteAuLettres[i]->afficherMessage();
    }
}

/**
 * @brief Vérifie si la boîte aux lettres est vide.
 * @return True si la boîte aux lettres est vide, sinon False.
 */
bool BoiteAuLettres::estVide(){
    lock_guard<std::mutex> guard(mtx);
    return boiteAuLettres.empty();
}

/**
 * @brief Récupère la taille actuelle de la boîte aux lettres.
 * @return La taille de la boîte aux lettres.
 */
int BoiteAuLettres::getSize(){
    lock_guard<std::mutex> guard(mtx);
    return boiteAuLettres.size();
}

/**
 * @brief Récupère un message par son index.
 * @param i L'index du message à récupérer.
 * @return Le message à l'index spécifié.
 */
shared_ptr<Message> BoiteAuLettres::getMessage(int i){
    lock_guard<std::mutex> guard(mtx);
    return boiteAuLettres[i];
}

/**
 * @brief Récupère tous les messages de la boîte aux lettres.
 * @return Un vecteur de tous les messages dans la boîte aux lettres.
 */
vector<shared_ptr<Message>> BoiteAuLettres::getBoiteAuLettres() const {
    return boiteAuLettres;
}
