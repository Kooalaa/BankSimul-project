#ifndef DLLPINCODE_H
#define DLLPINCODE_H

#include "DLLPincode_global.h"
#include "dialog.h"

class DLLPINCODE_EXPORT DLLPincode {
public:
    DLLPincode();
    ~DLLPincode();
    void Main();
    QByteArray PIN;

public slots:
    void Wrong_PIN(int attempts);
    void Locked_card();
    void Logged_in();

private:
    Dialog *pdialog;
};

#endif  // DLLPINCODE_H
