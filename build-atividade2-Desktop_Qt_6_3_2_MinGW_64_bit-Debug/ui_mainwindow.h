/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QLineEdit *inputX;
    QLineEdit *inputY;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *inputEscala;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(270, 30, 69, 22));
        comboBox_2 = new QComboBox(centralwidget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(380, 30, 69, 22));
        inputX = new QLineEdit(centralwidget);
        inputX->setObjectName(QString::fromUtf8("inputX"));
        inputX->setGeometry(QRect(590, 50, 113, 22));
        inputY = new QLineEdit(centralwidget);
        inputY->setObjectName(QString::fromUtf8("inputY"));
        inputY->setGeometry(QRect(590, 110, 113, 22));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 0, 49, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(380, 0, 49, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(588, 0, 111, 20));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(640, 30, 49, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(640, 90, 49, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(630, 180, 111, 20));
        inputEscala = new QLineEdit(centralwidget);
        inputEscala->setObjectName(QString::fromUtf8("inputEscala"));
        inputEscala->setGeometry(QRect(590, 220, 113, 22));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(comboBox, SIGNAL(activated(int)), MainWindow, SLOT(SelectedDraw(int)));
        QObject::connect(comboBox_2, SIGNAL(activated(int)), MainWindow, SLOT(SelectedColor(int)));
        QObject::connect(inputX, &QLineEdit::textChanged, MainWindow, qOverload<>(&QMainWindow::update));
        QObject::connect(inputY, &QLineEdit::textChanged, MainWindow, qOverload<>(&QMainWindow::update));
        QObject::connect(inputEscala, &QLineEdit::textChanged, MainWindow, qOverload<>(&QMainWindow::update));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Limpar", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Circulo", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Retangulo", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Elipse", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Quadrado", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("MainWindow", "Arco", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("MainWindow", "Hexagono", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "Preto", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Azul", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "Amarelo", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "Vermelho", nullptr));
        comboBox_2->setItemText(4, QCoreApplication::translate("MainWindow", "Verde", nullptr));
        comboBox_2->setItemText(5, QCoreApplication::translate("MainWindow", "Ciano", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "Figura", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Cor", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Editar coordenadas", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Escala", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
