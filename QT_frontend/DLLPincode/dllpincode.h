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
    void Main();

signals:
    void send_pin(QByteArray);

public slots:
    void Wrong_PIN(int attempts);
    void Locked_card();
    void Logged_in();
    void get_pin(QByteArray);

private:
    Dialog *pdialog;
    Error_dialog *perror_dialog;
};

#endif  // DLLPINCODE_H
