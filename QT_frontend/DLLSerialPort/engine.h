#ifndef ENGINE_H
#define ENGINE_H

#include <QDebug>
#include <QList>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class Engine : public QObject {
    Q_OBJECT
public:
    Engine(QObject* parent = nullptr);
    ~Engine();
    void read_RFID_tag();

public slots:
    void received_signal();

private:
    QSerialPort* p_serial_port;

signals:
    void send_num(QString card_num);
};

#endif  // ENGINE_H
