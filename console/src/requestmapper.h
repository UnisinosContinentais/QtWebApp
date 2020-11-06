/**
  @file
  @author Stefan Frings
*/

#ifndef STEFANFRINGS_REQUESTMAPPER_H
#define STEFANFRINGS_REQUESTMAPPER_H

#include <httpserver/httprequesthandler.h>

/**
  The request mapper dispatches incoming HTTP requests to controller classes
  depending on the requested path.
*/

class RequestMapper : public stefanfrings::HttpRequestHandler {
    Q_OBJECT
public:

    /**
      Constructor.
      @param parent Parent object
    */
    RequestMapper(QObject* parent=0);

    /**
      Destructor.
    */
    ~RequestMapper();

    /**
      Dispatch incoming HTTP requests to different controllers depending on the URL.
      @param request The received HTTP request
      @param response Must be used to return the response
    */
    void service(stefanfrings::HttpRequest& request, stefanfrings::HttpResponse& response);

};

#endif // STEFANFRINGS_REQUESTMAPPER_H
