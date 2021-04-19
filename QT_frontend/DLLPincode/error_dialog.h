#ifndef ERROR_DIALOG_H
#define ERROR_DIALOG_H

#include <QDialog>

namespace Ui {
class Error_dialog;
}

class Error_dialog : public QDialog {
    Q_OBJECT

public:
    explicit Error_dialog(QWidget *parent = nullptr);
    ~Error_dialog();
public slots:
    void show_error(int attempts);
    void show_locked_card();

private:
    Ui::Error_dialog *ui;
    QString error;
};

#endif  // ERROR_DIALOG_H
