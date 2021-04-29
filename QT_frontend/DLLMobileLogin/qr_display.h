#ifndef QR_DISPLAY_H
#define QR_DISPLAY_H

#include <QDialog>
#include <QGraphicsSvgItem>
#include <QString>
#include <QSvgRenderer>

#include "QR-Code-generator/cpp/QrCode.hpp"

namespace Ui {
class QR_display;
}

class QR_display : public QDialog {
    Q_OBJECT

public:
    explicit QR_display(QWidget *parent = nullptr);
    ~QR_display();
    void start(QString token);

private:
    Ui::QR_display *ui;
    QGraphicsScene *scene;
    QSvgRenderer *renderer;
    QXmlStreamReader *svg_reader;
    QGraphicsSvgItem *svg_item;
};

#endif  // QR_DISPLAY_H
