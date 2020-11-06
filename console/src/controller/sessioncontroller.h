/**
  @file
  @author Stefan Frings
*/

#ifndef STEFANFRINGS_SESSIONCONTROLLER_H
#define STEFANFRINGS_SESSIONCONTROLLER_H

#include <httpserver/httprequest.h>
#include <httpserver/httpresponse.h>
#include <httpserver/httprequesthandler.h>

/**
  This controller demonstrates how to use sessions.
*/

class SessionController : public stefanfrings::HttpRequestHandler {
    Q_OBJECT
public:

    /** Constructor */
    SessionController();

    /** Generates the response */
    void service(stefanfrings::HttpRequest& request, stefanfrings::HttpResponse& response);
};

#endif // STEFANFRINGS_SESSIONCONTROLLER_H
