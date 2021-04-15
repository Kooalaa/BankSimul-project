#ifndef BROWSE_TRANSACTIONS_H
#define BROWSE_TRANSACTIONS_H

#include <QDialog>

namespace Ui {
class browse_transactions;
}

class browse_transactions : public QDialog {
    Q_OBJECT

public:
    explicit browse_transactions(QWidget *parent = nullptr);
    ~browse_transactions();

private:
    Ui::browse_transactions *ui;
};

#endif  // BROWSE_TRANSACTIONS_H
