#include "materiel.h"
#include "ui_materiel.h"
#include "connectbdd.h"

#include <iostream>
#include <QSqlQuery>
#include <QString>
#include <QMessageBox>

using namespace std;

materiel::materiel(int matricule, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::materiel)
{
    ui->setupUi(this);
    this->setWindowTitle("MATERIEL");
    this->matriculeMatGlobal = matricule; // Prise du valeur de "matricule" dans la fenêtre de début
}

materiel::~materiel()
{
    delete ui;
}

void materiel::on_VALIDER_clicked()
{
    connectbdd conxbdd;
    conxbdd.mivohabdd();
    QString marque = ui->marqueEdit->text();
    QString designation = ui->designationEdit->currentText();
    QString etat = ui->etatEdit->currentText();
    QString dernierInt = ui->dernierEdit->text();


    if (marque.isEmpty() || designation.isEmpty() || etat.isEmpty()) {
        QMessageBox::warning(this, "attention", "Il semble qu'il y a des champ vide");
    } else {
        QSqlQuery matquery;
        lastIdU = matquery.lastInsertId();
        matquery.prepare("INSERT INTO MaterielsInfo(Designations, Marques, Etats, DernierIntervention) VALUES(:type, :marque, :etat, :dernierint);");
        matquery.bindValue(":type", designation);
        matquery.bindValue(":marque", marque);
        matquery.bindValue(":etat", etat);
        matquery.bindValue(":dernierint", dernierInt);

        if (!matquery.exec()) {
                    qDebug() << "Erreur lors de l'insertion :" << matquery.lastError();
                } else {
                    lastIdMateriel = matquery.lastInsertId(); // prend le dernier IdMatériel
                    qDebug() << lastIdMateriel;
                    qDebug() << "Insertion réussie dans MATÉRIELINFO OK";
                    QSqlQuery query;
                    query.prepare("INSERT INTO Gestion(MatriculeUtilisateur,IdMatInfo) VALUES(:IdU, :IdMat);");
                    qDebug() << matriculeMatGlobal;
                    query.bindValue(":IdU", matriculeMatGlobal);
                    query.bindValue(":IdMat", lastIdMateriel);
                    if (!query.exec()) {
                        qDebug() << "Erreur :" << "tsy mandeh le insert materiel";
                        qDebug() << "Erreur :" << query.lastError();

                    } else {
                        qDebug() << "Insertion dans GESTION parfait ";
                        cout << "Insertion dans Gestion parfait";
                        conxbdd.mihidybdd();
                        this->close();
                    }
                }
    }
}


void materiel::on_RETOUR_clicked()
{
    cout << "retour liste materiels..." << endl;
    this->close();
}



