/********************************************************************************
** Form generated from reading UI file 'Parametres.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETRES_H
#define UI_PARAMETRES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Parametres
{
public:
    QHBoxLayout *horizontalLayout_3;
    QTabWidget *tabWidget;
    QWidget *Vendeurs;
    QGridLayout *gridLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QSpinBox *numVendorsSpin;
    QScrollArea *vendorsScrollArea;
    QWidget *vendorsContainer;
    QPushButton *submitButton;
    QWidget *Protocol;
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *nombre_tours;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QSpinBox *lim_tour;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_5;
    QSpinBox *pen;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_6;
    QSpinBox *nbr_sim;
    QSpacerItem *verticalSpacer;
    QPushButton *protocolSubmitButton;

    void setupUi(QWidget *Parametres)
    {
        if (Parametres->objectName().isEmpty())
            Parametres->setObjectName("Parametres");
        Parametres->resize(425, 283);
        horizontalLayout_3 = new QHBoxLayout(Parametres);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        tabWidget = new QTabWidget(Parametres);
        tabWidget->setObjectName("tabWidget");
        Vendeurs = new QWidget();
        Vendeurs->setObjectName("Vendeurs");
        gridLayout = new QGridLayout(Vendeurs);
        gridLayout->setObjectName("gridLayout");
        widget_2 = new QWidget(Vendeurs);
        widget_2->setObjectName("widget_2");
        verticalLayout_5 = new QVBoxLayout(widget_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(widget_2);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        numVendorsSpin = new QSpinBox(widget_2);
        numVendorsSpin->setObjectName("numVendorsSpin");

        horizontalLayout->addWidget(numVendorsSpin);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        vendorsScrollArea = new QScrollArea(widget_2);
        vendorsScrollArea->setObjectName("vendorsScrollArea");
        vendorsScrollArea->setWidgetResizable(true);
        vendorsContainer = new QWidget();
        vendorsContainer->setObjectName("vendorsContainer");
        vendorsContainer->setGeometry(QRect(0, 0, 363, 127));
        vendorsScrollArea->setWidget(vendorsContainer);

        verticalLayout_2->addWidget(vendorsScrollArea);


        verticalLayout_5->addLayout(verticalLayout_2);

        submitButton = new QPushButton(widget_2);
        submitButton->setObjectName("submitButton");

        verticalLayout_5->addWidget(submitButton);


        gridLayout->addWidget(widget_2, 0, 0, 1, 1);

        tabWidget->addTab(Vendeurs, QString());
        Protocol = new QWidget();
        Protocol->setObjectName("Protocol");
        gridLayout_2 = new QGridLayout(Protocol);
        gridLayout_2->setObjectName("gridLayout_2");
        widget = new QWidget(Protocol);
        widget->setObjectName("widget");
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        nombre_tours = new QSpinBox(widget);
        nombre_tours->setObjectName("nombre_tours");

        horizontalLayout_2->addWidget(nombre_tours);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        lim_tour = new QSpinBox(widget);
        lim_tour->setObjectName("lim_tour");

        horizontalLayout_4->addWidget(lim_tour);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_6 = new QLabel(widget);
        label_6->setObjectName("label_6");

        horizontalLayout_5->addWidget(label_6);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        pen = new QSpinBox(widget);
        pen->setObjectName("pen");

        horizontalLayout_5->addWidget(pen);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");

        horizontalLayout_6->addWidget(label_4);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        nbr_sim = new QSpinBox(widget);
        nbr_sim->setObjectName("nbr_sim");

        horizontalLayout_6->addWidget(nbr_sim);


        verticalLayout_4->addLayout(horizontalLayout_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        protocolSubmitButton = new QPushButton(widget);
        protocolSubmitButton->setObjectName("protocolSubmitButton");

        verticalLayout_4->addWidget(protocolSubmitButton);


        gridLayout_2->addWidget(widget, 0, 0, 1, 1);

        tabWidget->addTab(Protocol, QString());

        horizontalLayout_3->addWidget(tabWidget);


        retranslateUi(Parametres);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Parametres);
    } // setupUi

    void retranslateUi(QWidget *Parametres)
    {
        Parametres->setWindowTitle(QCoreApplication::translate("Parametres", "Form", nullptr));
        label->setText(QCoreApplication::translate("Parametres", "Nombre Vendeurs", nullptr));
        submitButton->setText(QCoreApplication::translate("Parametres", "Valider", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Vendeurs), QCoreApplication::translate("Parametres", "Vendeurs", nullptr));
        label_2->setText(QCoreApplication::translate("Parametres", "Nombre Tours", nullptr));
        label_3->setText(QCoreApplication::translate("Parametres", "Tour limite acheter", nullptr));
        label_6->setText(QCoreApplication::translate("Parametres", "Penalit\303\251 (en %)", nullptr));
        label_4->setText(QCoreApplication::translate("Parametres", "Nbr negociations en meme temps", nullptr));
        protocolSubmitButton->setText(QCoreApplication::translate("Parametres", "Valider", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Protocol), QCoreApplication::translate("Parametres", "Protocol", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Parametres: public Ui_Parametres {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETRES_H
