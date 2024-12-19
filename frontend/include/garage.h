#ifndef GARAGE_H
#define GARAGE_H

#include <QWidget>
#include <QTableWidget>
#include <memory>
#include <vector>
#include "Voiture.h"

class QTableWidget;

class Garage : public QWidget {
    Q_OBJECT


private:
    QTableWidget* tableWidget;
    std::vector<std::shared_ptr<Voiture>> voitures;

public:
    explicit Garage(QWidget* parent = nullptr);
       // Ajouter un produit au garage
    void ajouterVoiture(const vector<shared_ptr<Voiture>> vo);
    void displayVoitures();
    void removeVoiture(int id);
    // Obtenir la liste de toutes les voitures
    std::vector<std::shared_ptr<Voiture>> getVoiture() const;

    // Trouver un produit par modèle et marque
    std::shared_ptr<Voiture> trouverVoitue(const std::string& marque, const std::string& modele);
    std::vector<std::shared_ptr<Voiture>> getAllVoitures() const;
    // Afficher tous les produits disponibles
    void afficherProduits() const;

    /*/ Récupérer tous les produits disponibles dans le garage sous forme de liste de voitures
    void recupererVoituresDispos(std::vector<Produits_dispos>& p_d);
*/
};

#endif // GARAGE_H

