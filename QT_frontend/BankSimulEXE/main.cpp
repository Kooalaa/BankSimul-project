#include <QApplication>

#include "start_window.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    start_window w;
    w.show();
    return a.exec();
}
