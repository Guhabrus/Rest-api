#include "web_server.h"



int HTTP_best_Server::main([[maybe_unused]] const std::vector<std::string> &argv)
{
    if(!prvt_helpRequest)
        {

            unsigned short port = (unsigned short)config().getInt("HHTPBestServer.port", 8080);

            std::string format_url = config().getString("HHTPBestServer.format",
                                                    Poco::DateTimeFormat::SORTABLE_FORMAT);

            Poco::Net::ServerSocket stng_srv(Poco::Net::SocketAddress("0.0.0.0", port));

            Poco::Net::HTTPServer serv(new HTTPbestHandFact(format_url), 
                                                    stng_srv, new Poco::Net::HTTPServerParams);


            serv.start();

            std::cout<<"Server start listenning port:"<<port<<std::endl;
            

            waitForTerminationRequest();
        }

        return Application::EXIT_OK ;
}