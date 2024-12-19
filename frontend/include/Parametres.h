#ifndef PARAMETRES_H
#define PARAMETRES_H

#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QList>
#include <vector>
#include <QPushButton>


using namespace std;

namespace Ui {
class Parametres;
}

class Parametres : public QWidget
{
    Q_OBJECT

public:
    explicit Parametres(QWidget *parent = nullptr, int* nbr_tours = nullptr, std::vector<std::vector<int>>* vendeurs_param = nullptr);
    ~Parametres();


private slots:
    void onNumVendorsChanged(int count);
    void onSubmit();
    void onRoundsButtonClicked();  // Add this declaration

signals:
    void submitVendorClicked(vector<vector<int>>& vendeurs_param_ptr);
    void submitProtocolClicked(int* nbr_rounds, int* tours_limites, int* penalite, int* neg_simult,bool* pt_differ);

private:
    Ui::Parametres *ui;
    QVBoxLayout *vendorsLayout;
    QList<QComboBox*> vendorStrategies;
    QList<QLineEdit*> vendorProducts;
    vector<int> vendorKarma;

    // Pointer to external data
    int* nbr_tours_ptr;
    int* tours_limites;
    int* penalite;
    int* neg_simult;
    bool pt_differ;
    std::vector<std::vector<int>>* vendeurs_param_ptr;
};

#endif // PARAMETRES_H
