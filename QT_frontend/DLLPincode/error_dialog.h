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
    void show_error();

private:
    Ui::Error_dialog *ui;
};

#endif  // ERROR_DIALOG_H
