#ifndef START_WINDOW_H
#define START_WINDOW_H

#include <QDebug>
#include <QMainWindow>

#include "dllpincode.h"
#include "main_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class start_window;
}
QT_END_NAMESPACE

class start_window : public QMainWindow {
    Q_OBJECT

public:
    start_window(QWidget *parent = nullptr);
    ~start_window();
signals:
    void insert_card();
private slots:
    void card_inserted();

private:
    Ui::start_window *ui;
    DLLPincode *ppincode;
    Main_window *pmain_window;
};
#endif  // START_WINDOW_H
