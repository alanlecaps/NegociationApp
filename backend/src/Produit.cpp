/**
 * @file Produit.cpp
 * @brief Implémentation de la classe Produit, représentant un produit.
 */

#include "Produit.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Destructeur de la classe Produit.
 */
Produit::~Produit() {}

/**
 * @brief Récupère la description du produit.
 * @return La description du produit.
 */
string Produit::getDescription() const {
    return this->description;
}

/**
 * @brief Récupère le prix du produit.
 * @return Le prix du produit.
 */
float Produit::getPrix() const {
    return this->prix;
}

/**
 * @brief Récupère la catégorie du produit.
 * @return La catégorie du produit.
 */
string Produit::getCategorie() const {
    return this->categorie;
}

/**
 * @brief Récupère l'image associée au produit.
 * @return Le nom de fichier ou l'URL de l'image du produit.
 */
string Produit::getImage() const {
    return this->image;
}

/**
 * @brief Récupère l'ID du produit.
 * @return L'ID du produit.
 */
int Produit::getId() const {
    return this->id;
}

/**
 * @brief Récupère le prix minimum du produit.
 * @return Le prix minimum du produit.
 */
float Produit::getPrixMin() const {
    return prixMin;
}

/**
 * @brief Récupère le prix maximum du produit.
 * @return Le prix maximum du produit.
 */
float Produit::getPrixMax() const {
    return prixMax;
}

/**
 * @brief Définit la description du produit.
 * @param description La description à définir.
 */
void Produit::setDescription(const string & description) {
    this->description = description;
}

/**
 * @brief Définit le prix du produit.
 * @param prix Le prix à définir.
 */
void Produit::setPrix(const float prix) {
    this->prix = prix;
}

/**
 * @brief Définit la catégorie du produit.
 * @param categorie La catégorie à définir.
 */
void Produit::setCategorie(const string& categorie) {
    this->categorie = categorie;
}

/**
 * @brief Définit l'image du produit.
 * @param image L'image à définir.
 */
void Produit::setImage(const string& image) {
    this->image = image;
}

/**
 * @brief Définit l'ID du produit.
 * @param idx L'ID à définir.
 */
void Produit::setId(int idx) {
    this->id = idx;
}

/**
 * @brief Affiche les détails du produit.
 * Cette fonction affiche l'ID, la catégorie, la description et le prix du produit.
 */
void Produit::afficherTout() const {
    cout << "ID: " << id << endl;
    cout << "Catégorie: " << categorie << endl;
    cout << "Description: " << description << endl;
    cout << "Prix: " << prix << "€" << endl << endl;
}
