/**
  @file
  @author Stefan Frings
*/

#ifndef STEFANFRINGS_DUMPCONTROLLER_H
#define STEFANFRINGS_DUMPCONTROLLER_H

#include <httpserver/httprequest.h>
#include <httpserver/httpresponse.h>
#include <httpserver/httprequesthandler.h>

/**
  This controller dumps the received HTTP request in the response.
*/

class DumpController : public stefanfrings::HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(DumpController)
public:

    /** Constructor */
    DumpController();

    /** Generates the response */
    void service(stefanfrings::HttpRequest& request, stefanfrings::HttpResponse& response);
};

#endif // STEFANFRINGS_DUMPCONTROLLER_H
