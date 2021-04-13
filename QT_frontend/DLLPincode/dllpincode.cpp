#include "dllpincode.h"

DLLPincode::DLLPincode() {}

DLLPincode::~DLLPincode() {
    delete pdialog;
    pdialog = nullptr;
}

void DLLPincode::Main() {
    pdialog = new Dialog();
    pdialog->exec();
    PIN = pdialog->store_PIN();
}
