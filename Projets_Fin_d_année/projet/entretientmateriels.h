#ifndef ENTRETIENTMATERIELS_H
#define ENTRETIENTMATERIELS_H

#include <QDialog>

namespace Ui {
class EntretientMateriels;
}

class EntretientMateriels : public QDialog
{
    Q_OBJECT

public:
    explicit EntretientMateriels(int matriculeU,QWidget *parent = nullptr);

    void getdonner(QString typeEnt, QString marqueEnt, QString etatEnt, QString NumMatEnt);
    void getinfoEntretient(QString nom, QString phone, QString tauxhorraire);

    int numEntretient;

    int matriculeUtilisateur;
    int getIdIntervenant(int numInt);
    int numIntervenant;

    int NumIntervention;
    int setIntervention(int Inter);

    QString typeMatEnt;
    QString marqueMatEnt;
    QString etatMatEnt;
    QString blemMatEnt;
    int numMatEnt;
    QString datedebEnt;
    QString nbheureEnt;
    QString datefinEnt;
    QString nomIntEnt;
    QString phoneIntEnt;
    QString tauxhEnt;

    ~EntretientMateriels();

private slots:
    void on_annulerEntretient_clicked();

    void on_dureeEntretient_valueChanged(int heure);

    void on_debutEntretient_userDateChanged(const QDate &date);

    void on_envoyeEntretient_clicked();

private:
    Ui::EntretientMateriels *ui;
};

#endif // ENTRETIENTMATERIELS_H
