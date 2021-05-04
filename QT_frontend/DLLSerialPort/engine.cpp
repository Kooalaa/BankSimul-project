#include "engine.h"

Engine::Engine(QObject *parent) : QObject(parent) {
    p_serial_port = new QSerialPort;
    connect(p_serial_port, SIGNAL(readyRead()), this, SLOT(received_signal()));
}

Engine::~Engine() {
    delete p_serial_port;
    p_serial_port = nullptr;
}

void Engine::read_RFID_tag() {
    p_serial_port->setPortName("COM3");
    qDebug() << p_serial_port->portName();
    p_serial_port->setBaudRate(9600);
    p_serial_port->setDataBits(QSerialPort::Data8);
    p_serial_port->setParity(QSerialPort::NoParity);
    p_serial_port->setStopBits(QSerialPort::OneStop);
    p_serial_port->setFlowControl(QSerialPort::HardwareControl);

    if (!p_serial_port->open(QIODevice::ReadWrite)) {
        qDebug() << "Does not open" << Qt::endl;

    } else {
        qDebug() << "Port opened" << Qt::endl;
    }
}

void Engine::received_signal() {
    QString received = p_serial_port->readAll();
    qDebug() << received << Qt::endl;
    p_serial_port->close();
    qDebug() << "Close port in the end";
    emit send_num(received);
}
