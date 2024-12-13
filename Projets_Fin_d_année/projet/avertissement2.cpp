#include "avertissement2.h"
#include "ui_avertissement2.h"

#include <listmateriels.h>

AVERTISSEMENT2::AVERTISSEMENT2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AVERTISSEMENT2)
{
    ui->setupUi(this);
     this->setWindowTitle("AVERTISSEMENT");
}

AVERTISSEMENT2::~AVERTISSEMENT2()
{
    delete ui;
}

void AVERTISSEMENT2::on_OUI_clicked()
{
    this->close();
}


void AVERTISSEMENT2::on_NON_clicked()
{
    this->close();
    ListMateriels *listmat;
    listmat->exec();
}
