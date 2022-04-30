#include "Poco/Thread.h"
#include "Poco/Runnable.h"

#include "config/config.h"
#include "Server/web_server.h"

int main(int argc, char *argv[])
{
    
    // Config settng(argc, argv);
    HTTP_best_Server test;
    
    std::cout<<" Hello i am server"<<std::endl;
    
    return test.run(argc, argv);
}