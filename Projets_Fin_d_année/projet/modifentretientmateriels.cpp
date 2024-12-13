#include "modifentretientmateriels.h"
#include "ui_modifentretientmateriels.h"
#include "connectbdd.h"

#include <QMessageBox>
#include <iostream>

using namespace std;

modifentretientmateriels::modifentretientmateriels(int numModifInt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifentretientmateriels)
{
    ui->setupUi(this);
    this->numModif = numModifInt;
}

modifentretientmateriels::~modifentretientmateriels()
{
    delete ui;
}

void modifentretientmateriels::on_annulerEntretientModif_clicked()
{
    QMessageBox message;
    message.setText("ANNULER LES CHANGEMENTS ?");
    QPushButton *Y = message.addButton(QMessageBox::Yes);
    QPushButton *N = message.addButton(QMessageBox::Cancel);
    message.exec();
    if (message.clickedButton()==Y) {
        this->close();
    } else if (message.clickedButton()==N) {
        cout << "C bon de rester non.!!" << endl;
    }
}


void modifentretientmateriels::on_envoyeEntretientModif_clicked()
{
    connectbdd conbdd;
    conbdd.mivohabdd();
    typeM = ui->typeEntretientModif->text();
    marqueM = ui->marqueEntretientModif->text();
    etatM = ui->etatEntretientModif->currentText();
    blemM = ui->blemEntretientModif->toPlainText();
    numM = ui->numMatEntretientModif->text().toInt();
    debutI = ui->debutEntretientModif->text();
    nbHI = ui->dureeEntretientModif->text();
    finI = ui->FinEntretientModif->text();
    numII = ui->phoneEntretientModif->currentText();
    nomII = ui->NomIntEntretientModif->currentText();

    if (typeM.isEmpty() || marqueM.isEmpty() || etatM.isEmpty()) {
        QMessageBox::warning(this, "Info", "IL SEMBLE Y AVOIR DES ÉLÉMENTS VIDES");
    } else {
        QMessageBox message;
        message.setText("APPLIQUER LES MODIFICATIONS ?");
        QPushButton *Y = message.addButton(QMessageBox::Yes);
        QPushButton *N = message.addButton(QMessageBox::Cancel);
        message.exec();
        if (message.clickedButton()==Y) {
            QSqlQuery querymodifEnt;
            querymodifEnt.prepare("UPDATE Entretients SET NumMateriel=:numM,ProblemMateriel=:blemMat WHERE NumEntretient=:numEnt;");
            querymodifEnt.bindValue(":blemMat", blemM);
            querymodifEnt.bindValue(":numM", numM);
            querymodifEnt.bindValue(":numEnt", numEntretients);

            if (!querymodifEnt.exec()) {
                qDebug() << "Erreur MAJ: " << querymodifEnt.lastError();
            } else {
                qDebug() << "MAJ parfait sur la ligne: " << numEntretients;
                querymodifEnt.prepare("UPDATE Interventions SET DateDebut=:debut,Nb_heure=:heure,DateFin=:fin WHERE Numero=:Numero;");
                querymodifEnt.bindValue(":debut", debutI);
                querymodifEnt.bindValue(":heure", nbHI);
                querymodifEnt.bindValue(":fin", finI);
                querymodifEnt.bindValue(":Numero", numModif);
                this->close();
                conbdd.mihidybdd();
            }

        } else if (message.clickedButton()==N) {
            cout << "Changement pas encore fait" << endl;
        }
    }
}

void modifentretientmateriels::getdonnerEntretient(QString designation, QString marque, QString etat, QString problem, QString numMat, QDate &debut, int duree, QDateTime &fin, QString &numInt, QString &nomInt)
{
    ui->typeEntretientModif->setText(designation);
    ui->marqueEntretientModif->setText(marque);
    ui->etatEntretientModif->addItem(etat);
    ui->etatEntretientModif->setCurrentText(etat);
    ui->blemEntretientModif->setText(problem);
    ui->numMatEntretientModif->setText(numMat);
    ui->debutEntretientModif->setDate(debut);
    ui->dureeEntretientModif->setValue(duree);
    ui->FinEntretientModif->setDateTime(fin);
    ui->phoneEntretientModif->addItem(numInt);
    ui->phoneEntretientModif->setCurrentText(numInt);
    ui->NomIntEntretientModif->addItem(nomInt);
    ui->NomIntEntretientModif->setCurrentText(nomInt);
}

QString modifentretientmateriels::getNumEntretient(QString numEntretient)
{
    return numEntretient;
}

void modifentretientmateriels::on_dureeEntretientModif_valueChanged(int arg1)
{
    QDate debutEnt = ui->debutEntretientModif->date();
//    QDateTime finEnt = ui->FinEntretientModif->dateTime();
    QDateTime debutDT(debutEnt, QTime::currentTime());
    QDateTime finDT = debutDT.addSecs(arg1 *3600);
    ui->FinEntretientModif->setDateTime(finDT);
}

