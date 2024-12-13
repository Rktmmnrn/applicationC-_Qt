#include "entretientmateriels.h"
#include "ui_entretientmateriels.h"
#include "connectbdd.h"

#include <QMessageBox>
#include <QSqlQuery>

EntretientMateriels::EntretientMateriels(int matriculeU, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntretientMateriels)
{
    ui->setupUi(this);
    this->setWindowTitle("ENTRETIENT");
    this->matriculeUtilisateur = matriculeU;

    // changement de la date et l'heure en fonction du temps
    ui->debutEntretient->setDate(QDate::currentDate());
    ui->FinEntretient->setDateTime(QDateTime::currentDateTime());
    ui->dureeEntretient->setRange(0,7200);
//    ui->dureeEntretient->setSuffix(" heure");

    ui->typeEntretient->setReadOnly(true);
    ui->marqueEntretient->setReadOnly(true);
    ui->etatEntretient->setReadOnly(true);
    ui->numMatEntretient->setReadOnly(true);
}

EntretientMateriels::~EntretientMateriels()
{
    delete ui;
}

void EntretientMateriels::on_annulerEntretient_clicked()
{
    this->close();
}

void EntretientMateriels::getdonner(QString typeEnt, QString marqueEnt, QString etatEnt, QString NumMatEnt)
{
    ui->typeEntretient->setText(typeEnt);
    ui->marqueEntretient->setText(marqueEnt);
    ui->etatEntretient->setText(etatEnt);
    ui->numMatEntretient->setText(NumMatEnt);
}

void EntretientMateriels::getinfoEntretient(QString nom, QString phone, QString tauxhorraire)
{
    ui->NomIntEntretient->addItem(nom);
    ui->phoneEntretient->addItem(phone);
    ui->tauxHEntretient->addItem(tauxhorraire);
}

void EntretientMateriels::on_dureeEntretient_valueChanged(int heure)
{
    QDate debutEnt = ui->debutEntretient->date();
    QDateTime debutDT(debutEnt, QTime::currentTime());
    QDateTime finDT = debutDT.addSecs(heure *3600);
    ui->FinEntretient->setDateTime(finDT);
}

void EntretientMateriels::on_debutEntretient_userDateChanged(const QDate &date)
{
    int heure = ui->dureeEntretient->value();
    QDateTime debutdatetime(date, QTime::currentTime());
    QDateTime findatetime = debutdatetime.addSecs(heure *3600);
    ui->FinEntretient->setDateTime(findatetime);
}

int EntretientMateriels::getIdIntervenant(int numInt)
{
    numIntervenant = numInt;
    return numIntervenant;
}


void EntretientMateriels::on_envoyeEntretient_clicked()
{
    connectbdd connectionbdd;
    connectionbdd.mivohabdd();

    typeMatEnt = ui->typeEntretient->text();
    marqueMatEnt = ui->marqueEntretient->text();
    etatMatEnt = ui->etatEntretient->text();
    blemMatEnt = ui->blemEntretient->toPlainText();
    numMatEnt = ui->numMatEntretient->text().toInt();
    datedebEnt = ui->debutEntretient->text();
    nbheureEnt = ui->dureeEntretient->text();
    datefinEnt = ui->FinEntretient->text();
    nomIntEnt = ui->NomIntEntretient->currentText();
    phoneIntEnt = ui->phoneEntretient->currentText();
    tauxhEnt = ui->tauxHEntretient->currentText();

    if (typeMatEnt.isEmpty() || marqueMatEnt.isEmpty() || etatMatEnt.isEmpty()) {
        QMessageBox::warning(this, "avertissement", "IL SEMBLE Y AVOIR DES ÉLÉMENTS VIDE");
    } else if(nbheureEnt=="0 heure") {
        QMessageBox::warning(this, "", "0 heure invalide !");
        } else {
        QSqlQuery envoyeEntretient;

        envoyeEntretient.prepare("INSERT INTO Interventions(DateDebut, Nb_heure, DateFin, IdUtilisateur) VALUES(:debut, :heure, :fin, :idUtilisateur);");
        envoyeEntretient.bindValue(":debut", datedebEnt);
        envoyeEntretient.bindValue(":heure", nbheureEnt);
        envoyeEntretient.bindValue(":fin", datefinEnt);
        envoyeEntretient.bindValue(":idUtilisateur", matriculeUtilisateur); // Insértion IdUtilisateur

        if (!envoyeEntretient.exec()) {
            qDebug() << "ERREUR INSERTION DANS 'Intervention' :" << envoyeEntretient.lastError();
        } else {
            NumIntervention = envoyeEntretient.lastInsertId().toInt(); // Prise NumIntervention
            envoyeEntretient.prepare("INSERT INTO Entretients(NumMateriel, ProblemMateriel, NumeroIntervention, IdIntervenant) VALUES(:numMat, :problemMat, :numIntervention, :idIntervenant);");
            envoyeEntretient.bindValue(":numMat", numMatEnt);
            envoyeEntretient.bindValue(":problemMat", blemMatEnt);
            envoyeEntretient.bindValue(":numIntervention", NumIntervention);
            envoyeEntretient.bindValue(":idIntervenant", numIntervenant); // Insértion IdIntervenant qui est NumIntervenant
            numEntretient = envoyeEntretient.lastInsertId().toInt();

            if (envoyeEntretient.exec()) {
                this->close();
                qDebug() << "Donnée insérer parfaitements...";
                QMessageBox::information(this, "Info", "ENVOYER");
                connectionbdd.mihidybdd();
            } else {
                qDebug() << "Erreur lors de l'insertion: " << envoyeEntretient.lastError().text();
            }
        }
    }
}

int EntretientMateriels::setIntervention(int Inter)
{
    Inter = NumIntervention;
    return Inter;
}
