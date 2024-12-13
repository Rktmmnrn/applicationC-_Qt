#ifndef FACTURE_H
#define FACTURE_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class facture;
}

class facture : public QDialog
{
    Q_OBJECT

public:
    explicit facture(int heure,int numEnt, QWidget *parent = nullptr);

    int heureIntervention;
    int numEntretient;

    void calculeTotal(int idEntretient);

    QStringList factList;

    void generationPDF();

    ~facture();

private slots:
    void on_editionPDF_clicked();

private:
    Ui::facture *ui;
};

#endif // FACTURE_H
