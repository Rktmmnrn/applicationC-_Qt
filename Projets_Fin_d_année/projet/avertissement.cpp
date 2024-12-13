#include "avertissement.h"
#include "ui_avertissement.h"
#include "mainwindow.h"

#include <dialog.h>

AVERTISSEMENT::AVERTISSEMENT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AVERTISSEMENT)
{
    ui->setupUi(this);
     this->setWindowTitle("AVERTISSEMENT");
}

AVERTISSEMENT::~AVERTISSEMENT()
{
    delete ui;
}

void AVERTISSEMENT::on_OUI_clicked()
{
    this->close();


}


void AVERTISSEMENT::on_NON_clicked()
{
MainWindow *dee= new  MainWindow;
dee->show();
this->close();
}
