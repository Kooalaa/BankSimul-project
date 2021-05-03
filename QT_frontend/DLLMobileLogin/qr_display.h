#ifndef QR_DISPLAY_H
#define QR_DISPLAY_H

#include <QDialog>
#include <QGraphicsSvgItem>
#include <QString>
#include <QSvgRenderer>
#include <QTimer>

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
    void stop();

private:
    Ui::QR_display *ui;
    QGraphicsScene *p_scene;
    QSvgRenderer *p_renderer;
    QXmlStreamReader *p_svg_reader;
    QGraphicsSvgItem *p_svg_item;
    QTimer *p_timer;
    int time;

signals:
    void cancel_login();

private slots:
    void on_cancel_btn_clicked();
};

#endif  // QR_DISPLAY_H
