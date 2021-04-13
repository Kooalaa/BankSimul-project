#ifndef TALLETA_H
#define TALLETA_H

#include <QDialog>

namespace Ui {
class Talleta;
}

class Talleta : public QDialog
{
    Q_OBJECT

public:
    explicit Talleta(QWidget *parent = nullptr);
    ~Talleta();

private:
    Ui::Talleta *ui;
};

#endif // TALLETA_H
