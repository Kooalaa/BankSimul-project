#ifndef SELAA_H
#define SELAA_H

#include <QDialog>

namespace Ui {
class Selaa;
}

class Selaa : public QDialog
{
    Q_OBJECT

public:
    explicit Selaa(QWidget *parent = nullptr);
    ~Selaa();

private:
    Ui::Selaa *ui;
};

#endif // SELAA_H
