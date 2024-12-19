/**
 * @file garage.cpp
 * @brief Implémentation de la classe Garage.
 *
 * Ce fichier contient les méthodes d'implémentation de la classe `Garage`, qui permet de gérer une liste de voitures
 * et de les afficher dans une table QTableWidget. Il inclut les fonctions pour ajouter des voitures et les afficher
 * dans une interface graphique avec Qt.
 *
 * @author [Ton Nom]
 * @date [Date]
 */

#include "garage.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDebug>

/**
 * @brief Constructeur de la classe Garage.
 *
 * Ce constructeur initialise le widget graphique `QTableWidget` avec 12 colonnes et un en-tête avec des labels représentant
 * différents attributs des voitures. Il configure également le layout vertical de l'interface.
 *
 * @param parent Le widget parent, utilisé pour la hiérarchie de widgets de Qt.
 */
Garage::Garage(QWidget* parent)
    : QWidget(parent), tableWidget(new QTableWidget(this)), voitures() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Initialisation des colonnes du tableau avec les étiquettes appropriées
    tableWidget->setColumnCount(12); // Nombre de colonnes pour les attributs de la voiture
    tableWidget->setHorizontalHeaderLabels({
        "ID", "Brand", "Model", "Year", "Boite de Vitesse", "Kilometres",
        "Essence", "MPG", "Taille Engin", "Description", "Prix", "Categorie"
    });

    // Ajuste la taille des colonnes pour qu'elles s'étendent sur toute la largeur de la table
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Ajout du QTableWidget au layout
    layout->addWidget(tableWidget);
    setLayout(layout);
}

/**
 * @brief Ajoute une liste de voitures au garage.
 *
 * Cette méthode permet d'ajouter un certain nombre de voitures à la liste interne du garage.
 * Les voitures sont ajoutées à la fin du vecteur `voitures`.
 *
 * @param vo Un vecteur de pointeurs intelligents vers des objets `Voiture` à ajouter au garage.
 */
void Garage::ajouterVoiture(std::vector<std::shared_ptr<Voiture>> vo) {

    // Ajout de chaque voiture du vecteur à la liste interne du garage
    for (int var = 0; var < vo.size(); ++var) {
        voitures.push_back(vo[var]);
    }

}

/**
 * @brief Affiche les voitures dans la table QTableWidget.
 *
 * Cette méthode parcourt la liste des voitures et affiche leurs attributs dans le `QTableWidget`.
 * Chaque ligne du tableau représente une voiture, et chaque cellule contient une information spécifique sur la voiture.
 *
 * Les attributs affichés sont : ID, marque, modèle, année, boîte de vitesses, kilomètres, essence, MPG, taille de l'engin,
 * description, prix et catégorie.
 */
void Garage::displayVoitures() {
    // Mise à jour du nombre de lignes dans la table en fonction du nombre de voitures
    tableWidget->setRowCount(static_cast<int>(voitures.size()));

    // Parcours des voitures et remplissage des cellules de la table
    for (size_t x = 0; x < voitures.size(); ++x) {
        std::shared_ptr<Voiture> v = voitures[x];

        // Remplissage des colonnes de la table avec les attributs de chaque voiture
        tableWidget->setItem(static_cast<int>(x), 0, new QTableWidgetItem(QString::number(v->getId())));
        tableWidget->setItem(static_cast<int>(x), 1, new QTableWidgetItem(QString::fromStdString(v->getBrand())));
        tableWidget->setItem(static_cast<int>(x), 2, new QTableWidgetItem(QString::fromStdString(v->getModel())));
        tableWidget->setItem(static_cast<int>(x), 3, new QTableWidgetItem(QString::number(v->getYear())));
        tableWidget->setItem(static_cast<int>(x), 4, new QTableWidgetItem(QString::fromStdString(v->getBoiteDeVitesse())));
        tableWidget->setItem(static_cast<int>(x), 5, new QTableWidgetItem(QString::number(v->getKilometres())));
        tableWidget->setItem(static_cast<int>(x), 6, new QTableWidgetItem(QString::fromStdString(v->getEssence())));
        tableWidget->setItem(static_cast<int>(x), 7, new QTableWidgetItem(QString::number(v->getMPG())));
        tableWidget->setItem(static_cast<int>(x), 8, new QTableWidgetItem(QString::number(v->getTailleEngin())));
        tableWidget->setItem(static_cast<int>(x), 9, new QTableWidgetItem(QString::fromStdString(v->getDescription())));
        tableWidget->setItem(static_cast<int>(x), 10, new QTableWidgetItem(QString::number(v->getPrix())));
        tableWidget->setItem(static_cast<int>(x), 11, new QTableWidgetItem(QString::fromStdString(v->getCategorie())));
    }
}

std::vector<std::shared_ptr<Voiture>> Garage::getAllVoitures() const {
    return voitures;
}

void Garage::removeVoiture(int id) {
    auto it = std::remove_if(voitures.begin(), voitures.end(), [id](const std::shared_ptr<Voiture>& v) {
        return v->getId() == id;  // Comparaison avec l'ID
    });

    if (it != voitures.end()) {
        // Suppression de la voiture
        voitures.erase(it, voitures.end());
        qDebug() << "Voiture supprimée avec ID:" << id;
    } else {
        qDebug() << "Voiture avec ID" << id << "non trouvée.";
    }
}

