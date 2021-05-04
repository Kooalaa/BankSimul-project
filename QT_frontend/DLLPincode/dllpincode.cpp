
#include "dllpincode.h"

DLLPincode::DLLPincode(QObject *parent) : QObject(parent) {
    p_error_dialog = new Error_dialog();
    p_dialog = new Dialog();
    connect(p_dialog, SIGNAL(send_pin(QByteArray)), this, SLOT(get_pin(QByteArray)));
    connect(p_error_dialog, SIGNAL(log_out()), this, SLOT(log_out()));
}

// Deleting pointers and making them nullpointers
DLLPincode::~DLLPincode() {
    delete p_dialog;
    p_dialog = nullptr;
    delete p_error_dialog;
    p_error_dialog = nullptr;
}

// Starts the sequence needed for pincode input if locked is true, else shows locked_card error
void DLLPincode::Main(bool locked) {
    if (!locked) {
        p_dialog->show_with_timer();
    } else {
        p_error_dialog->show_locked_card();
    }
}

// Calls p_error_dialog to show wrongpin error with attempts left as parameter
void DLLPincode::Wrong_PIN(int attempts) {
    p_error_dialog->show_error(attempts);
    p_dialog->show_with_timer();
}

// Calls p_error_dialog to show locked_card error when wrong pincode is given 3 times
void DLLPincode::Locked_card() { p_error_dialog->show_locked_card(); }

// Closes dialog when correct pincode is given
void DLLPincode::Logged_in() { p_dialog->close(); }

// Emits signal containing inserted pincode
void DLLPincode::get_pin(QByteArray PIN) { emit send_pin(PIN); }

void DLLPincode::log_out() {
    p_dialog->close();
    emit locked();
}
