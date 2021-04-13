#ifndef DLL_REST_API_H
#define DLL_REST_API_H

#include <QCryptographicHash>

#include "DLLRestAPI_global.h"
#include "engine_class.h"

class DLLRESTAPI_EXPORT dll_rest_api {
public:
    dll_rest_api();
    void login(QByteArray hash, int card_num);

private:
    engine_class *p_engine;
    ids_t *p_ids;
};

#endif  // DLL_REST_API_H
