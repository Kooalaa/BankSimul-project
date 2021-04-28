#ifndef ERROR_DIALOG_H
#define ERROR_DIALOG_H

#include <QDialog>
#include <QTimer>
namespace Ui {
class Error_dialog;
}

class Error_dialog : public QDialog {
    Q_OBJECT

public:
    explicit Error_dialog(QWidget *parent = nullptr);
    ~Error_dialog();
    void show_error(int attempts);
    void show_locked_card();
private slots:
    void timer();

private:
    Ui::Error_dialog *ui;
    QString error;
    QTimer *p_timer;
    int time = 2;
    void stop_timer();
};

#endif  // ERROR_DIALOG_H
