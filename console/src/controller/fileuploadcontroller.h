/**
  @file
  @author Stefan Frings
*/

#ifndef STEFANFRINGS_FILEUPLOADCONTROLLER_H
#define STEFANFRINGS_FILEUPLOADCONTROLLER_H

#include <httpserver/httprequest.h>
#include <httpserver/httpresponse.h>
#include <httpserver/httprequesthandler.h>

/**
  This controller displays a HTML form for file upload and recieved the file.
*/


class FileUploadController : public stefanfrings::HttpRequestHandler {
    Q_OBJECT
public:

    /** Constructor */
    FileUploadController();

    /** Generates the response */
    void service(stefanfrings::HttpRequest& request, stefanfrings::HttpResponse& response);
};

#endif // STEFANFRINGS_FILEUPLOADCONTROLLER_H
