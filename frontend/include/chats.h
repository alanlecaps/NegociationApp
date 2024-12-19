#ifndef CHATS_H
#define CHATS_H

#include <QWidget>
#include <QTabWidget>
#include <vector>
#include <memory>
#include "BoiteAuLettres.h"
#include "Acheteur.h"
#include "Vendeur.h"
#include <string>

class QVBoxLayout;

class Chats : public QWidget
{
    Q_OBJECT

public:
    Chats(int aheteur_id, int vendeur_id, const std::string &type, const std::string &offre, const std::string &message, std::shared_ptr<Chats> next, QWidget *parent = nullptr);
    Chats(int acheteur_id, int vendeur_id, const std::string &type, const std::string &offre, const std::string &message, QWidget *parent = nullptr);
    explicit Chats(QWidget *parent = nullptr);
    void setBoites(const std::vector<Acheteur> &boites, const std::vector<Vendeur> &vendeur);
private:
    void createChatTabs();  // Creates the tabs for each BoiteAuLettres
    void showDetails(std::shared_ptr<Message> message);
    void showProtocol(std::shared_ptr<Protocol> prot);
    void showAcheteurDetails(shared_ptr<Acheteur> a);
    void showVendeurDetails(shared_ptr<Vendeur> v);
    string StrattoInt(int i);


    QVBoxLayout *mainLayout;
    QTabWidget *tabWidget;  // Add QTabWidget for tabs
    std::vector<vector<std::shared_ptr<BoiteAuLettres>>> boites;
    std::vector<Acheteur> achet;
    std::vector<Vendeur> vend;


};

#endif // CHATS_H
