
#include "listmateriels.h"
#include "ui_listmateriels.h"
//#include "avertissement2.h"
#include "connectbdd.h"
#include "modifmat.h"
#include "entretientmateriels.h"
#include "detailsmateriels.h"
#include "error.h"
#include "modifentretientmateriels.h"
#include "mainwindow.h"
#include "facture.h"

#include <QPropertyAnimation>
#include <QMouseEvent>
#include <iostream>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QIcon>

using namespace std;

ListMateriels::ListMateriels(int Matricule, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListMateriels)
{
    ui->setupUi(this);
    this->setWindowTitle("GESTION DES MATÉRIELS");
    resize(1000,450);
    this->matriculeUtilisateurGlobal = Matricule; // initialise le matricule pour le lié avec celle dans la fenêtre de connection..
    bienvenueUtil(matriculeUtilisateurGlobal); // Appel du fonction Bienvenue

    ui->ajoutMat->setStyleSheet(qstyle.one);
    ui->zonederecherche->setStyleSheet(qstyle.zoneRecherche);
    ui->BttnListIntervenant->setStyleSheet(qstyle.BttnGauche);
    ui->listmatEntretenu->setStyleSheet(qstyle.BttnGauche);
    ui->retourBttn->setStyleSheet(qstyle.changeUtil);
    ui->quiterBttn->setStyleSheet(qstyle.quitU);

    ui->quiterBttn->installEventFilter(this); // Quand le souris passe par le boutton quitter
    ui->BttnListIntervenant->installEventFilter(this);
    ui->listmatEntretenu->installEventFilter(this);

    // Intégration des icons dans les bouttons
    ui->listmatEntretenu->setIcon(QIcon(":/images/Images/fix-work-repair-system-svgrepo-com.svg"));
    ui->listmatEntretenu->setIconSize(QSize(50,50));
    ui->BttnListIntervenant->setIcon(QIcon(":/images/Images/list-1422-svgrepo-com.svg"));
    ui->BttnListIntervenant->setIconSize(QSize(50,50));
    ui->detailsMat->setIcon(QIcon(":/images/Images/details-block-svgrepo-com.svg"));
    ui->detailsMat->setIconSize(QSize(20,20));
    ui->retourBttn->setIcon(QIcon(":/images/Images/logout-svgrepo-com.svg"));
    ui->retourBttn->setIconSize(QSize(30,30));
    ui->quiterBttn->setIcon(QIcon(":/images/Images/system-shutdown-panel-svgrepo-com.svg"));
    ui->quiterBttn->setIconSize(QSize(30,30));

    // Figé les bouttons
    ui->modifMat->setDisabled(true);
    ui->supprimMat->setDisabled(true);
    ui->IntervenirMat->setDisabled(true);
//    ui->IntervenirMat->setStyleSheet(qstyle.BttnEntretient0);
    ui->supprimerMatEntretenu->setDisabled(true);
    ui->factureBttn->setEnabled(false);

    ui->viewIntervenantVide->setHidden(true);

//    // Animation pour QFrame
//    frame = ui->gaucheFrame;
//    animation = new QPropertyAnimation(frame, "maxWidth", this);
//    animation->setDuration(300);
//    animation->setEasingCurve(QEasingCurve::InOutCubic);
//    frame->installEventFilter(this);

    afficheIntervenants();
    afficheListeIntervention();
    afficheMateriels();
}

ListMateriels::~ListMateriels()
{
    delete ui;
}

bool ListMateriels::eventFilter(QObject *obj, QEvent *evenm) // Fonction pour modifier les bouttons au survol
{
    if (obj == ui->quiterBttn) {
        if (evenm->type() == QEvent::Enter) {
            ui->quiterBttn->setText("QUITTER");
            ui->quiterBttn->setStyleSheet(qstyle.quitUtil);
            ui->quiterBttn->setIconSize(QSize(20,20));
        } else if (evenm->type() == QEvent::Leave){
            ui->quiterBttn->setText("");
            ui->quiterBttn->setIconSize(QSize(30,30));
            ui->quiterBttn->setStyleSheet(qstyle.quitU);
        }
    } else if (obj == ui->BttnListIntervenant) {
        if (evenm->type() == QEvent::Enter) {
            ui->BttnListIntervenant->setText("INTERVENANTS");
            ui->BttnListIntervenant->setIconSize(QSize(30,30));
        } else if (evenm->type() == QEvent::Leave) {
            ui->BttnListIntervenant->setText("");
            ui->BttnListIntervenant->setIconSize(QSize(50,50));
        }
    } else if (obj == ui->listmatEntretenu) {
        if (evenm->type() == QEvent::Enter) {
            ui->listmatEntretenu->setText("ENTRETIENTS");
            ui->listmatEntretenu->setIconSize(QSize(50,30));
        } else if (evenm->type() == QEvent::Leave) {
            ui->listmatEntretenu->setText("");
            ui->listmatEntretenu->setIconSize(QSize(50,50));
        }
    }
    return QDialog::eventFilter(obj, evenm);
}

void ListMateriels::bienvenueUtil(int matr) // MESSAGE DE BIENVENUE
{
    connectbdd bdd;
    bdd.mivohabdd();
    QSqlQuery querybvn;
    querybvn.prepare("SELECT PseudoUtilisateur FROM Utilisateurs WHERE Matricule=:matricule;");
    querybvn.bindValue(":matricule", matr);
    if (querybvn.exec()) {
        if (querybvn.next()) {
            qDebug() << "BIENVENUE : " << matr;
            ui->LabelBienvenue->setText("<p style='font-size: 20px'>Bienvenue <span style='font-weight: bold;'>"+querybvn.value(0).toString()+"</span></p>"); // Prise du Pseudo
            bdd.mihidybdd();
        } else qDebug() << "tsisy eh...";
    } else {
        qDebug() << "ERREUR DE BIENVENUE : " <<querybvn.lastError();
    }
}


void ListMateriels::on_ajoutMat_clicked() // AJOUT matériels
{
    cout << "mampidira materiel.." << endl;
    mat = new materiel(matriculeUtilisateurGlobal); // paramétrer "matriculeGlobal dans la fenêtre materiel
    mat->setModal(true);
    mat->exec();
    afficheMateriels();
}

void ListMateriels::on_retourBttn_clicked()
{
    QMessageBox::StandardButton message;
    message = QMessageBox::warning(this, "Confirmation",
                                  QString("CHANGER D'UTILISATEUR !?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if (message == QMessageBox::Yes) {
        this->close();
        MainWindow *wind= new  MainWindow(this);
        wind->show();
    } else {
        cout << "vous êtes encore connecter en tant que : " << matriculeUtilisateurGlobal << endl;
    }
}

void ListMateriels::on_quiterBttn_clicked() // QUITER L'APP
{
//    AVERTISSEMENT2 avert;
//    cout << "avertissement_2" << endl;
//    avert.exec();
    // Message pour quitter l'application
    QMessageBox::StandardButton message;
    message = QMessageBox::warning(this, "Confirmation",
                                  QString("VOULEZ VOUS QUITTER L'APPLICATION !?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if (message == QMessageBox::Yes) {
        this->close();
    } else {
    }
}


void ListMateriels::afficheMateriels() // AFFICHER LES MATÉRIELS
{
    connectbdd connbdd;
    connbdd.mivohabdd();

    model = new QSqlQueryModel(ui->page);
    model->setQuery("SELECT * FROM MaterielsInfo;");
    model->setHeaderData(0,Qt::Horizontal,tr("Numéro"));
    model->setHeaderData(1,Qt::Horizontal,tr("Designation"));
    model->setHeaderData(2,Qt::Horizontal,tr("Marque"));
    model->setHeaderData(3,Qt::Horizontal,tr("Etat"));
    model->setHeaderData(4,Qt::Horizontal,tr("Dernière_Intervention"));
    ui->viewMateriel->setModel(model);

    connbdd.mihidybdd();
    //figé les bouttons tant qu'ils sont pas cliquer
    ui->modifMat->setDisabled(true);
    ui->supprimMat->setDisabled(true);
}


void ListMateriels::afficheIntervenants() // AFFICHER LA LISTE D'INTERVENANTS
{
    connectbdd connbdd;
    connbdd.mivohabdd();

    model = new QSqlQueryModel(ui->page_2);
    model->setQuery("SELECT * FROM Intervenants;");
    model->setHeaderData(0,Qt::Horizontal,tr("NumIntervenant"));
    model->setHeaderData(1,Qt::Horizontal,tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,tr("Téléphone"));
    model->setHeaderData(3,Qt::Horizontal,tr("Spécialités"));
    model->setHeaderData(4,Qt::Horizontal,tr("Taux_Horraire /Ar"));
    ui->viewIntervenant->setModel(model);
    connbdd.mihidybdd();
}

void ListMateriels::on_viewIntervenant_clicked(const QModelIndex &index)
{
    IdIntervenant = ui->viewIntervenant->model()->data(ui->viewIntervenant->model()->index(index.row(),0)).toInt();
}


void ListMateriels::on_viewMateriel_clicked(const QModelIndex &index)
{
    // Prise des valeurs dans les tableaux
    Nb = ui->viewMateriel->model()->data(ui->viewMateriel->model()->index(index.row(),0)).toString();
    type = ui->viewMateriel->model()->data(ui->viewMateriel->model()->index(index.row(),1)).toString();
    marque = ui->viewMateriel->model()->data(ui->viewMateriel->model()->index(index.row(),2)).toString();
    etat = ui->viewMateriel->model()->data(ui->viewMateriel->model()->index(index.row(),3)).toString();
    dernierint = ui->viewMateriel->model()->data(ui->viewMateriel->model()->index(index.row(),4)).toString();
//    qDebug() << Nb;
//    qDebug() << marque;
//    qDebug() << type;
//    qDebug() << etat;

    // gestion boutton intervention
//    qDebug() << etat;
    if (etat=="ÇA VA ALLER") {
        ui->IntervenirMat->setDisabled(false);
        ui->IntervenirMat->setStyleSheet(qstyle.BttnEntretient0);
    } else if (etat=="PRUDENCE") {
        ui->IntervenirMat->setDisabled(false);
        ui->IntervenirMat->setStyleSheet(qstyle.BttnEntretient1);
    } else if (etat=="MEDIOCRE") {
        ui->IntervenirMat->setDisabled(false);
        ui->IntervenirMat->setStyleSheet(qstyle.BttnEntretient2);
    } else if(etat=="INCONNU") {
        ui->IntervenirMat->setDisabled(false);
        ui->IntervenirMat->setStyleSheet(qstyle.BttnEntretient0);
    } else {
        ui->IntervenirMat->setDisabled(true);
        ui->IntervenirMat->setStyleSheet(qstyle.Bttnnone);
    }

    ui->modifMat->setDisabled(false);
    ui->supprimMat->setDisabled(false);
}



// Modification en double click
void ListMateriels::on_viewMateriel_doubleClicked(const QModelIndex &index)
{
    modifMat modifMat;
    modifMat.getData(type, marque, etat, dernierint);
    // modifMat.Nbr = modifMat.getNb(Nb);
    modifMat.Nbr = modifMat.getNb(ui->viewMateriel->model()->data(ui->viewMateriel->model()->index(index.row(),0)).toString());
    modifMat.exec();
    afficheMateriels();
}

void ListMateriels::on_supprimMat_clicked() // SUPPRIMER UNE MATÉRIELE INFO
{
    qDebug() << Nb;
    QMessageBox mess;
    mess.setText("SUPPRIMER !?");
    QPushButton *o = mess.addButton(QMessageBox::Yes);
    QPushButton *n = mess.addButton(QMessageBox::Cancel);
    mess.exec();
    if (mess.clickedButton()==o) {
        connectbdd connbdd;
        connbdd.mivohabdd();
        QSqlQuery suppr;
        suppr.prepare("DELETE FROM MaterielsInfo WHERE NumMatInfo=:nb;");
        suppr.bindValue(":nb", Nb);
        if (suppr.exec()) {
            qDebug() << "ligne supprimer: " << Nb;
            connbdd.mihidybdd();
            afficheMateriels();
        } else {
            qDebug() << "Erreur de suppression.";
            qDebug() << suppr.lastError();
        }

    } else if (mess.clickedButton()==n) {
        cout << "Donnée non supprimer.." << endl;
    }
}

void ListMateriels::on_modifMat_clicked() // Modification Matériels
{
    modifMat modifMat;
    modifMat.getData(marque, type, etat, dernierint);
    modifMat.Nbr = modifMat.getNb(Nb);
    modifMat.exec();
    afficheMateriels();
}


void ListMateriels::afficheListeIntervention() // AFFICHE LA LISTE DE MATÉRIELS EN ENTRETIENTS
{
    connectbdd connbdd;
    connbdd.mivohabdd();
    model = new QSqlQueryModel(ui->page_3);
    model->setQuery("SELECT Entretients.NumMateriel,ProblemMateriel,MaterielsInfo.Designations,Marques,Etats,Interventions.DateDebut,Nb_heure,DateFin,Intervenants.Nom,NumeroTel,Entretients.NumEntretient "
                    "FROM Entretients INNER JOIN MaterielsInfo ON MaterielsInfo.NumMatInfo=Entretients.NumMateriel "
                    "INNER JOIN Interventions ON Interventions.Numero=Entretients.NumeroIntervention "
                    "INNER JOIN Intervenants ON Intervenants.NumInt=Entretients.IdIntervenant;"
                    );
    model->setHeaderData(0,Qt::Horizontal,tr("N° Matériels"));
    model->setHeaderData(1,Qt::Horizontal,tr("Problem"));
    model->setHeaderData(2,Qt::Horizontal,tr("Désignation"));
    model->setHeaderData(3,Qt::Horizontal,tr("Marques"));
    model->setHeaderData(4,Qt::Horizontal,tr("États"));
    model->setHeaderData(5,Qt::Horizontal,tr("Debut"));
    model->setHeaderData(6,Qt::Horizontal,tr("Heure"));
    model->setHeaderData(7,Qt::Horizontal,tr("Fin"));
    model->setHeaderData(8,Qt::Horizontal,tr("NomRéparateurs"));
    model->setHeaderData(9,Qt::Horizontal,tr("Téléphone"));
    model->setHeaderData(10,Qt::Horizontal,tr("Entretient N°"));
    ui->viewEntretient->setModel(model);

    connbdd.mihidybdd();
}

void ListMateriels::on_IntervenirMat_clicked() // CLICK SUR le Boutton INTERVENIR
{
    EntretientMateriels *entretientMat = new EntretientMateriels(matriculeUtilisateurGlobal);
    // Récuperation des données pour les mettres dans la fenêtre
    entretientMat->getdonner(type,marque,etat,Nb);

    connectbdd conbdd;
    conbdd.mivohabdd();
    QSqlQuery queryajout;
    queryajout.prepare("SELECT Nom,NumeroTel,TauxHorraire,NumInt FROM Intervenants WHERE NumInt=?");

    if (type=="CLAVIER" || type=="SOURIS") {
        queryajout.bindValue(0,0);
        if (queryajout.exec()) {
            while (queryajout.next()) {
                numIntervenant = queryajout.value(3).toInt();
                QString Nom = queryajout.value(0).toString();
                QString Num = queryajout.value(1).toString();
                QString Taux = queryajout.value(2).toString();
                entretientMat->getinfoEntretient(Nom, Num, Taux);
                entretientMat->getIdIntervenant(numIntervenant);
            }
        } else { qDebug() << "Erreur execution requête: "<<queryajout.lastError().text(); }
    } else if (type=="RESEAUX" || type=="PORTABLE") {
        queryajout.bindValue(0,7);
        if (queryajout.exec()) {
            while (queryajout.next()) {
                numIntervenant = queryajout.value(3).toInt();
                QString Nom = queryajout.value(0).toString();
                QString Num = queryajout.value(1).toString();
                QString Taux = queryajout.value(2).toString();
                entretientMat->getinfoEntretient(Nom, Num, Taux);
                entretientMat->getIdIntervenant(numIntervenant);
            }
        } else { qDebug() << "Erreur execution requête: "<<queryajout.lastError().text(); }
    } else if (type=="IMPRIMANTE" || type=="ALIMENTATION") {
        queryajout.bindValue(0,8);
        if (queryajout.exec()) {
            while (queryajout.next()) {
                numIntervenant = queryajout.value(3).toInt();
                QString Nom = queryajout.value(0).toString();
                QString Num = queryajout.value(1).toString();
                QString Taux = queryajout.value(2).toString();
                entretientMat->getinfoEntretient(Nom, Num, Taux);
                entretientMat->getIdIntervenant(numIntervenant);
            }
        } else { qDebug() << "Erreur execution requête: "<<queryajout.lastError().text(); }
    } else if (type=="ECRAN" || type=="UNITE CENTRALE") {
        queryajout.bindValue(0,9);
        if (queryajout.exec()) {
            while (queryajout.next()) {
                numIntervenant = queryajout.value(3).toInt();
                QString Nom = queryajout.value(0).toString();
                QString Num = queryajout.value(1).toString();
                QString Taux = queryajout.value(2).toString();
                entretientMat->getinfoEntretient(Nom, Num, Taux);
                entretientMat->getIdIntervenant(numIntervenant);
            }
        } else { qDebug() << "Erreur execution requête: "<<queryajout.lastError().text(); }
    } else {
        queryajout.bindValue(0,1);
        if (queryajout.exec()) {
            while (queryajout.next()) {
                numIntervenant = queryajout.value(3).toInt();
                QString Nom = queryajout.value(0).toString();
                QString Num = queryajout.value(1).toString();
                QString Taux = queryajout.value(2).toString();
                entretientMat->getinfoEntretient(Nom, Num, Taux);
                entretientMat->getIdIntervenant(numIntervenant);
            }
        } else { qDebug() << "Erreur execution requête: "<<queryajout.lastError().text(); }
    }

    conbdd.mihidybdd();
    entretientMat->exec();
    afficheListeIntervention();
}

void ListMateriels::on_supprimerMatEntretenu_clicked() // SUPPRIMER MATÉRIELS ENTRETENUE
{
    qDebug() << numEntretient;
    QMessageBox mess;
    mess.setText("SUPPRIMER !?");
    QPushButton *o = mess.addButton(QMessageBox::Yes);
    QPushButton *n = mess.addButton(QMessageBox::Cancel);
    mess.exec();
    if (mess.clickedButton()==o) {
        connectbdd connbdd;
        connbdd.mivohabdd();
        QSqlQuery suppr;
        suppr.prepare("DELETE FROM Entretients WHERE NumEntretient=:num");
        suppr.bindValue(":num", numEntretient);
        if (suppr.exec()) {
            qDebug() << "ligne supprimer: " << numEntretient;
            connbdd.mihidybdd();
            afficheListeIntervention();
            QMessageBox::information(this, "Information", "ligne "+numEntretient+" supprimer");
        } else {
            qDebug() << "Erreur de suppression.";
            qDebug() << suppr.lastError();
        }

    } else if (mess.clickedButton()==n) {
        cout << "Donnée non supprimer.." << endl;
    }
}

void ListMateriels::on_viewEntretient_doubleClicked(const QModelIndex &index) // MODIFICATION ENTRETIENT MATÉRIELS
{
//    EntretientMateriels *entretients = new EntretientMateriels(matriculeUtilisateurGlobal);
//    numModifNumIntervention = entretients->setIntervention(Inter);
    modifentretientmateriels *modificationEntretient = new modifentretientmateriels(numModifNumIntervention);
    modificationEntretient->getdonnerEntretient(typeEntretient, marqueEntretient, etatEntretient, blemEntretient, numMatEntretient, datedebutEntretient, heureEntretient, datefinEntretient, numIntEntretient, nomIntEntretient);
    modificationEntretient->numEntretients = modificationEntretient->getNumEntretient(ui->viewEntretient->model()->data(ui->viewEntretient->model()->index(index.row(),0)).toString());
    modificationEntretient->exec();
    afficheListeIntervention();
}

void ListMateriels::on_viewEntretient_clicked(const QModelIndex &index)
{
    numMatEntretient = ui->viewEntretient->model()->data(ui->viewEntretient->model()->index(index.row(),0)).toString();
    blemEntretient = ui->viewEntretient->model()->data(ui->viewEntretient->model()->index(index.row(),1)).toString();
    typeEntretient = ui->viewEntretient->model()->data(ui->viewEntretient->model()->index(index.row(),2)).toString();
    marqueEntretient = ui->viewEntretient->model()->data(ui->viewEntretient->model()->index(index.row(),3)).toString();
    etatEntretient = ui->viewEntretient->model()->data(ui->viewEntretient->model()->index(index.row(),4)).toString();
    datedebutEntretient = QDate::fromString(debutEntretient, "dd/MM/yyyy");
    debutEntretient = ui->viewEntretient->model()->data(ui->viewEntretient->model()->index(index.row(),5)).toString();
    heureEntretient = ui->viewEntretient->model()->data(ui->viewEntretient->model()->index(index.row(),6)).toInt(); // Heure Entretient
    datefinEntretient = QDateTime::fromString(finEntretient, "dd/MM/yyyy HH:mm");
    finEntretient = ui->viewEntretient->model()->data(ui->viewEntretient->model()->index(index.row(),7)).toString();
    nomIntEntretient = ui->viewEntretient->model()->data(ui->viewEntretient->model()->index(index.row(),8)).toString();
    numIntEntretient = ui->viewEntretient->model()->data(ui->viewEntretient->model()->index(index.row(),9)).toString();
    numEntretient = ui->viewEntretient->model()->data(ui->viewEntretient->model()->index(index.row(),10)).toString();

//    qDebug() << var;
//    qDebug() << numIntEntretient;
//    qDebug() << nomIntEntretient;
//    qDebug() << tauxHorEntretient;
    ui->supprimerMatEntretenu->setDisabled(false);
    ui->factureBttn->setDisabled(false);
    ui->supprimerMatEntretenu->setStyleSheet(qstyle.BttnEntretient2);
}


void ListMateriels::on_detailsMat_clicked() // DETAILS DES MATÉRIELS
{
    DetailsMateriels *detailMat = new DetailsMateriels(matriculeUtilisateurGlobal);
    detailMat->exec();
}

void ListMateriels::on_BttnListIntervenant_clicked()
{
    ui->materielStackW->setCurrentIndex(1);
    ui->BttnListIntervenant->setDisabled(true);
    afficheIntervenants();
}

void ListMateriels::on_listmatEntretenu_clicked()
{
    ui->materielStackW->setCurrentIndex(2);
    ui->listmatEntretenu->setDisabled(true);
    afficheListeIntervention();
}

void ListMateriels::on_retourListMat_clicked()
{
    ui->materielStackW->setCurrentIndex(0);
    afficheMateriels();
}

void ListMateriels::on_listmatEnt_clicked()
{
    ui->materielStackW->setCurrentIndex(0);
    afficheMateriels();
}


void ListMateriels::on_materielStackW_currentChanged(int index) // gestion des bouttons pour quand on change de fenêtre
{
    if (index==2) {
        ui->BttnListIntervenant->setDisabled(false);
    } else if (index==1) {
        ui->listmatEntretenu->setDisabled(false);
    } else {
        ui->BttnListIntervenant->setEnabled(true);
        ui->listmatEntretenu->setEnabled(true);
    }
}


void ListMateriels::on_zonederecherche_textChanged(const QString &text)
{
    connectbdd bdd;
    bdd.mivohabdd();
    QString queryString = QString(
            "SELECT Nom, NumeroTel,Specialité,TauxHorraire "
            "FROM Intervenants "
            "WHERE Nom LIKE '%%1%' OR NumeroTel LIKE '%%1%'"
        ).arg(text);
    model->setQuery(queryString);

    if (model->rowCount() == 0) {
        ui->viewIntervenantVide->setHidden(false);
        ui->viewIntervenantVide->setText("VIDE");
        ui->viewIntervenant->setHidden(true);
    } else {
        ui->viewIntervenantVide->setHidden(true);
        ui->viewIntervenant->setHidden(false);
    }
    ui->viewIntervenant->setModel(model);
    bdd.mihidybdd();
}



void ListMateriels::on_zonederecherche_editingFinished() // Finition dans la recherche
{
    connectbdd bdd;
    bdd.mivohabdd();
    QSqlQuery queryint;
    queryint.prepare("INSERT INTO Recherche(NumInt,IdUtilisateur) VALUES(:IdInt,:IdUtil);");
    queryint.bindValue(":IdInt", IdIntervenant);
    queryint.bindValue(":IdUtil", matriculeUtilisateurGlobal);

    if (queryint.exec()) {
        qDebug() << "INSERTION DANS RECHERCHE OK";
        bdd.mihidybdd();
    } else qDebug() << "Erreur : " << queryint.lastError();
}


void ListMateriels::on_factureBttn_clicked() // Ouverture du fenêtre FACTURE
{
    int numEnt = numEntretient.toInt();
    facture *fact = new facture(heureEntretient,numEnt);
    fact->exec();
}

