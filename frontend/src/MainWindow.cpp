#include "MainWindow.h"
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <vector>
#include "Parametres.h"
#include "back_end_main.h"
#include "store.h"
#include "Vente.h"
#include "garage.h"
#include "chats.h"
#include "Protocol.h"
#include "StartScreen.h"
#include <string.h>
#include <memory>

/**
 * @class MainWindow
 * @file  MainWindox.cpp
 * @brief Classe représentant la fenêtre principale de l'application.
 *
 * Cette classe gère l'affichage et la logique de navigation entre les différents écrans de l'application.
 * Elle permet également de gérer les paramètres, le magasin, les chats, le garage et la négociation.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), stackedWidget(new QStackedWidget(this)),
    nbr_tours(0), param_vendeurs(), vendeurs(), acheteurs(), p_d(), protocol() {

    // Configuration de la fenêtre principale
    setMinimumSize(500, 400);
    resize(800, 700);

    protocol = std::make_shared<Protocol>();

    // Initialisation des écrans
    startScreen = new StartScreen(this);
    parameterWindow = new Parametres(this, &nbr_tours, &param_vendeurs);
    store = new Store(this);
    chats = new Chats(this);
    garage = new Garage(this);
    vente = new Vente(garage, this);

    // Ajout des écrans au QStackedWidget
    stackedWidget->addWidget(startScreen);
    stackedWidget->addWidget(parameterWindow);
    stackedWidget->addWidget(store);
    stackedWidget->addWidget(chats);
    stackedWidget->addWidget(garage);
    stackedWidget->addWidget(vente);

    // Écran initial
    setCentralWidget(stackedWidget);

    // Connexions des signaux et slots
    connect(startScreen, &StartScreen::startclickedSig, this, &MainWindow::showShop);
    connect(parameterWindow, &Parametres::submitVendorClicked, this, &MainWindow::updateVendeurs);
    connect(parameterWindow, &Parametres::submitProtocolClicked, this, &MainWindow::updateProtocol);
    connect(store, &Store::cartValidated, this, &MainWindow::negocier);

    // Menu principal
    QMenuBar *menuBar = this->menuBar();
    QAction *shopAction =  menuBar->addAction("Shop");
    QAction *chatsAction =  menuBar->addAction("Chats");
    QAction *garageAction = menuBar->addAction("Garage");
    QAction *venteAction = menuBar->addAction("Vendre");
    QAction *parametresAction =menuBar->addAction("Parametres");

    // Connexion des actions du menu
    connect(shopAction, &QAction::triggered, this, &MainWindow::showShop);
    connect(chatsAction, &QAction::triggered, this, &MainWindow::showChats);
    connect(garageAction, &QAction::triggered, this, &MainWindow::showGarage);
    connect(parametresAction, &QAction::triggered, this, &MainWindow::showParametres);
    connect(venteAction, &QAction::triggered, this, &MainWindow::showVente); // Connecter l'action Vente

    bool f = true;
    int a = 0;
    std::vector<std::vector<int>> temp;
    updateProtocol(&a, &a, &a, &a, &f);
    updateVendeurs(temp);

    // Jouer la musique au démarrage
    startScreen->playStartupSound();
    stackedWidget->setCurrentWidget(startScreen);
}

MainWindow::~MainWindow() {}

/**
 * @brief Affiche la fenêtre des paramètres.
 *
 * Cette fonction permet d'afficher l'écran permettant de configurer les paramètres
 * liés aux vendeurs et à la négociation.
 */
void MainWindow::showParametres() {
    if (!parameterWindow) {
        parameterWindow = new Parametres(this, &nbr_tours, &param_vendeurs);
        stackedWidget->addWidget(parameterWindow);
    }
    stackedWidget->setCurrentWidget(parameterWindow);
}

/**
 * @brief Affiche l'écran du magasin.
 *
 * Cette fonction permet d'afficher l'écran du magasin où les produits sont affichés
 * et où l'utilisateur peut les ajouter à son panier.
 */
void MainWindow::showShop() {
    if (!store) {
        store = new Store(this);
        stackedWidget->addWidget(store);
    }
    recuperer_tous_produits(p_d, vendeurs);
    store->setProducts(p_d);
    stackedWidget->setCurrentWidget(store);
}

/**
 * @brief Affiche l'écran des chats.
 *
 * Cette fonction permet d'afficher l'écran des chats où l'utilisateur peut communiquer avec les vendeurs.
 */
void MainWindow::showChats() {
    if (!chats) {
        chats = new Chats(this);
        stackedWidget->addWidget(chats);
    }
    stackedWidget->setCurrentWidget(chats);
}

/**
 * @brief Affiche l'écran du garage.
 *
 * Cette fonction permet d'afficher l'écran du garage où l'utilisateur peut voir ses voitures.
 */
void MainWindow::showGarage() {
    if (!garage) {
        garage = new Garage(this);
        stackedWidget->addWidget(garage);
    }
    stackedWidget->setCurrentWidget(garage);
}

void MainWindow::showVente() {
    if (!vente) {
        vente = new Vente(garage, this);
        stackedWidget->addWidget(vente);
    }
    stackedWidget->setCurrentWidget(vente);
}


/**
 * @brief Lance la négociation entre les acheteurs et les vendeurs.
 *
 * Cette fonction initialise les acheteurs et les vendeurs, configure la négociation,
 * et affiche le résultat dans le garage et les chats.
 *
 * @param product Liste des produits choisis par l'utilisateur.
 */
void MainWindow::negocier(const std::vector<std::tuple<Voiture, int>>& product) {

    qDebug() <<"Debug 1";
    int achet_num = product.size();
    int vendeurs_size = static_cast<int>(vendeurs.size());
    qDebug() <<"Debug 2";

    acheteurs.clear();

    acheteur_Initialisation(acheteurs, achet_num, vendeurs_size);

    qDebug() <<"Debug 3";

    cout << vendeurs_size << "//" << achet_num << "//" << achet_num << endl;
    for (const auto &ven : vendeurs) {
        cout << ven.getVendeur_id() << endl;
    }
    for (const auto &ach : acheteurs) {
        cout << ach.getId() << endl;
    }
    bal_Initialisation(vendeurs_size, achet_num, vendeurs, acheteurs, protocol);
    qDebug() <<"Debug 4";

    for (int var = 0; var < achet_num; ++var) {
        shared_ptr<Voiture> p = std::make_shared<Voiture>(std::get<0>(product[var]));
        acheteurs[var].setStrat(std::get<1>(product[var]));
        acheteurs[var].setProd(p);
        qDebug() << acheteurs[var].getStrat();
    }

    vector<shared_ptr<Voiture>> voit;
    vector<shared_ptr<BoiteAuLettres>> bal_finales = start_negocier(acheteurs, vendeurs, voit);

    garage->ajouterVoiture(voit);
    garage->displayVoitures();
    chats->setBoites(acheteurs, vendeurs);
    recuperer_tous_produits(p_d, vendeurs);
    store->setProducts(p_d);
    stackedWidget->setCurrentWidget(chats);
}

/**
 * @brief Met à jour le protocole de négociation avec les nouveaux paramètres.
 *
 * Cette fonction prend en compte les paramètres fournis pour ajuster le protocole de négociation.
 *
 * @param nbr_rounds Nombre de tours de la négociation.
 * @param tours_limites Nombre de tours maximum pour chaque négociation.
 * @param penalite Pénalité pour les tours dépassés.
 * @param neg_simult Nombre de négociations simultanées.
 * @param pt_differ Indicateur de différenciation dans la négociation.
 */
void MainWindow::updateProtocol(int* nbr_rounds, int* tours_limites, int* penalite, int* neg_simult, bool* pt_differ) {
    if (*nbr_rounds == 0) {
        *nbr_rounds = 5;
    }
    if (*tours_limites == 0) {
        *tours_limites = 4;
    }
    if (*penalite == 0) {
        *penalite = 5;
    }
    if(*neg_simult==0){
        *neg_simult=3;
    }
    protocol->setNbrTours(*nbr_rounds);
    protocol->setNbrOblAchet(*tours_limites);
    protocol->setPenalite(*penalite);
    protocol->setNegMemeTemps(*neg_simult);
    protocol->setDifferer(pt_differ);

    qDebug() << "Protocol parameters updated:"
             << "nbr_tours:" << *nbr_rounds
             << "tours_limites:" << *tours_limites
             << "penalite:" << *penalite
             << "neg_simult:" << *neg_simult
             << "differ:" << pt_differ;
}

/**
 * @brief Met à jour les vendeurs avec les paramètres fournis.
 *
 * Cette fonction initialise les vendeurs avec les nouveaux paramètres donnés et met à jour les produits du magasin.
 *
 * @param vendeurs_param_ptr Paramètres des vendeurs.
 */
void MainWindow::updateVendeurs(std::vector<std::vector<int>>& vendeurs_param_ptr){
    if(vendeurs_param_ptr.empty()){
        vendeurs_param_ptr.resize(5);
        (vendeurs_param_ptr)[0] = {1, 10, 3};
        (vendeurs_param_ptr)[1] = {2, 34, 4};
        (vendeurs_param_ptr)[2] = {1, 123,4};
        (vendeurs_param_ptr)[3] = {2, 234, 4};
        (vendeurs_param_ptr)[4] = {1, 1,4};
    }
    vendeurs.clear();
    vendeur_Initialisation(vendeurs,vendeurs_param_ptr);
    recuperer_tous_produits(p_d,vendeurs);
    store->setProducts(p_d);
    stackedWidget->setCurrentWidget(store);
}
