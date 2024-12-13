#ifndef DETAILSMATERIELS_H
#define DETAILSMATERIELS_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QStringListModel>
#include <QSqlTableModel>

namespace Ui {
class DetailsMateriels;
}

class DetailsMateriels : public QDialog
{
    Q_OBJECT

public:
    explicit DetailsMateriels(int matriculeU ,QWidget *parent = nullptr);

    QStringListModel *listmodel;
    QSqlTableModel *tablemodel;
    int IdUtilisateurs;
    QString designationMatI;
    QString marqueMatI;

    int matriculeUt;

    void affichedetailsMat();

    void affichedetailsliste(int matricules);

    ~DetailsMateriels();

private slots:
    void on_OK_clicked();

    void on_MaterielsView_clicked(const QModelIndex &index);

private:
    Ui::DetailsMateriels *ui;
};

#endif // DETAILSMATERIELS_H
