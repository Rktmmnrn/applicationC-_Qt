#ifndef MODIFMAT_H
#define MODIFMAT_H
#include "stylesheet.h"

#include <QDialog>
#include <QString>

namespace Ui {
class modifMat;
}

class modifMat : public QDialog
{
    Q_OBJECT

public:
    explicit modifMat(QWidget *parent = nullptr);

    QString NbMat;
    QString Marque;
    QString Type;
    QString Etat;
    QString DernInt;

    QString Nbr; //variable prise dans listemateriel
    QString getNb(QString Nb);

    void getData(QString marque, QString type, QString etat, QString dernierint);

    stylesheet style;

    ~modifMat();

private slots:
    void on_annulerModif_clicked();

    void on_modif_clicked();

private:
    Ui::modifMat *ui;
};

#endif // MODIFMAT_H
