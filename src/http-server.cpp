#include <iostream>
#include <string>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/ServerApplication.h>

using namespace Poco::Net;
using namespace Poco::Util;

class MyRequestHandler : public HTTPRequestHandler
{
public:
    void handleRequest(HTTPServerRequest &request, HTTPServerResponse &response)
    {
        response.setStatus(HTTPServerResponse::HTTP_OK);
        response.setContentType("text/html");
        response.send() << "<html><body><h1>Hello, world!</h1></body></html>";
    }
};

class MyRequestHandlerFactory : public HTTPRequestHandlerFactory
{
public:
    HTTPRequestHandler *createRequestHandler(const HTTPServerRequest &request)
    {
        return new MyRequestHandler;
    }
};

class MyHTTPServerApp : public ServerApplication
{
protected:
    int main(const ArgVec &args)
    {
        // Create the server socket
        ServerSocket serverSocket(8000);

        // Create the HTTP server
        HTTPServerParams *pParams = new HTTPServerParams;
        pParams->setMaxQueued(100);
        pParams->setMaxThreads(16);
        HTTPServer server(new MyRequestHandlerFactory, serverSocket, pParams);

        // Start the server
        server.start();
        std::cout << "Server started on port 8000." << std::endl;

        // Wait for termination request
        waitForTerminationRequest();

        // Stop the server
        server.stop();
        return Application::EXIT_OK;
    }
};

int main(int argc, char **argv)
{
    MyHTTPServerApp app;
    return app.run(argc, argv);
}
