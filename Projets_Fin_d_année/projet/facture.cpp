#include "facture.h"
#include "ui_facture.h"
#include "connectbdd.h"

#include <QSqlQuery>
#include <QStandardItemModel>
#include <QPainter>
#include <QPdfWriter>

facture::facture(int heure,int numEnt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::facture)
{
    ui->setupUi(this);
    this->setWindowTitle("FACTURE");
    this->heureIntervention = heure;
    this->numEntretient = numEnt;
    calculeTotal(numEntretient);
}

facture::~facture()
{
    connectbdd bdd;
    bdd.mihidybdd();
    delete ui;
}


void facture::calculeTotal(int idEntretient)
{
    connectbdd bdd;
    bdd.mivohabdd();
    QSqlQuery query;
    query.prepare("SELECT Entretients.NumeroIntervention,IdIntervenant,Interventions.Nb_heure,Intervenants.TauxHorraire "
                  "FROM Entretients INNER JOIN Interventions ON Entretients.NumeroIntervention=Interventions.Numero "
                  "INNER JOIN Intervenants ON Entretients.IdIntervenant=Intervenants.NumInt "
                  "WHERE Entretients.NumEntretient=:idEntretient;"
                  );
    query.bindValue(":idEntretient", idEntretient);

    if (query.exec() && query.next()) {
        qDebug() << idEntretient;
        int numIntervention = query.value(0).toInt();
        int idIntervenant = query.value(1).toInt();
        int nbHeure = query.value(2).toInt();
        double taux = query.value(3).toDouble();

        double total = nbHeure * taux;

        factList << QString("Numéro d'Intervention: %1").arg(numIntervention)
                 << QString("ID Intervenant: %1").arg(idIntervenant)
                 << QString("Nombre d'Heures: %1").arg(nbHeure)
                 << QString("Taux Horaire: %1").arg(taux)
                 << QString("Total 'Ar': %1").arg(total);

        QStandardItemModel *model = new QStandardItemModel(this);
        for (int i = 0; i < factList.size(); ++i) {
            model->appendRow(new QStandardItem(factList[i]));
        }
        ui->viewFacture->setModel(model);

        bdd.mihidybdd();
    } else {
        qDebug() << "ERREUR FACTURATION..." << query.lastError();
    }
}

void facture::on_editionPDF_clicked()
{
    connectbdd bddfact;
    bddfact.mivohabdd();
    generationPDF();
}

void facture::generationPDF()
{
    QPdfWriter writer("facture_2.pdf");
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);

    QPainter painter(&writer);
    painter.setFont(QFont("Arial", 20)); // Définition du police

    // Écrire le titre
    painter.drawText(100, 100, "Facture matériels");
    painter.drawText(100, 130, "Détails des interventions :");

    QSqlQuery query;
    query.prepare("SELECT Entretients.NumeroIntervention,IdIntervenant,Interventions.Nb_heure,Intervenants.TauxHorraire "
                  "FROM Entretients INNER JOIN Interventions ON Entretients.NumeroIntervention=Interventions.Numero "
                  "INNER JOIN Intervenants ON Entretients.IdIntervenant=Intervenants.NumInt;");

    if (query.exec()) {
        int yPosition = 200; // Position verticale de départ

        // En-tête de tableau
        painter.drawText(100, yPosition, "Numéro d'Intervention");
        painter.drawText(500, yPosition, "ID Intervenant");
        painter.drawText(900, yPosition, "Heures");
        painter.drawText(1300, yPosition, "Taux");

        yPosition += 30; // Espacement après l'en-tête

        // Récupérer et afficher les données de chaque ligne
        while (query.next()) {
            int numIntervention = query.value(0).toInt();
            int idIntervenant = query.value(1).toInt();
            int nbHeure = query.value(2).toInt();
            double taux = query.value(3).toDouble();

            painter.drawText(100, yPosition, QString::number(numIntervention));
            painter.drawText(250, yPosition, QString::number(idIntervenant));
            painter.drawText(400, yPosition, QString::number(nbHeure));
            painter.drawText(500, yPosition, QString::number(taux));

            yPosition += 20; // Avancer vers le bas pour la prochaine ligne
        }
        painter.end();
        qDebug() << "PDF généré avec succès.";
        this->close();
    } else {
        qDebug() << "Erreur lors de la récupération des données :" << query.lastError();
    }
}
