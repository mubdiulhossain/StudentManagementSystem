#ifndef POSTGRESDATABASE_H
#define POSTGRESDATABASE_H
#include <QSqlDatabase>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <string>

#include "User.h"
#include "Admin.h"
#include "UnderGraduate.h"
#include "PostGraduate.h"
#include "Diploma.h"
class PostgresDatabase
{
private:
    QSqlDatabase db;
    User *currentLoggedInUser; //declaring current logged in user pointer
public:
    PostgresDatabase(QString hostName, QString databaseName, QString dbUserName, QString dbpassword, int port);
    User *getUser(QString, QString);
    bool databaseOpen();
    void databaseClose();

};

#endif // POSTGRESDATABASE_H
