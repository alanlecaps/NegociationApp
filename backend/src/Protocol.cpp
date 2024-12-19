/**
 * @file Protocol.cpp
 * @brief Implémentation de la classe Protocol, représentant les paramètres de protocole dans l'application.
 */

#include "Protocol.h"

// Constructeur
/**
 * @brief Constructeur de la classe Protocol.
 * Initialise les valeurs des paramètres du protocole à zéro ou à leur valeur par défaut.
 */
Protocol::Protocol()
    : nbr_tours(0), nbr_obl_achet(0), penalité(0), neg_meme_temps(0), differer(false) {}

// Implémentations des getters et setters

// nbr_tours
/**
 * @brief Récupère le nombre de tours.
 * @return Le nombre de tours.
 */
int Protocol::getNbrTours() const {
    return nbr_tours;
}

/**
 * @brief Définit le nombre de tours.
 * @param value Le nombre de tours à définir.
 */
void Protocol::setNbrTours(int value) {
    nbr_tours = value;
}

// nbr_obl_achet
/**
 * @brief Récupère le nombre d'acheteurs obligatoires.
 * @return Le nombre d'acheteurs obligatoires.
 */
int Protocol::getNbrOblAchet() const {
    return nbr_obl_achet;
}

/**
 * @brief Définit le nombre d'acheteurs obligatoires.
 * @param value Le nombre d'acheteurs obligatoires à définir.
 */
void Protocol::setNbrOblAchet(int value) {
    nbr_obl_achet = value;
}

// penalité
/**
 * @brief Récupère la valeur de la pénalité.
 * @return La valeur de la pénalité.
 */
int Protocol::getPenalite() const {
    return penalité;
}

/**
 * @brief Définit la valeur de la pénalité.
 * @param value La valeur de la pénalité à définir.
 */
void Protocol::setPenalite(int value) {
    penalité = value;
}

// neg_meme_temps
/**
 * @brief Récupère le nombre de négociations simultanées autorisées.
 * @return Le nombre de négociations simultanées.
 */
int Protocol::getNegMemeTemps() const {
    return neg_meme_temps;
}

/**
 * @brief Définit le nombre de négociations simultanées autorisées.
 * @param value Le nombre de négociations simultanées à définir.
 */
void Protocol::setNegMemeTemps(int value) {
    neg_meme_temps = value;
}

// differer
/**
 * @brief Indique si la négociation peut être différée.
 * @return Vrai si la négociation peut être différée, sinon faux.
 */
bool Protocol::isDifferer() const {
    return differer;
}

/**
 * @brief Définit si la négociation peut être différée.
 * @param value La valeur à définir pour l'attribut `differer`.
 */
void Protocol::setDifferer(bool value) {
    differer = value;
}
