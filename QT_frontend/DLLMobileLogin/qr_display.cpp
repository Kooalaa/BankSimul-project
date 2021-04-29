#include "qr_display.h"

#include <QDebug>

#include "ui_qr_display.h"

QR_display::QR_display(QWidget *parent) : QDialog(parent), ui(new Ui::QR_display) {
    ui->setupUi(this);

    scene = new QGraphicsScene;
    svg_reader = new QXmlStreamReader;
    renderer = new QSvgRenderer;
    svg_item = new QGraphicsSvgItem;

    qrcodegen::QrCode qrcode =
        qrcodegen::QrCode::encodeText("Initialization sample", qrcodegen::QrCode::Ecc::MEDIUM);

    svg_reader->clear();
    QString svg = QString::fromStdString(qrcode.toSvgString(1));
    svg_reader->addData(svg);
    renderer->load(svg_reader);

    svg_item->setSharedRenderer(renderer);

    scene->addItem(svg_item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

QR_display::~QR_display() {
    delete ui;
    delete scene;
    delete svg_reader;
    delete renderer;
    delete svg_item;
}

void QR_display::start(QString token) {
    this->show();
    qrcodegen::QrCode qrcode =
        qrcodegen::QrCode::encodeText(token.toStdString().c_str(), qrcodegen::QrCode::Ecc::MEDIUM);

    svg_reader->clear();
    QString svg = QString::fromStdString(qrcode.toSvgString(1));
    svg_reader->addData(svg);
    renderer->load(svg_reader);

    svg_item->setSharedRenderer(renderer);
    ui->label->setText(token);

    ui->graphicsView->fitInView(svg_item, Qt::KeepAspectRatio);
}
