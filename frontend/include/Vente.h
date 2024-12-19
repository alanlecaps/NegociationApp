#ifndef VENTE_H
#define VENTE_H

#include <QWidget>
#include <QTableWidget>
#include <vector>
#include <memory>
#include <QDialog>
#include "garage.h"

class Vente : public QWidget {
    Q_OBJECT

public:
    explicit Vente(Garage* garage, QWidget* parent = nullptr);

private slots:
    void onVendreButtonClicked(); // Gestion du bouton "Vendre"

private:
    QTableWidget* tableWidgetVente;
    Garage* garage;
    std::vector<std::shared_ptr<Voiture>> voituresEnVente;

    void displayVoituresVente();  // Afficher les voitures en vente
    void afficherGarageDialog(); // Afficher le garage et gérer la sélection
};

#endif // VENTE_H
