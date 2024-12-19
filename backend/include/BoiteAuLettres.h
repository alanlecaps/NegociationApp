#ifndef _BAL_H
#define _BAL_H

#include <vector>
#include <iostream>
#include <mutex>
#include "Message.h"
#include "Protocol.h"
#include <memory>

using namespace std ;

class BoiteAuLettres
{
    private:
        vector<shared_ptr<Message>> boiteAuLettres; //Vecteur de Messages
        shared_ptr<Protocol> protocol;
        mutable std::mutex mtx;

    public:
        BoiteAuLettres(shared_ptr<Protocol> pro);
        ~BoiteAuLettres();


        //Messages controlleur
        int laisserMessage(shared_ptr<Message> m); //Methode que vendeur et acheteur utilisent pour laisser un message
        shared_ptr<Message> dernierMessage(); //retourne le dernier message

        void afficherDiscussion();  //Affiche toutes les messages au terminal

        //Getters
        bool estVide();
        int getSize();
        shared_ptr<Message> getMessage(int i);
        shared_ptr<Protocol> getProtocol() const;
        std::vector<std::shared_ptr<Message>> getBoiteAuLettres() const;

        //Setters
        void setProtocol(shared_ptr<Protocol> prot);
};

#endif