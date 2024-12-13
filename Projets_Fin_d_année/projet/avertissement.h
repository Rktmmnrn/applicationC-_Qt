#ifndef AVERTISSEMENT_H
#define AVERTISSEMENT_H

#include <QDialog>

namespace Ui {
class AVERTISSEMENT;
}

class AVERTISSEMENT : public QDialog
{
    Q_OBJECT

public:
    explicit AVERTISSEMENT(QWidget *parent = nullptr);
    ~AVERTISSEMENT();

private slots:
    void on_OUI_clicked();

    void on_NON_clicked();

private:
    Ui::AVERTISSEMENT *ui;
};

#endif // AVERTISSEMENT_H
