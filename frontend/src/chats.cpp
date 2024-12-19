/**
 * @file chats.cpp
 * @brief Implémentation de la classe Chats pour gérer les conversations entre acheteurs et vendeurs.
 *
 * Cette classe gère l'affichage des messages échangés entre un acheteur et un vendeur à travers un widget
 * avec des onglets pour chaque conversation. Elle permet de visualiser les détails des messages, des protocoles,
 * ainsi que les informations spécifiques à chaque acheteur et vendeur.
 */

#include "chats.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QToolTip>
#include <QTabWidget>
#include <QDialog>
#include <Acheteur.h>

/**
 * @brief Constructeur de la classe Chats avec identification d'acheteur, de vendeur, et les informations de type, offre et message.
 * @param idAcheteur ID de l'acheteur.
 * @param idVendeur ID du vendeur.
 * @param type Type de message.
 * @param offre Offre associée au message.
 * @param message Contenu du message.
 * @param parent Parent du widget (par défaut).
 */
Chats::Chats(int idAcheteur, int idVendeur, const std::string &type, const std::string &offre, const std::string &message, QWidget *parent)
    : QWidget(parent)
{

}

/**
 * @brief Constructeur de la classe Chats pour initialiser l'interface sans détails spécifiques.
 * @param parent Parent du widget (par défaut).
 */
Chats::Chats(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);
}

/**
 * @brief Associe des boîtes aux lettres à des acheteurs et vendeurs, et génère les onglets de chat.
 * @param acheteur Liste des acheteurs.
 * @param vendeur Liste des vendeurs.
 */
void Chats::setBoites(const std::vector<Acheteur> &acheteur, const std::vector<Vendeur> &vendeur)
{
    achet = acheteur;
    vend = vendeur;
    this->boites.clear();
    this->boites.resize(acheteur.size());

    for (int var = 0; var < acheteur.size(); ++var) {
        this->boites[var] = acheteur[var].getBoiteAuLettresvec();
    }

    createChatTabs();
}

/**
 * @brief Crée les onglets de conversation pour chaque acheteur et ses messages.
 */
void Chats::createChatTabs()
{
    tabWidget->clear();

    for (size_t acheteurIndex = 0; acheteurIndex < boites.size(); ++acheteurIndex) {
        const auto &acheteurBoites = boites[acheteurIndex];

        QTabWidget *innerTabWidget = new QTabWidget();

        for (size_t boiteIndex = 0; boiteIndex < acheteurBoites.size(); ++boiteIndex) {
            const auto &boite = acheteurBoites[boiteIndex];

            QScrollArea *scrollArea = new QScrollArea();
            scrollArea->setWidgetResizable(true);

            QWidget *containerWidget = new QWidget();
            QVBoxLayout *containerLayout = new QVBoxLayout(containerWidget);

            QHBoxLayout *buttonLayout = new QHBoxLayout();
            QPushButton *acheteurButton = new QPushButton("Acheteur", containerWidget);
            QPushButton *vendeurButton = new QPushButton("Vendeur", containerWidget);

            acheteurButton->setToolTip("Show Acheteur details");
            vendeurButton->setToolTip("Show Vendeur details");

            connect(acheteurButton, &QPushButton::clicked, this, [=]() {
                showAcheteurDetails(std::make_shared<Acheteur>(achet[acheteurIndex]));
            });

            connect(vendeurButton, &QPushButton::clicked, this, [=]() {
                showVendeurDetails(std::make_shared<Vendeur>(vend[boiteIndex]));
            });

            buttonLayout->addWidget(acheteurButton);
            buttonLayout->addWidget(vendeurButton);

            containerLayout->addLayout(buttonLayout);

            for (size_t messageIndex = 0; messageIndex < boite->getBoiteAuLettres().size(); ++messageIndex) {
                const auto &message = boite->getMessage(messageIndex);

                QWidget *messageWidget = new QWidget(containerWidget);
                QVBoxLayout *messageLayout = new QVBoxLayout(messageWidget);
                messageLayout->setAlignment(messageIndex % 2 == 0 ? Qt::AlignLeft : Qt::AlignRight);

                QPushButton *offerButton;
                if (message->getObjet() == "search") {
                    offerButton = new QPushButton("Search", messageWidget);
                } else if (message->getObjet() == "offer") {
                    offerButton = new QPushButton(QString("Offer: $%1").arg(message->getOffre()), messageWidget);
                } else if (message->getObjet() == "break-down") {
                    offerButton = new QPushButton("Break-down", messageWidget);
                } else {
                    offerButton = new QPushButton("Accept", messageWidget);
                }

                offerButton->setToolTip("Click to see details");

                connect(offerButton, &QPushButton::clicked, this, [=]() {
                    showDetails(message);
                });

                messageLayout->addWidget(offerButton);
                containerLayout->addWidget(messageWidget);
            }

            QPushButton *protocolButton = new QPushButton("Show Protocol", containerWidget);
            containerLayout->addWidget(protocolButton);

            std::shared_ptr<Protocol> prot = boite->getProtocol();
            connect(protocolButton, &QPushButton::clicked, this, [this, prot]() {
                showProtocol(prot);
            });

            containerWidget->setLayout(containerLayout);
            scrollArea->setWidget(containerWidget);

            innerTabWidget->addTab(scrollArea, QString("Vendeur %1").arg(boiteIndex + 1));
        }

        tabWidget->addTab(innerTabWidget, QString("Acheteur %1").arg(acheteurIndex + 1));
    }
}

/**
 * @brief Affiche les détails d'un message dans une boîte de dialogue.
 * @param message Le message dont les détails doivent être affichés.
 */
void Chats::showDetails(std::shared_ptr<Message> message)
{
    QDialog *detailsDialog = new QDialog(this);
    QVBoxLayout *detailsLayout = new QVBoxLayout(detailsDialog);

    detailsLayout->addWidget(new QLabel(QString("Sender ID: %1").arg(message->getIdEmmeteur())));
    detailsLayout->addWidget(new QLabel(QString("Receiver ID: %1").arg(message->getIdRecep())));

    if (auto voiture = std::dynamic_pointer_cast<Voiture>(message->getProduit())) {
        detailsLayout->addWidget(new QLabel(QString("Product (Car)")));
        detailsLayout->addWidget(new QLabel(QString("Brand: %1").arg(QString::fromStdString(voiture->getBrand()))));
        detailsLayout->addWidget(new QLabel(QString("Model: %1").arg(QString::fromStdString(voiture->getModel()))));
        detailsLayout->addWidget(new QLabel(QString("Year: %1").arg(voiture->getYear())));
        detailsLayout->addWidget(new QLabel(QString("Transmission: %1").arg(QString::fromStdString(voiture->getBoiteDeVitesse()))));
        detailsLayout->addWidget(new QLabel(QString("Kilometres: %1").arg(voiture->getKilometres())));
        detailsLayout->addWidget(new QLabel(QString("Fuel: %1").arg(QString::fromStdString(voiture->getEssence()))));
        detailsLayout->addWidget(new QLabel(QString("MPG: %1").arg(voiture->getMPG())));
        detailsLayout->addWidget(new QLabel(QString("Engine Size: %1").arg(voiture->getTailleEngin())));
    } else {
        detailsLayout->addWidget(new QLabel("Product details not available."));
    }

    detailsDialog->setWindowTitle("Message Details");
    detailsDialog->setModal(true);
    detailsDialog->exec();
}

/**
 * @brief Affiche le protocole d'une boîte aux lettres dans une boîte de dialogue.
 * @param prot Protocole à afficher.
 */
void Chats::showProtocol(std::shared_ptr<Protocol> prot)
{
    QDialog *protocolDialog = new QDialog(this);
    QVBoxLayout *protocolLayout = new QVBoxLayout(protocolDialog);
    protocolLayout->addWidget(new QLabel(QString("Nombre Tours: %1").arg(prot->getNbrTours())));
    protocolLayout->addWidget(new QLabel(QString("Tour Limite Acheter: %1").arg(prot->getNbrOblAchet())));
    protocolLayout->addWidget(new QLabel(QString("Penaite: %1").arg(prot->getPenalite())));
    protocolLayout->addWidget(new QLabel(QString("Nombre Negociation en meme temps :%1").arg(prot->getNegMemeTemps())));
    if(prot->isDifferer()){
        protocolLayout->addWidget(new QLabel(QString("Produit achete peut differer: True")));
    }else{
        protocolLayout->addWidget(new QLabel(QString("Produit achete peut differer: False")));
    }

    protocolDialog->setWindowTitle("Protocol");
    protocolDialog->setModal(true);
    protocolDialog->exec();
}

/**
 * @brief Affiche les détails d'un acheteur dans une boîte de dialogue.
 * @param a Acheteur dont les détails doivent être affichés.
 */
void Chats::showAcheteurDetails(shared_ptr<Acheteur> a)
{
    QDialog *achetDial = new QDialog(this);
    QVBoxLayout *achetLayout = new QVBoxLayout(achetDial);
    achetLayout->addWidget(new QLabel(QString("ID: %1").arg(a->getId())));
    achetLayout->addWidget(new QLabel(QString("Strategie: %1").arg(QString::fromStdString(StrattoInt(a->getStrat())))));
    achetLayout->addWidget(new QLabel(QString("Prix cible: %1").arg(a->getPrix())));

    achetDial->setWindowTitle("Acheteur");
    achetDial->setModal(true);
    achetDial->exec();
}

/**
 * @brief Affiche les détails d'un vendeur dans une boîte de dialogue.
 * @param v Vendeur dont les détails doivent être affichés.
 */
void Chats::showVendeurDetails(shared_ptr<Vendeur> v)
{
    QDialog *vendDial = new QDialog(this);
    QVBoxLayout *vendLay = new QVBoxLayout(vendDial);
    vendLay->addWidget(new QLabel(QString("ID: %1").arg(v->getVendeur_id())));
    vendLay->addWidget(new QLabel(QString("Strategie: %1").arg(QString::fromStdString(StrattoInt(v->getStyle_negociacion())))));
    vendLay->addWidget(new QLabel(QString("Prix cible : %1").arg(v->getPrix())));

    vendDial->setWindowTitle("Vendeur");
    vendDial->setModal(true);
    vendDial->exec();
}

/**
 * @brief Convertit un entier représentant une stratégie en une chaîne de caractères.
 * @param i Valeur entière représentant une stratégie.
 * @return Nom de la stratégie sous forme de chaîne.
 */
string Chats::StrattoInt(int i)
{
    switch (i) {
    case 1:
        return "pas a pas";
    case 2:
        return "Compromis";
    case 3:
        return "Aggressive";
    case 4:
        return "Mirroir";
    case 5:
        return "Ultimatum";
    default:
        return "";
    }
}
