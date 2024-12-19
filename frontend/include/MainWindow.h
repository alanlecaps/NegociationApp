#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QMenuBar>
#include "StartScreen.h"
#include "Parametres.h"
#include "Vendeur.h"
#include "Acheteur.h"
#include "Protocol.h"
#include "back_end_main.h"
#include "store.h"
#include "chats.h"
#include "Vente.h"
#include "garage.h"
#include <tuple>
#include <vector>
#include <memory>

class Parametres;
class Store;
class Garage;
class Chats;
class StartScreen;
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateProtocol(int* nbr_rounds, int* tours_limites, int* penalite, int* neg_simult, bool* pt_differ);
    void updateVendeurs(std::vector<std::vector<int>>& vendeurs_param_ptr);

private slots:
    void showShop();
    void showChats();
    void showGarage();
    void showParametres();
    void showVente();
    void negocier(const std::vector<std::tuple<Voiture, int>>& product);

private:
    QStackedWidget *stackedWidget;
    Parametres *parameterWindow;
    QWidget *mainMenuScreen;

    // Widgets supplémentaires
    Store *store = nullptr;
    Chats *chats = nullptr;
    Garage *garage = nullptr;
    StartScreen *startScreen; // Déclaration du StartScreen comme membre
    Vente *vente = nullptr;

    // Données pour la logique
    int nbr_tours;
    std::vector<std::vector<int>> param_vendeurs;
    std::vector<Vendeur> vendeurs;
    std::vector<Acheteur> acheteurs;
    std::vector<Produits_dispos> p_d;
    std::vector<std::vector<Produits_dispos>> produits_selectionnees;
    std::shared_ptr<Protocol> protocol;
};

#endif // MAINWINDOW_H

