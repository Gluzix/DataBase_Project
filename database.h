#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlQuery>

static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

#endif // DATABASE_H
