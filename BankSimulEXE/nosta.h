#ifndef NOSTA_H
#define NOSTA_H

#include <QDialog>

namespace Ui {
class Nosta;
}

class Nosta : public QDialog
{
    Q_OBJECT

public:
    explicit Nosta(QWidget *parent = nullptr);
    ~Nosta();

private:
    Ui::Nosta *ui;
};

#endif // NOSTA_H
