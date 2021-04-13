/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton_6;
    QPushButton *pushButton_8;
    QPushButton *pushButton_4;
    QPushButton *pushButton_11;
    QPushButton *pushButton_9;
    QPushButton *pushButton_5;
    QPushButton *Backspace;
    QPushButton *pushButton_10;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_7;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *OK;
    QPushButton *Close;
    QLabel *label;
    QButtonGroup *Key_pad;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(439, 346);
        verticalLayout_3 = new QVBoxLayout(Dialog);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_6 = new QPushButton(Dialog);
        Key_pad = new QButtonGroup(Dialog);
        Key_pad->setObjectName(QString::fromUtf8("Key_pad"));
        Key_pad->addButton(pushButton_6);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_6, 2, 0, 1, 1);

        pushButton_8 = new QPushButton(Dialog);
        Key_pad->addButton(pushButton_8);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        sizePolicy.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_8, 0, 2, 1, 1);

        pushButton_4 = new QPushButton(Dialog);
        Key_pad->addButton(pushButton_4);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_4, 1, 0, 1, 1);

        pushButton_11 = new QPushButton(Dialog);
        Key_pad->addButton(pushButton_11);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        sizePolicy.setHeightForWidth(pushButton_11->sizePolicy().hasHeightForWidth());
        pushButton_11->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_11, 3, 1, 1, 1);

        pushButton_9 = new QPushButton(Dialog);
        Key_pad->addButton(pushButton_9);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        sizePolicy.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_9, 1, 2, 1, 1);

        pushButton_5 = new QPushButton(Dialog);
        Key_pad->addButton(pushButton_5);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_5, 1, 1, 1, 1);

        Backspace = new QPushButton(Dialog);
        Backspace->setObjectName(QString::fromUtf8("Backspace"));
        sizePolicy.setHeightForWidth(Backspace->sizePolicy().hasHeightForWidth());
        Backspace->setSizePolicy(sizePolicy);

        gridLayout->addWidget(Backspace, 3, 2, 1, 1);

        pushButton_10 = new QPushButton(Dialog);
        Key_pad->addButton(pushButton_10);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        sizePolicy.setHeightForWidth(pushButton_10->sizePolicy().hasHeightForWidth());
        pushButton_10->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_10, 2, 2, 1, 1);

        pushButton_2 = new QPushButton(Dialog);
        Key_pad->addButton(pushButton_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_2, 0, 0, 1, 1);

        pushButton_3 = new QPushButton(Dialog);
        Key_pad->addButton(pushButton_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_3, 0, 1, 1, 1);

        pushButton_7 = new QPushButton(Dialog);
        Key_pad->addButton(pushButton_7);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        sizePolicy.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_7, 2, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        OK = new QPushButton(Dialog);
        OK->setObjectName(QString::fromUtf8("OK"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(OK->sizePolicy().hasHeightForWidth());
        OK->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(OK);

        Close = new QPushButton(Dialog);
        Close->setObjectName(QString::fromUtf8("Close"));
        sizePolicy1.setHeightForWidth(Close->sizePolicy().hasHeightForWidth());
        Close->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(Close);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(label);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Dialog", "7", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Dialog", "3", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Dialog", "4", nullptr));
        pushButton_11->setText(QCoreApplication::translate("Dialog", "0", nullptr));
        pushButton_9->setText(QCoreApplication::translate("Dialog", "6", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Dialog", "5", nullptr));
        Backspace->setText(QCoreApplication::translate("Dialog", "Backspace", nullptr));
        pushButton_10->setText(QCoreApplication::translate("Dialog", "9", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Dialog", "1", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Dialog", "2", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Dialog", "8", nullptr));
        OK->setText(QCoreApplication::translate("Dialog", "OK", nullptr));
        Close->setText(QCoreApplication::translate("Dialog", "Close", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "10", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
