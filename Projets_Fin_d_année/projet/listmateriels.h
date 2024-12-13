#ifndef LISTMATERIELS_H
#define LISTMATERIELS_H
#include "mainwindow.h"
#include "materiel.h"
#include "stylesheet.h"

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QEvent>

namespace Ui {
class ListMateriels;
}

class ListMateriels : public QDialog
{
    Q_OBJECT

public:
    explicit ListMateriels(int Matricule, QWidget *parent = nullptr);
    void bienvenueUtil(int matr);

    int matriculeUtilisateurGlobal;
    int numIntervenant;
    materiel *mat;
    QSqlQueryModel *model;

    stylesheet qstyle;

    QString Nb;
    QString marque;
    QString type;
    QString etat;
    QString dernierint;

    QString numEntretient;
    QString typeEntretient;
    QString marqueEntretient;
    QString etatEntretient;
    QString blemEntretient;
    QString numMatEntretient;
    QString debutEntretient;
    QDate datedebutEntretient;
    int heureEntretient;
    QString finEntretient;
    QDateTime datefinEntretient;
    QString numIntEntretient;
    QString nomIntEntretient;
    QString tauxHorEntretient;

    int IdIntervenant;

    int numModifNumIntervention;

    QSqlTableModel *tableModel;

    void afficheMateriels();

    void afficheIntervenants();

    void afficheListeIntervention();

    ~ListMateriels();

private slots:
    void on_ajoutMat_clicked();

    void on_retourBttn_clicked();

    void on_quiterBttn_clicked();

    void on_viewMateriel_clicked(const QModelIndex &index);

//    void selectItem(const QModelIndex &index);
    void on_supprimMat_clicked();

    void on_modifMat_clicked();

    void on_viewMateriel_doubleClicked(const QModelIndex &index);

    void on_IntervenirMat_clicked();

    void on_detailsMat_clicked();

    void on_BttnListIntervenant_clicked();

    void on_retourListMat_clicked();

    void on_listmatEnt_clicked();

    void on_listmatEntretenu_clicked();

    void on_supprimerMatEntretenu_clicked();

    void on_viewEntretient_doubleClicked(const QModelIndex &index);

    void on_viewEntretient_clicked(const QModelIndex &index);

    void on_materielStackW_currentChanged(int arg1);

    void on_zonederecherche_textChanged(const QString &text);

    void on_zonederecherche_editingFinished();

    void on_viewIntervenant_clicked(const QModelIndex &index);

    void on_factureBttn_clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *evenm) override;

private:

    Ui::ListMateriels *ui;
};

#endif // LISTMATERIELS_H
