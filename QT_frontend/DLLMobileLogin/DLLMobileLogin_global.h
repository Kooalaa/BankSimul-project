#ifndef DLLMOBILELOGIN_GLOBAL_H
#define DLLMOBILELOGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLLMOBILELOGIN_LIBRARY)
#  define DLLMOBILELOGIN_EXPORT Q_DECL_EXPORT
#else
#  define DLLMOBILELOGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // DLLMOBILELOGIN_GLOBAL_H