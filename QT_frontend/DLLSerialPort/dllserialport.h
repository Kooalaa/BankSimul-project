#ifndef DLLSERIALPORT_H
#define DLLSERIALPORT_H

#include <QObject>

#include "DLLSerialPort_global.h"
#include "engine.h"

class DLLSERIALPORT_EXPORT DLLSerialPort : public QObject {
    Q_OBJECT;

public:
    DLLSerialPort(QObject *parent = nullptr);
    ~DLLSerialPort();
    void read_card();
    void readPortInfo();

private:
    Engine *engine;

signals:
    void card_read(QString card_num);

private slots:
    void received_card_num(QString card_num);
};

#endif  // DLLSERIALPORT_H
