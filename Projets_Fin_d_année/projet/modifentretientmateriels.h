#ifndef MODIFENTRETIENTMATERIELS_H
#define MODIFENTRETIENTMATERIELS_H

#include <QDialog>

namespace Ui {
class modifentretientmateriels;
}

class modifentretientmateriels : public QDialog
{
    Q_OBJECT

public:
    explicit modifentretientmateriels(int numModifInt, QWidget *parent = nullptr);

    void getdonnerEntretient(QString designation, QString marque, QString etat, QString problem, QString numMat, QDate &debut, int duree, QDateTime &fin, QString &numInt, QString &nomInt);
    QString getNumEntretient(QString numEntretient);
    QString numEntretients;

    QString typeM;
    QString marqueM;
    QString etatM;
    QString blemM;
    int numM;
    QString debutI;
    QString nbHI;
    QString finI;
    QString numII;
    QString nomII;

    int numModif;

    ~modifentretientmateriels();

private slots:
    void on_annulerEntretientModif_clicked();

    void on_envoyeEntretientModif_clicked();

    void on_dureeEntretientModif_valueChanged(int arg1);

private:
    Ui::modifentretientmateriels *ui;
};

#endif // MODIFENTRETIENTMATERIELS_H
