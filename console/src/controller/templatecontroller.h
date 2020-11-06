/**
  @file
  @author Stefan Frings
*/

#ifndef STEFANFRINGS_TEMPLATECONTROLLER_H
#define STEFANFRINGS_TEMPLATECONTROLLER_H

#include <httpserver/httprequest.h>
#include <httpserver/httpresponse.h>
#include <httpserver/httprequesthandler.h>

/**
  This controller generates a website using the template engine.
  It generates a Latin1 (ISO-8859-1) encoded website from a UTF-8 encoded template file.
*/

class TemplateController : public stefanfrings::HttpRequestHandler {
    Q_OBJECT
public:

    /** Constructor */
    TemplateController();

    /** Generates the response */
    void service(stefanfrings::HttpRequest& request, stefanfrings::HttpResponse& response);
};

#endif // STEFANFRINGS_TEMPLATECONTROLLER_H
