#ifndef STORE_H
#define STORE_H

#include <QWidget>
#include <QScrollArea>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <vector>
#include <tuple>
#include <QLabel>
#include "back_end_main.h"

namespace Ui {
class Store;
}

class Store : public QWidget
{
    Q_OBJECT

public:
    explicit Store(QWidget *parent = nullptr);
    void setProducts(const std::vector<Produits_dispos>& products);
    QPushButton* getViewCartButton() const;  // Assurez-vous que cette méthode est déclarée    QList<QPushButton*> getSelectButtons() const;
    QVector<QPushButton*> getSelectButtons() const; // Ajoutez cette méthode si elle manque

    void filterProducts();
    void addToCart(const Produits_dispos &product);  // Adds selected product to the cart
    void viewCart();


signals:
    void productSelected(const Produits_dispos &product, double maxBid);
    void cartValidated(const std::vector<std::tuple<Voiture, int>>& cartDetails);

private:
    Ui::Store *ui;
    QLineEdit *filterEdit;
    QScrollArea *scrollArea;
    QWidget *productsContainer;
    QVBoxLayout *productsLayout;
    std::vector<Produits_dispos> originalProducts;   // All available products
    std::vector<std::tuple<Voiture,int>> cart;  // Updated cart to store tuples of product, price, strategy
    void displayProducts(const std::vector<Produits_dispos>& products);  // Displays products based on filter or full list
    void ajouterProduit();
    void showProtocol();
    QVector<QPushButton*> selectButtons; // Conteneur pour stocker les boutons

};

#endif // STORE_H
