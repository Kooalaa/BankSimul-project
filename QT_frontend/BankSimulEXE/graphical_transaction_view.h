#ifndef GRAPHICAL_TRANSACTION_VIEW_H
#define GRAPHICAL_TRANSACTION_VIEW_H

#include <QDialog>

namespace Ui {
class graphical_transaction_view;
}

class graphical_transaction_view : public QDialog
{
    Q_OBJECT

public:
    explicit graphical_transaction_view(QWidget *parent = nullptr);
    ~graphical_transaction_view();

private:
    Ui::graphical_transaction_view *ui;
};

#endif // GRAPHICAL_TRANSACTION_VIEW_H
