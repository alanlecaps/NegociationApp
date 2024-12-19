/**
 * @file Message.cpp
 * @brief Implémentation de la classe Message.
 *
 * Ce fichier contient l'implémentation des méthodes de la classe `Message`, utilisée pour représenter un message
 * envoyé entre un émetteur et un récepteur dans le cadre de négociations ou d'offres.
 * La classe contient des informations sur l'objet de l'offre, l'offre elle-même, le message, ainsi que des identifiants
 * pour l'émetteur et le récepteur. Elle inclut également un produit auquel le message se réfère.
 *
 * @author [Ton Nom]
 * @date [Date]
 */

#include "Message.h"
#include <iostream>

using namespace std;

/**
 * @brief Constructeur de la classe Message.
 *
 * Ce constructeur initialise un message avec l'identifiant de l'émetteur, l'identifiant du récepteur,
 * l'objet du message, l'offre associée, le contenu du message, et un produit lié à l'offre.
 *
 * @param id_e Identifiant de l'émetteur du message.
 * @param id_r Identifiant du récepteur du message.
 * @param obj Objet du message.
 * @param offr Offre associée au message.
 * @param mess Contenu du message.
 * @param prod Pointeur partagé vers le produit lié à l'offre.
 */
Message::Message(int id_e, int id_r, string obj, float offr, string mess, shared_ptr<Produit> prod)
{
    objet = obj;
    offre = offr;
    message = mess;
    id_emmeteur = id_e;
    id_recepteur = id_r;
    produit = prod;
}

/**
 * @brief Destructeur de la classe Message.
 *
 * Ce destructeur libère les ressources allouées par l'objet Message.
 * Dans ce cas, il n'y a pas de gestion particulière, car les membres de la classe sont automatiquement gérés
 * (par exemple, le pointeur partagé `produit` est géré par un `shared_ptr`).
 */
Message::~Message() {}

/**
 * @brief Modifie l'objet du message.
 *
 * @param obj L'objet à définir pour le message.
 */
void Message::setObjet(string obj) {
    objet = obj;
}

/**
 * @brief Modifie l'offre associée au message.
 *
 * @param offr L'offre à définir pour le message.
 */
void Message::setOffre(float offr) {
    offre = offr;
}

/**
 * @brief Modifie le contenu du message.
 *
 * @param mess Le texte du message à définir.
 */
void Message::setMessage(string mess) {
    message = mess;
}

/**
 * @brief Modifie l'identifiant de l'émetteur du message.
 *
 * @param idem L'identifiant de l'émetteur à définir.
 */
void Message::setIdEmmeteur(int idem) {
    id_emmeteur = idem;
}

/**
 * @brief Modifie l'identifiant du récepteur du message.
 *
 * @param idre L'identifiant du récepteur à définir.
 */
void Message::setIdRecep(int idre) {
    id_recepteur = idre;
}

/**
 * @brief Modifie le produit lié au message.
 *
 * @param prod Pointeur partagé vers le produit à définir.
 */
void Message::setProduit(shared_ptr<Produit> prod) {
    produit = prod;
}

/**
 * @brief Récupère l'objet du message.
 *
 * @return L'objet du message.
 */
string Message::getObjet() {
    return objet;
}

/**
 * @brief Récupère l'offre associée au message.
 *
 * @return L'offre du message.
 */
float Message::getOffre() {
    return offre;
}

/**
 * @brief Récupère le contenu du message.
 *
 * @return Le texte du message.
 */
string Message::getMessage() {
    return message;
}

/**
 * @brief Récupère l'identifiant de l'émetteur du message.
 *
 * @return L'identifiant de l'émetteur.
 */
int Message::getIdEmmeteur() {
    return id_emmeteur;
}

/**
 * @brief Récupère l'identifiant du récepteur du message.
 *
 * @return L'identifiant du récepteur.
 */
int Message::getIdRecep() {
    return id_recepteur;
}

/**
 * @brief Récupère le produit lié au message.
 *
 * @return Le pointeur partagé vers le produit lié à l'offre.
 */
shared_ptr<Produit> Message::getProduit() {
    return produit;
}

/**
 * @brief Affiche les détails du message.
 *
 * Cette méthode affiche les informations complètes du message, y compris les identifiants des émetteurs et récepteurs,
 * l'objet du message, l'offre, le produit lié, et le contenu du message.
 */
void Message::afficherMessage() {
    cout << "ID Emetteur: " << id_emmeteur << endl;
    cout << "ID Recepteur: " << id_recepteur << endl;
    cout << "Objet: " << objet << endl;
    cout << "ID Produit: " << produit->getId() << endl;
    cout << "Offre: " << offre << endl << endl;
    cout << "Message: " << message << endl << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
}
