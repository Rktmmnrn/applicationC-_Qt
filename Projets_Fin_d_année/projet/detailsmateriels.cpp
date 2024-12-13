#include "detailsmateriels.h"
#include "ui_detailsmateriels.h"
#include "connectbdd.h"

DetailsMateriels::DetailsMateriels(int matriculeU, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailsMateriels)
{
    ui->setupUi(this);
    this->setWindowTitle("DETAILS DES MATÉRIELS");
    resize(700,400);
    this->matriculeUt = matriculeU; // récuperation du matricule de l'utilisateurs

    affichedetailsMat();
}

DetailsMateriels::~DetailsMateriels()
{
    delete ui;
}

void DetailsMateriels::on_OK_clicked()
{
    this->close();
}

void DetailsMateriels::affichedetailsMat()
{
    connectbdd basedd;
    basedd.mivohabdd();
    QSqlQueryModel *querymodeldetails;
    querymodeldetails = new QSqlQueryModel(ui->MaterielsView);
    querymodeldetails->setQuery("SELECT Utilisateurs.Matricule,Gestion.IdMatInfo,MaterielsInfo.Designations,Marques "
                                "FROM Utilisateurs INNER JOIN Gestion ON Gestion.MatriculeUtilisateur=Utilisateurs.Matricule "
                                "INNER JOIN MaterielsInfo ON MaterielsInfo.NumMatInfo=Gestion.IdMatInfo;");
    querymodeldetails->setHeaderData(0,Qt::Horizontal,tr("Utilisateurs N°"));
    ui->MaterielsView->setModel(querymodeldetails);
    basedd.mihidybdd();
}

void DetailsMateriels::on_MaterielsView_clicked(const QModelIndex &index)
{
    IdUtilisateurs = ui->MaterielsView->model()->data(ui->MaterielsView->model()->index(index.row(), 0)).toInt();
    designationMatI = ui->MaterielsView->model()->data(ui->MaterielsView->model()->index(index.row(), 1)).toString();
    marqueMatI = ui->MaterielsView->model()->data(ui->MaterielsView->model()->index(index.row(), 2)).toString();

    connectbdd bdd;
    bdd.mivohabdd();
    QSqlQuery querydetails;
    querydetails.prepare("SELECT Utilisateurs.NomUtilisateur,PseudoUtilisateur,Gestion.IdMatInfo,MaterielsInfo.Etats,DernierIntervention,Interventions.DateDebut,Nb_heure,DateFin "
                         "FROM Utilisateurs INNER JOIN Gestion ON Utilisateurs.Matricule=Gestion.MatriculeUtilisateur "
                         "INNER JOIN Interventions ON Interventions.IdUtilisateur=Utilisateurs.Matricule "
                         "INNER JOIN MaterielsInfo ON MaterielsInfo.NumMatInfo=Gestion.IdMatInfo WHERE Matricule=:matriculeU;");
    querydetails.bindValue(":matriculeU", IdUtilisateurs);

    QStringList detailsList;
    if (querydetails.exec() && querydetails.next()) {
        detailsList << "Utilisateurs : " + querydetails.value(0).toString();
        detailsList << "Son Pseudo : " + querydetails.value(1).toString();
        detailsList << "Matériels N° : " + querydetails.value(2).toString();
        detailsList << "États du matériels : " + querydetails.value(3).toString();
        detailsList << "Dérnière Intervention le : " + querydetails.value(4).toString();
        detailsList << "Début de l'Intervention le : " + querydetails.value(5).toString();
        detailsList << "Durée : " + querydetails.value(6).toString() + "Heure";
        detailsList << "Fin de l'Intervention le : " + querydetails.value(7).toString();
    } else qDebug() << "ERREUR DETAILS : " << querydetails.lastError();

    listmodel = new QStringListModel(this);
    listmodel->setStringList(detailsList);
    ui->detailsMatListView->setModel(listmodel);
    bdd.mihidybdd();
}
