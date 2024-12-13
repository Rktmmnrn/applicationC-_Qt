#ifndef AVERTISSEMENT2_H
#define AVERTISSEMENT2_H

#include <QDialog>

namespace Ui {
class AVERTISSEMENT2;
}

class AVERTISSEMENT2 : public QDialog
{
    Q_OBJECT

public:
    explicit AVERTISSEMENT2(QWidget *parent = nullptr);
    ~AVERTISSEMENT2();

private slots:
    void on_OUI_clicked();

    void on_NON_clicked();

private:
    Ui::AVERTISSEMENT2 *ui;
};

#endif // AVERTISSEMENT2_H
