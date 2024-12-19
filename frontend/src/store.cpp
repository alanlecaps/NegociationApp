/**
 * @file store.cpp
 * @brief Implémentation de la classe Store pour la gestion des produits et du panier dans un magasin.
 *
 * Ce fichier contient l'implémentation de la classe Store, qui permet aux utilisateurs de filtrer les produits,
 * de visualiser les produits, de les ajouter au panier et de sélectionner des stratégies d'achat. Il offre une interface
 * pour afficher et gérer une liste de produits avec des fonctionnalités de filtrage et de panier.
 */

#include "store.h"
#include "ui_store.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QComboBox>
#include <QWidget>
#include <tuple>


/**
 * @brief Constructeur de la classe Store.
 *
 * Le constructeur configure l'interface utilisateur, y compris le champ de filtrage, la zone de défilement pour les produits,
 * et un bouton pour visualiser le panier.
 *
 * @param parent Le widget parent de cette instance de Store.
 */


Store::Store(QWidget *parent)    : QWidget(parent), ui(new Ui::Store)
{

    // Layout setup
    ui->setupUi(this);

    // Configuration du layout principal
    QWidget *firstTab = ui->tabWidget->widget(0);
    QVBoxLayout *mainLayout = new QVBoxLayout(firstTab);

    // Champ de texte pour filtrer les produits
    filterEdit = new QLineEdit(this);
    filterEdit->setPlaceholderText("Filtrer par modèle ou marque...");
    connect(filterEdit, &QLineEdit::textChanged, this, &Store::filterProducts);
    mainLayout->addWidget(filterEdit);


    // Configuration de la zone de défilement

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);

    // Conteneur pour les produits
    productsContainer = new QWidget();
    productsLayout = new QVBoxLayout(productsContainer);
    scrollArea->setWidget(productsContainer);


    // Button to view the cart
    QPushButton *viewCartButton = ui->CartButton;
    connect(viewCartButton, &QPushButton::clicked, this, &Store::viewCart);
    connect(ui->ajout,&QPushButton::clicked,this,&Store::ajouterProduit);

    setLayout(mainLayout);
}

/**
 * @brief Définit la liste des produits à afficher dans le magasin.
 *
 * Cette fonction permet de définir la liste des produits disponibles dans le magasin. Elle prend en paramètre un vecteur
 * de produits (type `Produits_dispos`) et les affiche dans l'interface.
 *
 * @param products Un vecteur de produits disponibles (de type `Produits_dispos`).
 */
void Store::setProducts(const std::vector<Produits_dispos>& products)
{
    originalProducts = products;  // Sauvegarde la liste originale
    displayProducts(products);    // Affiche les produits
}

/**
 * @brief Affiche la liste des produits dans le magasin.
 *
 * Cette fonction crée un widget pour chaque produit et l'ajoute au layout de l'interface utilisateur. Elle affiche
 * chaque produit avec ses informations comme la marque, le modèle, les prix et la quantité disponible.
 *
 * @param products Un vecteur de produits à afficher.
 */
void Store::displayProducts(const std::vector<Produits_dispos>& products)
{
    // Suppression des widgets existants
    QLayoutItem *item;
    while ((item = productsLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Ajout des produits au layout
    for (const Produits_dispos &product : products) {
        QWidget *productWidget = new QWidget();
        QVBoxLayout *productLayout = new QVBoxLayout(productWidget);

        // Création d'un label avec les informations du produit
        QLabel *label = new QLabel(QString("Marque: %1, Modèle: %2, Fourchette de Prix: $%3 - $%4, Quantité: %5")
                                       .arg(QString::fromStdString(product.marque))
                                       .arg(QString::fromStdString(product.modele))
                                       .arg(product.prix_min)
                                       .arg(product.prix_max)
                                       .arg(product.nbr));
        productLayout->addWidget(label);

        // Bouton pour ajouter le produit au panier
        QPushButton *selectButton = new QPushButton("Ajouter au Panier", productWidget);
        connect(selectButton, &QPushButton::clicked, this, [=]() {
            addToCart(product);  // Ajoute le produit au panier lorsque le bouton est cliqué
        });
        productLayout->addWidget(selectButton);

        productWidget->setLayout(productLayout);
        productsLayout->addWidget(productWidget);
    }
    productsLayout->addStretch();
}

/**
 * @brief Filtre les produits en fonction du texte saisi dans le champ de filtrage.
 *
 * Cette fonction filtre les produits en fonction de l'entrée de l'utilisateur. Si la marque ou le modèle d'un produit
 * contient le texte de recherche, ce produit sera inclus dans la liste filtrée.
 */
void Store::filterProducts()
{
    QString filterText = filterEdit->text().toLower();  // Texte saisi par l'utilisateur
    std::vector<Produits_dispos> filteredProducts;

    // Filtrage des produits en fonction du texte
    for (const auto &product : originalProducts) {
        QString marque = QString::fromStdString(product.marque).toLower();
        QString modele = QString::fromStdString(product.modele).toLower();

        if (marque.contains(filterText) || modele.contains(filterText)) {
            filteredProducts.push_back(product);
        }
    }
    displayProducts(filteredProducts);  // Affiche les produits filtrés
}

/**
 * @brief Ajoute un produit au panier avec un prix choisi par l'utilisateur.
 *
 * Cette fonction permet d'ajouter un produit au panier avec un prix que l'utilisateur choisit dans une boîte de dialogue.
 * Si le prix est valide, le produit est ajouté au panier.
 *
 * @param product Le produit à ajouter au panier.
 */
void Store::addToCart(const Produits_dispos &product)
{
    // Copie du produit pour modification
    Produits_dispos selectedProduct = product;
    Voiture voit=Voiture();
    voit.setBrand(selectedProduct.marque);
    voit.setModel(selectedProduct.modele);

    // Affiche une boîte de dialogue pour entrer le prix souhaité
    bool ok;
    double desiredPrice = QInputDialog::getDouble(this, "Entrer le prix souhaité",
                                                  QString("Entrez votre prix souhaité pour %1 %2 (Fourchette: $%3 - $%4):")
                                                      .arg(QString::fromStdString(selectedProduct.marque))
                                                      .arg(QString::fromStdString(selectedProduct.modele))
                                                      .arg(selectedProduct.prix_min)
                                                      .arg(selectedProduct.prix_max),
                                                  selectedProduct.prix_min, 0, 1000000, 2, &ok);

    if (ok) {
        voit.setPrix(static_cast<float>(desiredPrice)); // Mise à jour avec le prix choisi
        cart.push_back({voit, 0});  // Ajout au panier



        // Affiche un message pour confirmer l'ajout
        QMessageBox::information(this, "Produit ajouté",
                                 QString("Ajouté au panier:\nMarque: %1\nModèle: %2\nPrix: $%3\nQuantité: %4")

                                     .arg(QString::fromStdString(selectedProduct.marque))
                                     .arg(QString::fromStdString(selectedProduct.modele))
                                     .arg(desiredPrice)
                                     .arg(selectedProduct.nbr));
    }
}


void Store::ajouterProduit(){
    // Copie du produit pour modification
    Voiture voit=Voiture();
    // Boîte de dialogue pour le prix souhaité
    bool ok;
    double desiredPrice = QInputDialog::getDouble(this, "Input Value", "Enter a value:",
                                           1000.0,          // Initial value
                                           0.0,             // Minimum value
                                           1000000.0,       // Maximum value
                                           2,               // Number of decimals
                                           &ok);            // Ok status pointer
    if (ok){
        int anne=ui->annee_c->value();
        string bdv= ui->bdv_c->currentText().toStdString();
        if(bdv=="Tout"){
            bdv="";
        }
        int kilometres= ui->km_c->value();
        string essence= ui->esse_c->currentText().toStdString();
        if(essence=="Tout"){
            essence="";
        }
        int mpg= ui->mpg_c->value();
        double taille_e= ui->tailleE_c->value();
        voit.setPrix(static_cast<float>(desiredPrice)) ; // Mise à jour avec le prix choisi
        voit.setYear(anne);
        voit.setBoiteDeVitesse(bdv);
        voit.setKilometres(kilometres);
        voit.setEssence(essence);
        voit.setMPG(mpg);
        voit.setTailleEngin(taille_e);
        cart.push_back({voit, 0});  // Ajout au panier

        QMessageBox::information(this,"Product Added", QString("Marque: %1, Modèle: %2, Year: %3, BoitedeVitesse: %4, Kilometres: %5, Essence: %6, MPG: %7, Engin: %8\n")
                                                            .arg(QString::fromStdString(voit.getBrand()))
                                                            .arg(QString::fromStdString(voit.getModel()))
                                                            .arg(voit.getYear())
                                                            .arg(QString::fromStdString(voit.getBoiteDeVitesse()))
                                                            .arg(voit.getKilometres())
                                                            .arg(QString::fromStdString(voit.getEssence()))
                                                            .arg(voit.getMPG())
                                                            .arg(voit.getTailleEngin()));
    }
}

/**
 * @brief Affiche le contenu du panier.
 *
 * Cette fonction permet de voir les produits dans le panier, avec la stratégie choisie et le prix total des produits.
 * Si le panier est vide, elle affiche un message d'information.
 */

void Store::viewCart()
{
    if (cart.empty()) {
        QMessageBox::information(this, "Panier", "Votre panier est vide.");
        return;
    }


    // Vector to store product details (Product, Strategy)
    std::vector<std::tuple<Voiture, int>> productDetails;

    QString cartDetails;
    double totalPrice = 0;

    // Collecte les détails pour chaque produit dans le panier
    for (const auto &product : cart) {

        // Ajoute les détails du produit au résumé du panier
        cartDetails += QString("Marque: %1, Modèle: %2, Year: %3, BoitedeVitesse: %4, Kilometres: %5, Essence: %6, MPG: %7, Engin: %8\n")
                           .arg(QString::fromStdString(std::get<0>(product).getBrand()))
                           .arg(QString::fromStdString(std::get<0>(product).getModel()))
                           .arg(std::get<0>(product).getYear())
                           .arg(QString::fromStdString(std::get<0>(product).getBoiteDeVitesse()))
                           .arg(std::get<0>(product).getKilometres())
                           .arg(QString::fromStdString(std::get<0>(product).getEssence()))
                           .arg(std::get<0>(product).getMPG())
                           .arg(std::get<0>(product).getTailleEngin());



        // Affiche une boîte de dialogue pour choisir la stratégie d'achat
        QDialog strategyDialog(this);
        strategyDialog.setWindowTitle("Choisir la stratégie");

        QVBoxLayout *layout = new QVBoxLayout(&strategyDialog);
        QLabel *infoLabel = new QLabel(
            QString("Veuillez sélectionner une stratégie pour le produit:\nMarque: %1, Modèle: %2")
                .arg(QString::fromStdString(std::get<0>(product).getBrand()))
                .arg(QString::fromStdString(std::get<0>(product).getModel()))
            );
        layout->addWidget(infoLabel);

        QComboBox *strategyDropdown = new QComboBox(&strategyDialog);
        strategyDropdown->addItem("Stratégie pas à pas");
        strategyDropdown->addItem("Stratégie compromis");
        strategyDropdown->addItem("Stratégie agressive");
        strategyDropdown->addItem("Stratégie miroir");
        strategyDropdown->addItem("Stratégie ultimatum");
        layout->addWidget(strategyDropdown);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        layout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, &strategyDialog, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, &strategyDialog, &QDialog::reject);

        // Affiche la boîte de dialogue et traite la sélection
        int selectedStrategyIndex = -1;
        if (strategyDialog.exec() == QDialog::Accepted) {
            selectedStrategyIndex = strategyDropdown->currentIndex();
            selectedStrategyIndex++;  // Incrémente l'index pour le rendre 1-based
        } else {
            QMessageBox::information(this, "Annulé", "La sélection de la stratégie a été annulée.");
            return;  // Quitte si la sélection est annulée
        }

        // Enregistre les détails du produit avec la stratégie choisie
        productDetails.emplace_back(std::get<0>(product), selectedStrategyIndex);

        // Calculate total price
        totalPrice +=std::get<0>(product).getPrix();

    }

    // Prépare et affiche le résumé du panier
    QString summary = "Résumé du Panier :\n\n" + cartDetails + "\n";
    for (const auto &detail : productDetails) {
        const auto &produit = std::get<0>(detail);
        int strategyIndex = std::get<1>(detail);

        summary += QString("Marque: %1, Modèle: %2, Prix: $%3, Stratégie: %4\n")
                       .arg(QString::fromStdString(produit.getBrand()))
                       .arg(QString::fromStdString(produit.getModel()))
                       .arg(produit.getPrix())
                       .arg(strategyIndex); // Display strategy as 1-based index

    }
    summary += QString("\nPrix Total : $%1").arg(totalPrice);

    QMessageBox::information(this, "Résumé du Panier", summary);

    // Émet le signal avec les détails du panier validé
    emit cartValidated(productDetails);

    // Vide le panier après validation
    cart.clear();
}

