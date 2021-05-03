#include "qr_mobile_token.h"

#include "ui_qr_mobile_token.h"

QR_mobile_token::QR_mobile_token(QWidget *parent) : QDialog(parent), ui(new Ui::qr_mobile_token) {
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
            time = 10;
            this->on_close_btn_clicked();
        }
    });
}

QR_mobile_token::~QR_mobile_token() {
    delete ui;
    delete p_scene;
    delete p_renderer;
    delete p_svg_reader;
}

void QR_mobile_token::start(QString token) {
    this->show();
    p_timer->start(1000);
    time = 10;
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

void QR_mobile_token::on_generate_btn_clicked() { emit request_new_token(); }

void QR_mobile_token::on_close_btn_clicked() {
    p_timer->stop();
    this->close();
}
