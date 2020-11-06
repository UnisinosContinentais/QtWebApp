/**
  @file
  @author Stefan Frings
*/

#include <QCoreApplication>
#include <QDir>
#include "global.h"
#include <httpserver/httplistener.h>
#include <httpserver/httpsessionstore.h>
#include <httpserver/staticfilecontroller.h>
#include <logging/filelogger.h>
#include <templateengine/templatecache.h>
#include "requestmapper.h"

using namespace stefanfrings;

/** Search the configuration file */
QString searchConfigFile()
{
    QString binDir=QCoreApplication::applicationDirPath();
    QString appName=QCoreApplication::applicationName();
    QString fileName(appName+".ini");

    QStringList searchList;
    searchList.append("C:/Git/QtWebApp/QtWebApp/console/etc"); // for development with shadow build
    searchList.append(QDir::rootPath()+"etc/opt");
    searchList.append(QDir::rootPath()+"etc");

    Q_FOREACH (QString dir, searchList)
    {
        QFile file(dir+"/"+fileName);
        if (file.exists())
        {
            // found
            fileName=QDir(file.fileName()).canonicalPath();
            qDebug("Using config file %s",qPrintable(fileName));
            return fileName;
        }
    }

    // not found
    Q_FOREACH (QString dir, searchList)
    {
        qWarning("%s/%s not found",qPrintable(dir),qPrintable(fileName));
    }
    qFatal("Cannot find config file %s",qPrintable(fileName));

    return "";
}


/**
  Entry point of the program.
*/
int main(int argc, char *argv[])
{
    QCoreApplication app(argc,argv);

    app.setApplicationName("Demo1");
    app.setOrganizationName("Butterfly");

    // Find the configuration file
    QString configFileName=searchConfigFile();

    // Configure logging into a file
    QSettings* logSettings=new QSettings(configFileName,QSettings::IniFormat);
    logSettings->beginGroup("logging");
    FileLogger* logger=new FileLogger(logSettings,10000);
    logger->installMsgHandler();

    // Configure template loader and cache
    QSettings* templateSettings=new QSettings(configFileName,QSettings::IniFormat);
    templateSettings->beginGroup("templates");
    templateCache=new TemplateCache(templateSettings);

    // Configure session store
    QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat);
    sessionSettings->beginGroup("sessions");
    sessionStore=new HttpSessionStore(sessionSettings);

    // Configure static file controller
    QSettings* fileSettings=new QSettings(configFileName,QSettings::IniFormat);
    fileSettings->beginGroup("docroot");
    staticFileController=new StaticFileController(fileSettings);

    // Configure and start the TCP listener
    QSettings* listenerSettings=new QSettings(configFileName,QSettings::IniFormat);
    listenerSettings->beginGroup("listener");
    new HttpListener(listenerSettings,new RequestMapper());

    qInfo("Application has started");
    app.exec();
    qInfo("Application has stopped");
}
