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

private:
    Dialog *pdialog;
};

#endif  // DLLPINCODE_H
