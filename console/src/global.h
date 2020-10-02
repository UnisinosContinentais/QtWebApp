/**
  @file
  @author Stefan Frings
*/

#ifndef GLOBAL_H
#define GLOBAL_H

#include <templateengine/templatecache.h>
#include <httpserver/httpsessionstore.h>
#include <httpserver/staticfilecontroller.h>
#include <logging/filelogger.h>

using namespace stefanfrings;

/**
  Global objects that are shared by multiple source files
  of this project.
*/

/** Cache for template files */
extern TemplateCache* templateCache;

/** Storage for session cookies */
extern  HttpSessionStore* sessionStore;

/** Controller for static files */
extern  StaticFileController* staticFileController;

/** Redirects log messages to a file */
extern  FileLogger* logger;

#endif // GLOBAL_H
