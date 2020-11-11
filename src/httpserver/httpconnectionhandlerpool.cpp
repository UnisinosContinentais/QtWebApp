#ifndef QT_NO_SSL
    #include <QSslSocket>
    #include <QSslKey>
    #include <QSslCertificate>
    #include <QSslConfiguration>
#endif
#include <QDir>
#include <QString>
#include <QSslCertificate>
#include <QFile>
#include <QFileInfo>

#include "httpserver/httpconnectionhandler.h"
#include "httpserver/httpconnectionhandlerpool.h"

using namespace stefanfrings;

HttpConnectionHandlerPool::HttpConnectionHandlerPool(const QSettings *settings, HttpRequestHandler *requestHandler)
    : QObject()
{
    Q_ASSERT(settings!=0);
    this->settings=settings;
    this->requestHandler=requestHandler;
    //this->sslConfiguration=NULL;
    //loadSslConfig();
    cleanupTimer.start(settings->value("cleanupInterval",1000).toInt());
    connect(&cleanupTimer, SIGNAL(timeout()), SLOT(cleanup()));
}


HttpConnectionHandlerPool::~HttpConnectionHandlerPool()
{
    // delete all connection handlers and wait until their threads are closed
    foreach(HttpConnectionHandler* handler, pool)
    {
       delete handler;
    }
    //delete sslConfiguration;
    qDebug("HttpConnectionHandlerPool (%p): destroyed", this);
}


HttpConnectionHandler* HttpConnectionHandlerPool::getConnectionHandler()
{
    HttpConnectionHandler* freeHandler=0;
    mutex.lock();
    // find a free handler in pool
    foreach(HttpConnectionHandler* handler, pool)
    {
        if (!handler->isBusy())
        {
            freeHandler=handler;
            freeHandler->setBusy();
            break;
        }
    }
    // create a new handler, if necessary
    if (!freeHandler)
    {
        int maxConnectionHandlers=settings->value("maxThreads",100).toInt();
        if (pool.count()<maxConnectionHandlers)
        {
            freeHandler=new HttpConnectionHandler(settings,requestHandler);
            freeHandler->setBusy();
            pool.append(freeHandler);
        }
    }
    mutex.unlock();
    return freeHandler;
}


void HttpConnectionHandlerPool::cleanup()
{
    int maxIdleHandlers=settings->value("minThreads",1).toInt();
    int idleCounter=0;
    mutex.lock();
    foreach(HttpConnectionHandler* handler, pool)
    {
        if (!handler->isBusy())
        {
            if (++idleCounter > maxIdleHandlers)
            {
                delete handler;
                pool.removeOne(handler);
                qDebug("HttpConnectionHandlerPool: Removed connection handler (%p), pool size is now %i",handler,pool.size());
                break; // remove only one handler in each interval
            }
        }
    }
    mutex.unlock();
}


void HttpConnectionHandlerPool::loadSslConfig()
{

}
