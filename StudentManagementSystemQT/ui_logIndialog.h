/********************************************************************************
** Form generated from reading UI file 'logIndialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_logInDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *header;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *userId;
    QLabel *password;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *text_box_ID;
    QLineEdit *text_box_Password;
    QSpacerItem *horizontalSpacer;
    QLabel *showerror;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *loginButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *logInDialog)
    {
        if (logInDialog->objectName().isEmpty())
            logInDialog->setObjectName(QString::fromUtf8("logInDialog"));
        logInDialog->resize(324, 248);
        verticalLayout = new QVBoxLayout(logInDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        header = new QLabel(logInDialog);
        header->setObjectName(QString::fromUtf8("header"));
        QFont font;
        font.setPointSize(11);
        header->setFont(font);
        header->setFrameShape(QFrame::NoFrame);

        verticalLayout->addWidget(header);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        groupBox = new QGroupBox(logInDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        userId = new QLabel(groupBox);
        userId->setObjectName(QString::fromUtf8("userId"));

        verticalLayout_3->addWidget(userId);

        password = new QLabel(groupBox);
        password->setObjectName(QString::fromUtf8("password"));

        verticalLayout_3->addWidget(password);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        text_box_ID = new QLineEdit(groupBox);
        text_box_ID->setObjectName(QString::fromUtf8("text_box_ID"));

        verticalLayout_2->addWidget(text_box_ID);

        text_box_Password = new QLineEdit(groupBox);
        text_box_Password->setObjectName(QString::fromUtf8("text_box_Password"));
        text_box_Password->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(text_box_Password);


        horizontalLayout->addLayout(verticalLayout_2);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addWidget(groupBox);

        showerror = new QLabel(logInDialog);
        showerror->setObjectName(QString::fromUtf8("showerror"));

        verticalLayout->addWidget(showerror);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        loginButton = new QPushButton(logInDialog);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));

        horizontalLayout_3->addWidget(loginButton);

        pushButton_2 = new QPushButton(logInDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(logInDialog);

        QMetaObject::connectSlotsByName(logInDialog);
    } // setupUi

    void retranslateUi(QDialog *logInDialog)
    {
        logInDialog->setWindowTitle(QCoreApplication::translate("logInDialog", "Log In", nullptr));
        header->setText(QCoreApplication::translate("logInDialog", "Welcome to the Management System", nullptr));
        groupBox->setTitle(QCoreApplication::translate("logInDialog", "Log In", nullptr));
        userId->setText(QCoreApplication::translate("logInDialog", "ID: ", nullptr));
        password->setText(QCoreApplication::translate("logInDialog", "Password:", nullptr));
        showerror->setText(QString());
        loginButton->setText(QCoreApplication::translate("logInDialog", "Log In", nullptr));
        pushButton_2->setText(QCoreApplication::translate("logInDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class logInDialog: public Ui_logInDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
