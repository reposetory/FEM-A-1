/********************************************************************************
** Form generated from reading UI file 'heat_equation.ui'
**
** Created: Sat Dec 10 15:06:45 2016
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HEAT_EQUATION_H
#define UI_HEAT_EQUATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_heat_equation
{
public:
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *time_step;
    QLabel *label_5;
    QLineEdit *space_step;
    QLabel *label_6;
    QLineEdit *total_time;
    QPushButton *goButton;
    QLineEdit *output_file_name;
    QLabel *label_7;
    QComboBox *comboBox_dim;
    QComboBox *comboBox_num_scheme;
    QLabel *label_8;

    void setupUi(QWidget *heat_equation)
    {
        if (heat_equation->objectName().isEmpty())
            heat_equation->setObjectName(QString::fromUtf8("heat_equation"));
        heat_equation->resize(466, 505);
        label_2 = new QLabel(heat_equation);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 120, 91, 21));
        label_3 = new QLabel(heat_equation);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 160, 101, 21));
        label_4 = new QLabel(heat_equation);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(70, 200, 101, 21));
        time_step = new QLineEdit(heat_equation);
        time_step->setObjectName(QString::fromUtf8("time_step"));
        time_step->setGeometry(QRect(180, 200, 121, 21));
        label_5 = new QLabel(heat_equation);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(70, 240, 101, 21));
        space_step = new QLineEdit(heat_equation);
        space_step->setObjectName(QString::fromUtf8("space_step"));
        space_step->setGeometry(QRect(180, 240, 121, 21));
        label_6 = new QLabel(heat_equation);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(70, 280, 101, 21));
        total_time = new QLineEdit(heat_equation);
        total_time->setObjectName(QString::fromUtf8("total_time"));
        total_time->setGeometry(QRect(180, 280, 121, 21));
        goButton = new QPushButton(heat_equation);
        goButton->setObjectName(QString::fromUtf8("goButton"));
        goButton->setGeometry(QRect(200, 370, 81, 31));
        output_file_name = new QLineEdit(heat_equation);
        output_file_name->setObjectName(QString::fromUtf8("output_file_name"));
        output_file_name->setGeometry(QRect(180, 320, 121, 21));
        label_7 = new QLabel(heat_equation);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(70, 320, 101, 21));
        comboBox_dim = new QComboBox(heat_equation);
        comboBox_dim->setObjectName(QString::fromUtf8("comboBox_dim"));
        comboBox_dim->setGeometry(QRect(180, 120, 121, 21));
        comboBox_num_scheme = new QComboBox(heat_equation);
        comboBox_num_scheme->setObjectName(QString::fromUtf8("comboBox_num_scheme"));
        comboBox_num_scheme->setGeometry(QRect(180, 160, 121, 21));
        label_8 = new QLabel(heat_equation);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(180, 80, 171, 20));

        retranslateUi(heat_equation);
        QObject::connect(goButton, SIGNAL(clicked()), heat_equation, SLOT(close()));

        QMetaObject::connectSlotsByName(heat_equation);
    } // setupUi

    void retranslateUi(QWidget *heat_equation)
    {
        heat_equation->setWindowTitle(QApplication::translate("heat_equation", "heat_equation", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("heat_equation", "dimension: ", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("heat_equation", "numerical scheme", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("heat_equation", "time step: k", 0, QApplication::UnicodeUTF8));
        time_step->setText(QString());
        label_5->setText(QApplication::translate("heat_equation", "spatial step: h ", 0, QApplication::UnicodeUTF8));
        space_step->setText(QString());
        label_6->setText(QApplication::translate("heat_equation", "total time: T", 0, QApplication::UnicodeUTF8));
        total_time->setText(QString());
        goButton->setText(QApplication::translate("heat_equation", "SUBMIT", 0, QApplication::UnicodeUTF8));
        output_file_name->setText(QString());
        label_7->setText(QApplication::translate("heat_equation", "output file name:", 0, QApplication::UnicodeUTF8));
        comboBox_dim->clear();
        comboBox_dim->insertItems(0, QStringList()
         << QApplication::translate("heat_equation", "dimension:", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("heat_equation", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("heat_equation", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("heat_equation", "3", 0, QApplication::UnicodeUTF8)
        );
        comboBox_num_scheme->clear();
        comboBox_num_scheme->insertItems(0, QStringList()
         << QApplication::translate("heat_equation", "numerical method:", 0, QApplication::UnicodeUTF8)
        );
        label_8->setText(QApplication::translate("heat_equation", "INPUT PARAMETERS", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class heat_equation: public Ui_heat_equation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HEAT_EQUATION_H
