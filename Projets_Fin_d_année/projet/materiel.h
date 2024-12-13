#ifndef MATERIEL_H
#define MATERIEL_H
#include "mainwindow.h"

#include <QDialog>
#include <QSqlQuery>

class MainWindow;

namespace Ui {
class materiel;
}

class materiel : public QDialog
{
    Q_OBJECT

public:
    explicit materiel(int matricule, QWidget *parent = nullptr);

    int matriculeMatGlobal;
    MainWindow *mainW;
    QVariant lastIdMateriel;
    QVariant lastIdU;

    ~materiel();

private slots:
    void on_VALIDER_clicked();

    void on_RETOUR_clicked();

private:
    Ui::materiel *ui;
};

#endif // MATERIEL_H
