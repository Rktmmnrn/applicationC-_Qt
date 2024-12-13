#include "modifmat.h"
#include "ui_modifmat.h"
#include "connectbdd.h"
#include "listmateriels.h"

#include <QMessageBox>
#include <iostream>

using namespace std;

modifMat::modifMat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifMat)
{
    ui->setupUi(this);
    ui->titreModif->setStyleSheet(style.labelModif);
    this->setWindowTitle("Modification");
}

modifMat::~modifMat()
{
    delete ui;
}

void modifMat::getData(QString marque, QString type, QString etat, QString dernierint)
{
    ui->typeModif->setCurrentText(type);
    ui->marqueModif->setText(marque);
    ui->etatModif->setCurrentText(etat);
    ui->intModif->setText(dernierint);
}

QString modifMat::getNb(QString Nb)
{
    return Nb;
}

void modifMat::on_annulerModif_clicked()
{
    this->close();
}


void modifMat::on_modif_clicked()
{
    connectbdd bdd;
    bdd.mivohabdd();
    Marque = ui->marqueModif->text();
    Type = ui->typeModif->currentText();
    Etat = ui->etatModif->currentText();
    DernInt = ui->intModif->text();

    if (Marque.isEmpty() || Type.isEmpty() || Etat.isEmpty() || DernInt.isEmpty()) {
        QMessageBox::warning(this, "attention", "Il semble qu'il y a des champ vide");
    } else {
        QSqlQuery matquery;
        matquery.prepare("UPDATE MaterielsInfo SET Designations=:type,Marques=:marque,Etats=:etat,DernierIntervention=:dernierint WHERE NumMatInfo=:NumMat;");
        matquery.bindValue(":marque", Marque);
        matquery.bindValue(":type", Type);
        matquery.bindValue(":etat", Etat);
        matquery.bindValue(":dernierint", DernInt);
        matquery.bindValue(":NumMat", Nbr); // "Nbr" est une variable prise dans listmateriel

        if (!matquery.exec()) {
                    qDebug() << "Erreur lors du MAJ :" << matquery.lastError();
                } else {
                    qDebug() << "Mise à jour parfait sur la ligne: " << Nbr;
                }

        bdd.mihidybdd();
        this->close();
        QMessageBox::warning(this, "Info", "Modification fait sur le materiel Numéro: "+Nbr);
    }
}
