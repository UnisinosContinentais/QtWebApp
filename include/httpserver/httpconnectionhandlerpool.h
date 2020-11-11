#ifndef STEFANFRINGS_HTTPCONNECTIONHANDLERPOOL_H
#define STEFANFRINGS_HTTPCONNECTIONHANDLERPOOL_H

#include <QList>
#include <QTimer>
#include <QObject>
#include <QMutex>
#include "httpconnectionhandler.h"
#include "export.h"

namespace stefanfrings {

class QTWEBAPP_EXPORT_DECL HttpConnectionHandlerPool : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(HttpConnectionHandlerPool)
public:
    HttpConnectionHandlerPool(const QSettings* settings, HttpRequestHandler *requestHandler);

    /** Destructor */
    virtual ~HttpConnectionHandlerPool();

    /** Get a free connection handler, or 0 if not available. */
    HttpConnectionHandler* getConnectionHandler();

private:

    /** Settings for this pool */
    const QSettings* settings;

    /** Will be assigned to each Connectionhandler during their creation */
    HttpRequestHandler* requestHandler;

    /** Pool of connection handlers */
    QList<HttpConnectionHandler*> pool;

    /** Timer to clean-up unused connection handler */
    QTimer cleanupTimer;

    /** Used to synchronize threads */
    QMutex mutex;


    /** Load SSL configuration */
    void loadSslConfig();

private Q_SLOTS:

    /** Received from the clean-up timer.  */
    void cleanup();

};

} // end of namespace

#endif // STEFANFRINGS_HTTPCONNECTIONHANDLERPOOL_H
