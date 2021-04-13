#include "dll_rest_api.h"

dll_rest_api::dll_rest_api() { p_engine = new engine_class; }

void dll_rest_api::login(QByteArray hash, int card_num) {
    p_engine->login(hash, card_num);
}
