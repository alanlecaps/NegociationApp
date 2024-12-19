/**
 * @file StartScreen.cpp
 * @brief Implémentation de l'écran de démarrage de l'application CarDealer.
 * Cet écran contient un fond d'écran, un texte de bienvenue et un bouton pour commencer.
 */

#include "StartScreen.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QResizeEvent>
#include <QPixmap>
#include <QDir>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QDebug>

/**
 * @brief Constructeur de l'écran de démarrage.
 * Initialise l'interface avec un fond d'écran, un texte de bienvenue et un bouton pour commencer.
 * Charge également un fichier audio de démarrage.
 * @param parent Le parent QWidget.
 */
StartScreen::StartScreen(QWidget *parent) : QWidget(parent),
    mediaPlayer(new QMediaPlayer(this)),
    audioOutput(new QAudioOutput(this)) {
    // Appliquer un style pour le fond d'écran
    backgroundLabel = new QLabel(this);

    QPixmap background("../../data/6907007.jpg");

    backgroundLabel->setPixmap(background);
    backgroundLabel->setScaledContents(true);  // Redimensionne l'image si nécessaire
    backgroundLabel->setAlignment(Qt::AlignCenter);  // Centrer l'image

    // Configure le lecteur audio
    mediaPlayer->setAudioOutput(audioOutput);

    // Charge un fichier audio (assurez-vous que le fichier est dans le bon chemin)
    mediaPlayer->setSource(QUrl::fromLocalFile("../../data/startup.mp3"));
    // Démarre la lecture du son
    mediaPlayer->play();

    // Texte de bienvenue
    welcomeText = new QLabel("CarDealer vous souhaite la bienvenue !<br> "
                             "*  Trouvez votre bonheur en un clic et démarrez votre aventure !  *", this);
    welcomeText->setStyleSheet("font-size: 22px; color: black; font-weight: bold;padding: 20px;");
    welcomeText->setAlignment(Qt::AlignCenter);  // Aligner le texte sur toute la largeur

    // Pour forcer l'élargissement du texte et remplir la largeur de l'écran
    welcomeText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // Bouton pour commencer
    startButton = new QPushButton("Let's go ! ", this);
    startButton->setStyleSheet("font-size: 22px; color: Black; padding: 1px; background-color: rgba(255, 255, 255, 0.7);");
    connect(startButton, &QPushButton::clicked, this, &StartScreen::playButtonSound);  // Connecter le clic du bouton au son

    // Agencement vertical
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(welcomeText, 0, Qt::AlignTop | Qt::AlignHCenter);  // Positionner le texte en haut et centré
    layout->addWidget(startButton, 0, Qt::AlignBottom | Qt::AlignHCenter);  // Positionner le bouton en bas et centré
    layout->setSpacing(20);  // Espacement entre le texte et le bouton
    setLayout(layout);

    // Connecter le bouton au signal
    connect(startButton, &QPushButton::clicked, this, &StartScreen::startClicked);
}

/**
 * @brief Destructeur de l'écran de démarrage.
 * Libère les ressources allouées par l'écran de démarrage.
 */
StartScreen::~StartScreen() {
    // Libérer les ressources
    delete backgroundLabel;
    delete welcomeText;
    delete startButton;
    delete mediaPlayer;
    delete audioOutput;
}

/**
 * @brief Slot exécuté lorsque le bouton "Let's go!" est cliqué.
 * Émet un signal pour indiquer que l'écran de démarrage a été validé.
 */
void StartScreen::startClicked() {
    // Logique à exécuter lorsque le bouton est cliqué
    emit startclickedSig();
}

/**
 * @brief Gestionnaire d'événements pour le redimensionnement de la fenêtre.
 * Permet de redimensionner l'image de fond lorsque la taille de la fenêtre change.
 * @param event L'événement de redimensionnement.
 */
void StartScreen::resizeEvent(QResizeEvent* event) {
    backgroundLabel->setGeometry(0, 0, event->size().width(), event->size().height());
}

/**
 * @brief Joue le son de démarrage.
 * Cette fonction semble redondante, car le son est déjà joué dans le constructeur.
 * Toutefois, elle peut être utilisée pour jouer un autre son.
 */
void StartScreen::playStartupSound() {
    mediaPlayer->setSource(QUrl::fromLocalFile("../../data/audio.mp3"));
    mediaPlayer->play();
}

/**
 * @brief Joue un son général, appelé à partir de la fonction publique `playSound()`.
 */
void StartScreen::playSound() {
    playStartupSound();  // Appel de la méthode privée depuis la méthode publique
}

/**
 * @brief Joue un son spécifique lorsque le bouton "Let's go!" est cliqué.
 */
void StartScreen::playButtonSound() {
    QMediaPlayer *player = new QMediaPlayer();
    player->setAudioOutput(audioOutput);  // Connectez à la sortie audio
    player->setSource(QUrl::fromLocalFile("../../data/bouton.mp3"));  // Remplacez le chemin par celui du fichier son
    audioOutput->setVolume(1.0);  // Volume maximal (valeur entre 0.0 et 1.0)
    player->play();
}

/**
 * @brief Accesseur pour obtenir le bouton de démarrage.
 * @return Le bouton de démarrage.
 */
QPushButton* StartScreen::getStartButton() const {
    return startButton;
}
