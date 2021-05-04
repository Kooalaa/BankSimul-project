#ifndef WITHDRAW_DONE_H
#define WITHDRAW_DONE_H

#include <QDialog>
#include <QTimer>
namespace Ui {
class withdraw_done;
}

class withdraw_done : public QDialog {
    Q_OBJECT

public:
    explicit withdraw_done(QWidget *parent = nullptr);
    ~withdraw_done();
    void show_ui(QString, double, QString);
private slots:
    void on_pushButton_clicked();
    void timer();
signals:
    void log_out();
    void return_to_main();

private:
    Ui::withdraw_done *ui;
    QTimer *p_timer;
    int time = 10;
};

#endif  // WITHDRAW_DONE_H
