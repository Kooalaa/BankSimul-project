#ifndef QR_MOBILE_TOKEN_H
#define QR_MOBILE_TOKEN_H

#include <QDialog>
#include <QGraphicsSvgItem>
#include <QString>
#include <QSvgRenderer>
#include <QTimer>

#include "QR-Code-generator/cpp/QrCode.hpp"

namespace Ui {
class qr_mobile_token;
}

class QR_mobile_token : public QDialog {
    Q_OBJECT

public:
    explicit QR_mobile_token(QWidget *parent = nullptr);
    ~QR_mobile_token();
    void start(QString token);

private:
    Ui::qr_mobile_token *ui;
    QGraphicsScene *p_scene;
    QXmlStreamReader *p_svg_reader;
    QSvgRenderer *p_renderer;
    QGraphicsSvgItem *p_svg_item;
    QTimer *p_timer;
    int time;

signals:
    void request_new_token();

private slots:
    void on_generate_btn_clicked();
    void on_close_btn_clicked();
};

#endif  // QR_MOBILE_TOKEN_H
