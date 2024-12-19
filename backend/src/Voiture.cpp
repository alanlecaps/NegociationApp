/**
 * \file Voiture.cpp
 * \brief Implémentation de la classe Voiture.
 *
 * Ce fichier contient l'implémentation des méthodes de la classe `Voiture`, qui gère les informations relatives
 * à une voiture, telles que la marque, le modèle, l'année de fabrication, les kilomètres, la consommation de carburant, etc.
 * La classe permet également d'afficher ces informations et de les modifier via des méthodes getter et setter.
 *
 * \author Lylia
 * \date Décembre 2024
 */

#include "Voiture.h"
#include "string"
#include "iostream"

using namespace std;

// Destructeur de la classe Voiture
/**
 * \brief Destructeur de la classe Voiture.
 *
 * Ce destructeur est utilisé pour nettoyer les ressources allouées à l'objet Voiture si nécessaire.
 * Pour l'instant, il ne fait rien car la gestion mémoire est simple.
 */
Voiture::~Voiture() {}

// Méthodes getter
/**
 * \brief Retourne la marque de la voiture.
 *
 * \return La marque de la voiture.
 */
string Voiture::getBrand() const {
    return brand;
}

/**
 * \brief Retourne le modèle de la voiture.
 *
 * \return Le modèle de la voiture.
 */
string Voiture::getModel() const {
    return model;
}

/**
 * \brief Retourne l'année de fabrication de la voiture.
 *
 * \return L'année de fabrication de la voiture.
 */
int Voiture::getYear() const {
    return year;
}

/**
 * \brief Retourne le type de boîte de vitesses de la voiture.
 *
 * \return Le type de boîte de vitesses.
 */
string Voiture::getBoiteDeVitesse() const {
    return boite_de_vitesse;
}

/**
 * \brief Retourne le kilométrage de la voiture.
 *
 * \return Le kilométrage de la voiture en kilomètres.
 */
int Voiture::getKilometres() const {
    return kilometres;
}

/**
 * \brief Retourne le type de carburant de la voiture.
 *
 * \return Le type de carburant utilisé par la voiture (essence, diesel, etc.).
 */
string Voiture::getEssence() const {
    return essence;
}

/**
 * \brief Retourne la consommation de carburant en miles par gallon (MPG).
 *
 * \return La consommation de carburant en MPG.
 */
float Voiture::getMPG() const {
    return mpg;
}

/**
 * \brief Retourne la taille du moteur de la voiture.
 *
 * \return La taille du moteur en litres.
 */
float Voiture::getTailleEngin() const {
    return taille_engin;
}

// Méthodes setter
/**
 * \brief Définit la marque de la voiture.
 *
 * \param b La nouvelle marque à attribuer à la voiture.
 */
void Voiture::setBrand(const string& b) {
    brand = b;
}

/**
 * \brief Définit le modèle de la voiture.
 *
 * \param m Le nouveau modèle à attribuer à la voiture.
 */
void Voiture::setModel(const string& m) {
    model = m;
}

/**
 * \brief Définit l'année de fabrication de la voiture.
 *
 * \param y La nouvelle année de fabrication de la voiture.
 */
void Voiture::setYear(int y) {
    year = y;
}

/**
 * \brief Définit le type de boîte de vitesses de la voiture.
 *
 * \param bv Le nouveau type de boîte de vitesses (manuelle, automatique, etc.).
 */
void Voiture::setBoiteDeVitesse(const string& bv) {
    boite_de_vitesse = bv;
}

/**
 * \brief Définit le kilométrage de la voiture.
 *
 * \param km Le nouveau kilométrage de la voiture.
 */
void Voiture::setKilometres(int km) {
    kilometres = km;
}

/**
 * \brief Définit le type de carburant de la voiture.
 *
 * \param e Le type de carburant (essence, diesel, etc.).
 */
void Voiture::setEssence(const string& e) {
    essence = e;
}

/**
 * \brief Définit la consommation en MPG de la voiture.
 *
 * \param mpg_val La nouvelle consommation en miles par gallon (MPG).
 */
void Voiture::setMPG(float mpg_val) {
    mpg = mpg_val;
}

/**
 * \brief Définit la taille du moteur de la voiture.
 *
 * \param taille La nouvelle taille du moteur en litres.
 */
void Voiture::setTailleEngin(float taille) {
    taille_engin = taille;
}

/**
 * \brief Affiche les informations complètes de la voiture.
 *
 * Cette méthode affiche les informations détaillées de la voiture, y compris celles héritées de la classe `Produit`.
 */
void Voiture::afficherTout() const {
    cout << endl << endl;
    Produit::afficherTout();  // Affiche les informations héritées de la classe Produit
    cout << endl << "Marque: " << brand << "\nModele: " << model << "\nAnnee: " << year
         << "\nBoîte de Vitesse: " << boite_de_vitesse << "\nKilometres: " << kilometres
         << "\nEssence: " << essence << "\nMPG: " << mpg
         << "\nTaille du Moteur: " << taille_engin << endl;
}
