#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "stylesheet.h"

#include <QMainWindow>
#include <QtSql>
#include <QSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
//    QSqlDatabase bdd = QSqlDatabase:: database("MaConnexion");
//    connectbdd conn;
    stylesheet styleUtil;

    QString NomUtil;
    QString PseudoUtil;
    int MatriculeUtil;
    QString FonctionUtil;

    QString nomselectionner;
//    QString pseudoselectionner;

    ~MainWindow();

private slots:
    void on_ANNULER_clicked();

    void on_VALIDER_clicked();

    void on_EditNom_textChanged(const QString &arg1);

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
