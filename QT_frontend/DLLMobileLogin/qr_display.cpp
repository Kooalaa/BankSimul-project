#include "qr_display.h"

#include "ui_qr_display.h"

QR_display::QR_display(QWidget *parent) : QDialog(parent), ui(new Ui::QR_display) {
    ui->setupUi(this);
    p_timer = new QTimer;

    p_scene = new QGraphicsScene;
    p_svg_reader = new QXmlStreamReader;
    p_renderer = new QSvgRenderer;
    p_svg_item = new QGraphicsSvgItem;

    p_scene->addItem(p_svg_item);
    ui->graphicsView->setScene(p_scene);
    ui->graphicsView->show();

    connect(p_timer, &QTimer::timeout, this, [this] {
        ui->time->setNum(--time);
        if (time == 0) {
            this->stop();
        }
    });
}

QR_display::~QR_display() {
    delete ui;
    delete p_scene;
    delete p_renderer;
    delete p_svg_reader;
}

void QR_display::start(QString token) {
    this->show();
    p_timer->start(1000);
    time = 15;
    ui->time->setNum(time);
    ui->token->setText(token);

    qrcodegen::QrCode qr_code =
        qrcodegen::QrCode::encodeText(token.toStdString().c_str(), qrcodegen::QrCode::Ecc::MEDIUM);

    p_svg_reader->clear();
    QString svg = QString::fromStdString(qr_code.toSvgString(1));
    p_svg_reader->addData(svg);
    p_renderer->load(p_svg_reader);

    p_svg_item->setSharedRenderer(p_renderer);
    ui->graphicsView->fitInView(p_svg_item, Qt::KeepAspectRatio);
}

void QR_display::stop() {
    p_timer->stop();
    this->close();
}

void QR_display::on_cancel_btn_clicked() {
    emit cancel_login();
    p_timer->stop();
    this->close();
}
