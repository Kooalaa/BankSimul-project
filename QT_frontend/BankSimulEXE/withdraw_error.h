#ifndef WITHDRAW_ERROR_H
#define WITHDRAW_ERROR_H

#include <QDialog>

namespace Ui {
class withdraw_error;
}

class withdraw_error : public QDialog
{
    Q_OBJECT

public:
    explicit withdraw_error(QWidget *parent = nullptr);
    ~withdraw_error();

private:
    Ui::withdraw_error *ui;
};

#endif // WITHDRAW_ERROR_H
