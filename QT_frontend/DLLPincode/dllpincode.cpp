#include "dllpincode.h"

DLLPincode::DLLPincode(QObject *parent) : QObject(parent) {
    perror_dialog = new Error_dialog();
    pdialog = new Dialog();
    connect(pdialog, SIGNAL(send_pin(QByteArray)), this, SLOT(get_pin(QByteArray)));
}

DLLPincode::~DLLPincode() {
    delete pdialog;

    pdialog = nullptr;
}

void DLLPincode::Main() { pdialog->show(); }

void DLLPincode::Wrong_PIN(int attempts) { perror_dialog->show_error(attempts); }

void DLLPincode::Locked_card() { perror_dialog->show_locked_card(); }

void DLLPincode::Logged_in() { pdialog->close(); }

void DLLPincode::get_pin(QByteArray PIN) { emit send_pin(PIN); }
