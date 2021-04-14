#ifndef START_WINDOW_H
#define START_WINDOW_H

#include <QDebug>
#include <QMainWindow>

#include "dllpincode.h"
#include "main_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Start_window;
}
QT_END_NAMESPACE

class Start_window : public QMainWindow {
    Q_OBJECT

public:
    Start_window(QWidget *parent = nullptr);
    ~Start_window();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Start_window *ui;
    DLLPincode *ppincode;
    Main_window *pmain_window;
};
#endif  // START_WINDOW_H
