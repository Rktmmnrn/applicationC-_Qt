#ifndef CONNECTBDD_H
#define CONNECTBDD_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QtSql>
#include <QSql>
#include <QSqlError>

class connectbdd
{
public:
    QSqlDatabase bdd;

    void mihidybdd() {
        bdd.close();
        qDebug() << "Mihidy donnee zao...";
        bdd.removeDatabase(QSqlDatabase::defaultConnection);
    };

    bool mivohabdd() {
//        bdd = QSqlDatabase:: addDatabase("QSQLITE", "maConnection");
        bdd = QSqlDatabase:: addDatabase("QSQLITE");
        bdd.setDatabaseName("/home/fenohery/Documents/Projets_ENI/Projets_Fin_d_année/BaseDeDonnee/ProjFinAnn");
        QStringList drivers = QSqlDatabase::drivers();

        if (!bdd.open()) {
            qDebug() << "TSY MIVOHA BDD";
            return false;
        } else {
            qDebug() << "drivers dispo" << drivers;
            return true;
        }
    }


};

#endif // CONNECTBDD_H
