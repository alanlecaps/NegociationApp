#ifndef VOITURE_H
#define VOITURE_H

#include<string>
#include<iostream>
#include "Produit.h"
using namespace std;

class Voiture : public Produit{
private:
    string brand;
    string model;
    int year;
    string boite_de_vitesse;
    int kilometres;
    string essence;
    float mpg;
    float taille_engin;

public:

    Voiture(int id, string description, float prix, string categorie, string image,
            string br, string mod, int year, string bdv, int km, string essen, float mpg, float te)
        : Produit(id, description, prix, categorie, image),  
          brand(br), model(mod), year(year), boite_de_vitesse(bdv),
          kilometres(km), essence(essen), mpg(mpg), taille_engin(te) {
    }

    Voiture()
        : Produit(0, "", 0.0f, "", ""),
        brand(""),
        model(""),
        year(0),
        boite_de_vitesse(""),
        kilometres(0),
        essence(""),
        mpg(0.0f),
        taille_engin(0.0f) {
    }


    ~Voiture() override;

    // Getter-Methoden
    string getBrand() const;
    string getModel() const;
    int getYear() const; 
    string getBoiteDeVitesse() const;
    int getKilometres() const ;
    string getEssence() const; 
    float getMPG() const;
    float getTailleEngin() const;

    // Setter-Methoden
    void setBrand(const string& b);
    void setModel(const string& m) ;
    void setYear(int y); 
    void setBoiteDeVitesse(const string& bv);
    void setKilometres(int km);
    void setEssence(const string& e);
    void setMPG(float mpg_val) ;
    void setTailleEngin(float taille) ;

    void afficherTout() const override;
    

};


#endif
