#ifndef QTWEBAPP_EXPORT_H
#define QTWEBAPP_EXPORT_H

#include <QtCore/QtGlobal>

#if defined(MAKE_QTWEBAPP_LIB)
#  define QTWEBAPP_EXPORT_DECL Q_DECL_EXPORT
#else
#  define QTWEBAPP_EXPORT_DECL Q_DECL_IMPORT
#endif

#endif // QTWEBAPP_EXPORT_H


