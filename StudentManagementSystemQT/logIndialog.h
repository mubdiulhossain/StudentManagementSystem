#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class logInDialog;
}

class logInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit logInDialog(QWidget *parent = nullptr);

    ~logInDialog();

private slots:

    void on_loginButton_clicked();

public slots:
    void on_pushButton_2_clicked();
    void receiveData(bool);
signals:
    void logInData(QString, QString);

private:
    Ui::logInDialog *ui;

    bool istrue;
};

#endif // LOGINDIALOG_H
