/**
  @file
  @author Stefan Frings
*/

#ifndef STEFANFRINGS_GLOBAL_H
#define STEFANFRINGS_GLOBAL_H

#include <templateengine/templatecache.h>
#include <httpserver/httpsessionstore.h>
#include <httpserver/staticfilecontroller.h>
#include <logging/filelogger.h>

/**
  Global objects that are shared by multiple source files
  of this project.
*/

/** Cache for template files */
extern stefanfrings::TemplateCache* templateCache;

/** Storage for session cookies */
extern stefanfrings::HttpSessionStore* sessionStore;

/** Controller for static files */
extern stefanfrings::StaticFileController* staticFileController;

/** Redirects log messages to a file */
extern stefanfrings::FileLogger* logger;

#endif // STEFANFRINGS_GLOBAL_H
