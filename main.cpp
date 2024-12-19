/**
 * @file main.cpp
 * @brief Point d'entrée du programme.
 *
 * Ce fichier contient la fonction `main` qui sert de point d'entrée pour l'application Qt. Il crée l'instance de
 * l'application et de la fenêtre principale, puis lance l'exécution de l'application.
 *
 */

#include "back_end_main.h"
#include "MainWindow.h"
#include <QApplication>

/**
 * @brief Fonction principale du programme.
 *
 * Cette fonction initialise l'application Qt, crée la fenêtre principale de l'application et la montre à l'utilisateur.
 * Ensuite, elle entre dans la boucle d'exécution de l'application en appelant `app.exec()`.
 *
 * @param argc Nombre d'arguments passés en ligne de commande.
 * @param argv Tableau des arguments passés en ligne de commande.
 * @return Le code de sortie de l'application.
 */
int main(int argc, char *argv[]) {
    // Initialisation de l'application Qt
    QApplication app(argc, argv);

    // Création de la fenêtre principale
    MainWindow mainWindow;

    // Affichage de la fenêtre principale
    mainWindow.show();

    // Exécution de la boucle d'événements de l'application
    return app.exec();
}
