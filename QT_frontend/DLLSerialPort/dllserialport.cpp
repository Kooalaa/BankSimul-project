#include "dllserialport.h"

DLLSerialPort::DLLSerialPort(QObject *parent) : QObject(parent) {
    engine = new Engine;
    connect(engine, &Engine::send_num, this, &DLLSerialPort::received_card_num);
}

DLLSerialPort::~DLLSerialPort() {
    delete engine;
    engine = nullptr;
}

void DLLSerialPort::read_card() { engine->read_RFID_tag(); }

void DLLSerialPort::received_card_num(QString card_num) { emit card_read(card_num); }
