#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listmateriels.h"
//#include "avertissement.h"
#include "connectbdd.h"
#include <QPushButton>

#include <QDebug>
#include <QString>
#include <QSqlError>
#include <QtSql>
#include <QSql>
#include <iostream>
#include <QMessageBox>
#include <QSqlQuery>
#include <QCompleter>
#include <QStringList>
#include <QPixmap>
#include <QTimer>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("FENÊTRE DE CONNECTION");
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug() << "fenêtre fermer...";
}

void MainWindow:: on_ANNULER_clicked()
{
     this->close();
//    AVERTISSEMENT avert;
//    cout << "Avertissement_1..." << endl;
//    avert.exec();
    QMessageBox mssbx;
    mssbx.setText("SORTIR !");
    QPushButton *Y = mssbx.addButton(QMessageBox::Yes);
    QPushButton *N = mssbx.addButton(QMessageBox::Cancel);
    mssbx.exec();
    if (mssbx.clickedButton()==Y) {
        this->close();
    } else if (mssbx.clickedButton()==N){
        cout << "Bon choix" << endl;
        MainWindow *main = new MainWindow();
        main->show();
    }
}

void MainWindow:: on_VALIDER_clicked()
{
//    declaration variable champ de text
    NomUtil = ui->EditNom->text();
    PseudoUtil = ui->EditPseudo->text();
    FonctionUtil = ui->EditFonction->text();
    if (NomUtil.isEmpty()|| FonctionUtil.isEmpty() || PseudoUtil.isEmpty()) {
        QMessageBox::warning(this, "Avertissement", "VEUILLEZ REMPLIR SVP...");
        qDebug() << "fenoy oh...";
//        connbdd.mihidybdd();
    } else {
        connectbdd connbdd;
        connbdd.mivohabdd();
        QSqlQuery query;
        query.prepare("SELECT Matricule,PseudoUtilisateur FROM Utilisateurs WHERE PseudoUtilisateur=:pseudo");
        query.bindValue(":pseudo", PseudoUtil);
//        qDebug() << query.value(0);
//        qDebug() << query.value(1);
        if (query.exec() && query.first()) {
            int matriculeUtilisateur = query.value(0).toInt(); // matricule SÉLÉCTIONNER

            qDebug() << matriculeUtilisateur;
            if (query.value(1).toString() > 0) {
//                QMessageBox::critical(this, "", "PSEUDO EXISTANT VEUILLEZ SAISIR UN AUTRE NOM UTILISATEUR");

                QMessageBox mssbx;
                mssbx.setText("PSEUDO EXISTANT \n ÊTES VOUS : "+PseudoUtil+" ?");
                QPushButton *Y = mssbx.addButton(QMessageBox::Yes);
                QPushButton *N = mssbx.addButton(QMessageBox::No);
                mssbx.exec();
                if (mssbx.clickedButton()==Y) {
                    ListMateriels *listMat = new ListMateriels(matriculeUtilisateur);
                    this->close();
                    connbdd.mihidybdd();
                    listMat->exec();
                } else if (mssbx.clickedButton()==N) {
                    cout << "ENTRER UN NOUVEAU PSEUDO !" << endl;
                }
            } else {
                cout << "Y A RIEN ICI" << endl;
            }
        } else {
            query.prepare("INSERT INTO Utilisateurs(NomUtilisateur,PseudoUtilisateur,Fonction) VALUES (:Nom,:Pseudo,:Fonction);");
            query.bindValue(":Nom",NomUtil);
            query.bindValue(":Pseudo", PseudoUtil);
            query.bindValue(":Fonction",FonctionUtil);
            qDebug() << query.exec();
            MatriculeUtil = query.lastInsertId().toInt(); // définition du matricule pour le prendre après

            if (!query.exec()) {
                        qDebug() << "Erreur lors de l'insertion :" << query.lastError();
                    } else {
                        qDebug() << "Utilisateurs tafiditra...";
                        connbdd.mihidybdd();
                        ListMateriels *listMat = new ListMateriels(MatriculeUtil); // APPEL DU FENÊTRE "ListeMatériel" PARAMÉTRER
                        this->close();
                        listMat->setModal(true);
                        listMat->exec();
                    }
        }
    }
}


void MainWindow::on_EditNom_textChanged(const QString &textChanged)
{
    connectbdd bdd;
    bdd.mivohabdd();
    QStringList nomList;
    QSqlQuery query("SELECT NomUtilisateur,PseudoUtilisateur FROM Utilisateurs;");
//    QString pseudoU = query.value(1).toString();
    nomselectionner = textChanged;

    while (query.next()) {
           nomselectionner = query.value(0).toString();
//           pseudoselectionner = pseudoU;
           nomList << nomselectionner;
       }

    QCompleter *completer = new QCompleter(nomList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->EditNom->setCompleter(completer);
    bdd.mihidybdd();
}
