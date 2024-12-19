/**
 * @file Parametres.cpp
 * @brief Implémentation de la classe Parametres, représentant la gestion des paramètres dans l'application.
 */

#include "Parametres.h"
#include "ui_Parametres.h"
#include <vector>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <vector>
#include <QSpinBox>
#include <QTabWidget>
#include <QWidget>

using namespace std;

/**
 * @brief Constructeur de la classe Parametres.
 * @param parent Le widget parent (optionnel).
 * @param nbr_tours Un pointeur vers le nombre de tours.
 * @param vendeurs_param Un pointeur vers un vecteur de paramètres des vendeurs.
 */
Parametres::Parametres(QWidget *parent, int* nbr_tours, std::vector<std::vector<int>>* vendeurs_param)
    : QWidget(parent),
    ui(new Ui::Parametres),
    nbr_tours_ptr(nbr_tours),
    vendeurs_param_ptr(vendeurs_param),
    tours_limites(new int(0)),  // Initialisation à une nouvelle valeur entière 0
    penalite(new int(0)),      // Initialisation de même pour les autres variables
    neg_simult(new int(0)),
    pt_differ(false)
{
    ui->setupUi(this);

    if (!ui->vendorsContainer->layout()) {
        QVBoxLayout *vendorsLayout = new QVBoxLayout(ui->vendorsContainer);
        ui->vendorsContainer->setLayout(vendorsLayout);
    }
    // Ajout dynamique des champs pour les vendeurs dans l'onglet Vendeurs
    connect(ui->numVendorsSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &Parametres::onNumVendorsChanged);

    ui->nombre_tours->setRange(0, 100); // Plage des tours
    connect(ui->nombre_tours, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value){
        *nbr_tours_ptr = value;
    });

    connect(ui->protocolSubmitButton, &QPushButton::clicked, this, &Parametres::onRoundsButtonClicked);

    connect(ui->submitButton, &QPushButton::clicked, this, &Parametres::onSubmit);
}

/**
 * @brief Destructeur de la classe Parametres.
 */
Parametres::~Parametres()
{
}

/**
 * @brief Slot appelé lorsque le nombre de vendeurs change.
 * Cette méthode gère la mise à jour des champs dynamiques pour chaque vendeur.
 * @param count Le nouveau nombre de vendeurs.
 */
void Parametres::onNumVendorsChanged(int count)
{

    QVBoxLayout *vendorsLayout = qobject_cast<QVBoxLayout *>(ui->vendorsContainer->layout());
    if (!vendorsLayout) {
        qWarning() << "vendorsContainer n'a pas de layout!";
        return;
    }

    QLayoutItem *child;
    while ((child = vendorsLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    vendorStrategies.clear();
    vendorProducts.clear();

    for (int i = 0; i < count; ++i) {
        QWidget *vendorWidget = new QWidget();
        QFormLayout *formLayout = new QFormLayout(vendorWidget);

        QLabel *strategyLabel = new QLabel(QString("Stratégie pour le vendeur %1:").arg(i + 1));
        QComboBox *strategyCombo = new QComboBox();
        strategyCombo->addItems({"Pas à pas", "Compromis", "Agressive", "Miroir", "Ultimatum"});
        formLayout->addRow(strategyLabel, strategyCombo);

        QLabel *productsLabel = new QLabel(QString("Nombre de produits pour le vendeur %1:").arg(i + 1));
        QLineEdit *productsInput = new QLineEdit();
        productsInput->setValidator(new QIntValidator(0, 100, this));
        formLayout->addRow(productsLabel, productsInput);

        QLabel *karmaLabel = new QLabel(QString("A partir de quel tour l'acheteur perd du karma").arg(i + 1));
        QSpinBox *karmaInput = new QSpinBox();
        karmaInput->setRange(1, 100);
        formLayout->addRow(karmaLabel, karmaInput);

        vendorWidget->setLayout(formLayout);
        vendorsLayout->addWidget(vendorWidget);

        vendorStrategies.append(strategyCombo);
        vendorProducts.append(productsInput);
        vendorKarma.push_back(karmaInput->value());
    }

    vendorsLayout->invalidate();
    ui->vendorsContainer->adjustSize();
    ui->vendorsScrollArea->setWidgetResizable(true);
    ui->vendorsScrollArea->update();
}

/**
 * @brief Slot appelé lorsque le bouton "Rounds" est cliqué.
 * Cette méthode met à jour les paramètres liés aux tours.
 */
void Parametres::onRoundsButtonClicked()
{

    // Vérification des pointeurs avant d'y accéder
    if (!nbr_tours_ptr) {
        qCritical() << "Erreur : nbr_tours_ptr est nul!";
        return;
    }

    if (!tours_limites) {
        qCritical() << "Erreur : tours_limites est nul!";
        return;
    }

    if (!penalite) {
        qCritical() << "Erreur : penalite est nul!";
        return;
    }

    if (!neg_simult) {
        qCritical() << "Erreur : neg_simult est nul!";
        return;
    }

    // Mise à jour des valeurs depuis les éléments UI
    *nbr_tours_ptr = ui->nombre_tours->value();
    *tours_limites = ui->lim_tour->value();
    *penalite = ui->pen->value();
    *neg_simult = ui->nbr_sim->value();
    pt_differ = false;

    // Émission du signal avec les valeurs mises à jour
    emit submitProtocolClicked(nbr_tours_ptr, tours_limites, penalite, neg_simult, &pt_differ);

}

/**
 * @brief Slot appelé lorsque le bouton "Submit" est cliqué.
 * Cette méthode collecte les paramètres des vendeurs et émet un signal.
 */
void Parametres::onSubmit()
{

    // Redimensionnement de vendeurs_param_ptr en fonction du nombre de stratégies des vendeurs
    vendeurs_param_ptr->resize(vendorStrategies.size());

    for (int i = 0; i < vendorStrategies.size(); ++i) {
        int strategyIndex = vendorStrategies[i]->currentIndex();
        strategyIndex++;
        int productCount = vendorProducts[i]->text().toInt();
        int karmatour = vendorKarma[i];
        (*vendeurs_param_ptr)[i] = {strategyIndex, productCount, karmatour};
    }

    emit submitVendorClicked(*vendeurs_param_ptr);
    this->close();
}
