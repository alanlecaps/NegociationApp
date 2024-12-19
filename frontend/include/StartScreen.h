#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSizePolicy>

class StartScreen : public QWidget
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);
    void playStartupSound();  // Déclaration de la méthode ici
    void playSound();  // Fonction publique qui appelle playStartupSound
    ~StartScreen();
    void playButtonSound();  // Méthode publique pour jouer un son de bouton
    QPushButton *startButton;
    QPushButton* getStartButton() const;  // Getter pour startButton


private slots:
    void startClicked();

signals:
    void startclickedSig();

private:
    QLabel *welcomeText;
    QLabel *backgroundLabel;
    QMediaPlayer *mediaPlayer;  // Pour lire le son
    QAudioOutput *audioOutput; // Pour gérer la sortie audio

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // STARTSCREEN_H
