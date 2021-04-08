#include "dll_rest_api.h"

dll_rest_api::dll_rest_api() { p_engine = new engine_class; }

void dll_rest_api::login(int pin, int card_num) {
    QByteArray arr;
    arr.setNum(pin);
    QByteArray hash = QCryptographicHash::hash(arr, QCryptographicHash::Sha3_256);
    p_engine->login(hash, card_num);
}
