/**
  @file
  @author Stefan Frings
*/

#ifndef STEFANFRINGS_FORMCONTROLLER_H
#define STEFANFRINGS_FORMCONTROLLER_H

#include <httpserver/httprequest.h>
#include <httpserver/httpresponse.h>
#include <httpserver/httprequesthandler.h>

/**
  This controller displays a HTML form and dumps the submitted input.
*/


class FormController : public stefanfrings::HttpRequestHandler {
    Q_OBJECT
public:

    /** Constructor */
    FormController();

    /** Generates the response */
    void service(stefanfrings::HttpRequest& request, stefanfrings::HttpResponse& response);
};

#endif // STEFANFRINGS_FORMCONTROLLER_H
