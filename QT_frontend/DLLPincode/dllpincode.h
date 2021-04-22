#ifndef DLLPINCODE_H
#define DLLPINCODE_H

#include <QObject>

#include "DLLPincode_global.h"
#include "dialog.h"
#include "error_dialog.h"

class DLLPINCODE_EXPORT DLLPincode : public QObject {
    Q_OBJECT
public:
    DLLPincode(QObject *parent = nullptr);
    ~DLLPincode();
    void Main(bool);

signals:
    void send_pin(QByteArray);

public slots:
    void Wrong_PIN(int attempts);
    void Locked_card();
    void Logged_in();
    void get_pin(QByteArray);

private:
    Dialog *p_dialog;
    Error_dialog *p_error_dialog;
};

#endif  // DLLPINCODE_H
