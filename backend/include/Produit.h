#ifndef PRODUIT_H
#define PRODUIT_H
#include<string>
#include<iostream>

using namespace std;

class Produit{

private:
    int id;
    string description;
    float prix;
    float prixMin;
    float prixMax;
    string categorie;
    string image;

public:
    virtual ~Produit();
    Produit(int idx, string descriptionx, float prixx, string categoriex, string imagex)
    :id(idx),description(descriptionx),prix(prixx),categorie(categoriex),image(imagex){} // pour le constructeur

    //pour les getters


    string getDescription() const;
    float getPrixMin() const;
    float getPrixMax() const;
    string getCategorie() const;
    string getImage() const;
    int getId() const;
    float getPrix() const;
    //pour les setters

    void setDescription(const string & description);
    void setPrixMin(const float min_prix);
    void setPrixMax(const float max_prix);
    void setPrix(const float prix);
    void setCategorie(const string& categorie);
    void setImage(const string& image);
    void setId(int idx);

    // les fonctions/methodes

    virtual void afficherTout() const;
   
};
#endif

