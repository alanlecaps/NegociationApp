#include "Vente.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QLabel>

Vente::Vente(Garage* garage, QWidget* parent)
    : QWidget(parent), garage(garage) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Tableau pour les voitures en vente
    tableWidgetVente = new QTableWidget(this);
    tableWidgetVente->setColumnCount(3);
    tableWidgetVente->setHorizontalHeaderLabels({"ID", "Marque", "Modèle"});
    layout->addWidget(tableWidgetVente);

    QLabel* bandeMaintenance = new QLabel("En Maintenance", this);
    bandeMaintenance->setAlignment(Qt::AlignCenter);
    bandeMaintenance->setStyleSheet("background-color: yellow; color: black; font-weight: bold; padding: 5px;");
    layout->addWidget(bandeMaintenance);

    // Bouton "Vendre"
    QPushButton* vendreButton = new QPushButton("Vendre", this);
    connect(vendreButton, &QPushButton::clicked, this, &Vente::onVendreButtonClicked);
    layout->addWidget(vendreButton);

    displayVoituresVente();
}

void Vente::displayVoituresVente() {
    tableWidgetVente->setRowCount(static_cast<int>(voituresEnVente.size()));
    for (size_t row = 0; row < voituresEnVente.size(); ++row) {
        auto voiture = voituresEnVente[row];
        tableWidgetVente->setItem(static_cast<int>(row), 0, new QTableWidgetItem(QString::number(voiture->getId())));
        tableWidgetVente->setItem(static_cast<int>(row), 1, new QTableWidgetItem(QString::fromStdString(voiture->getBrand())));
        tableWidgetVente->setItem(static_cast<int>(row), 2, new QTableWidgetItem(QString::fromStdString(voiture->getModel())));
        /* tableWidgetVente->setItem(static_cast<int>(row), 3, new QTableWidgetItem(QString::fromStdString(voiture->getBoiteDeVitesse())));
        tableWidgetVente->setItem(static_cast<int>(row), 4, new QTableWidgetItem(QString::fromStdString(voiture->getEssence())));
        tableWidgetVente->setItem(static_cast<int>(row), 5, new QTableWidgetItem(QString::fromStdString(voiture->getDescription())));
        tableWidgetVente->setItem(static_cast<int>(row), 6, new QTableWidgetItem(QString::fromStdString(voiture->getCategorie())));
        tableWidgetVente->setItem(static_cast<int>(row), 7, new QTableWidgetItem(QString::number(voiture->getYear())));
        tableWidgetVente->setItem(static_cast<int>(row), 8, new QTableWidgetItem(QString::number(voiture->getKilometres())));
        tableWidgetVente->setItem(static_cast<int>(row), 9, new QTableWidgetItem(QString::number(voiture->getMPG())));
        tableWidgetVente->setItem(static_cast<int>(row), 10, new QTableWidgetItem(QString::number(voiture->getTailleEngin())));
        tableWidgetVente->setItem(static_cast<int>(row), 11, new QTableWidgetItem(QString::number(voiture->getPrix()))); */
        
    }
}

void Vente::onVendreButtonClicked() {
    afficherGarageDialog();
}

void Vente::afficherGarageDialog() {
    // Crée une boîte de dialogue pour afficher les voitures du garage
    QDialog dialog(this);
    dialog.setWindowTitle("Sélectionner une voiture");

    QVBoxLayout* dialogLayout = new QVBoxLayout(&dialog);

    QTableWidget* garageTable = new QTableWidget(&dialog);
    garageTable->setColumnCount(3);
    garageTable->setHorizontalHeaderLabels({"ID", "Marque", "Modèle"});

    auto voituresGarage = garage->getAllVoitures(); // Assure-toi que cette méthode existe
    garageTable->setRowCount(static_cast<int>(voituresGarage.size()));

    for (size_t row = 0; row < voituresGarage.size(); ++row) {
        auto voiture = voituresGarage[row];
        garageTable->setItem(static_cast<int>(row), 0, new QTableWidgetItem(QString::number(voiture->getId())));
        garageTable->setItem(static_cast<int>(row), 1, new QTableWidgetItem(QString::fromStdString(voiture->getBrand())));
        garageTable->setItem(static_cast<int>(row), 2, new QTableWidgetItem(QString::fromStdString(voiture->getModel())));
    }

    dialogLayout->addWidget(garageTable);

    QPushButton* validerButton = new QPushButton("Valider", &dialog);
    dialogLayout->addWidget(validerButton);

    connect(validerButton, &QPushButton::clicked, [&]() {
        auto selectedRows = garageTable->selectedItems();
        if (selectedRows.isEmpty()) {
            QMessageBox::warning(&dialog, "Erreur", "Aucune voiture sélectionnée !");
            return;
        }

        int row = garageTable->currentRow();
        auto voiture = voituresGarage[row];

        bool ok;
        double prixDeVente = QInputDialog::getDouble(this, "Prix de vente", "Entrez le prix :", 0, 0, 1e6, 2, &ok);

        if (ok) {
            voituresEnVente.push_back(voiture);
            // Retirer la voiture du garage après l'avoir vendue
            garage->removeVoiture(voiture->getId());
            displayVoituresVente();
            garage->displayVoitures();
            QMessageBox::information(this, "Succès", "Voiture ajoutée en vente.");
            dialog.accept();
        }
    });

    dialog.exec();
}
