#ifndef HTTPREQUESTFACTORY_H
#define HTTPREQUESTFACTORY_H


#include "Poco/Util/ServerApplication.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerRequest.h"

#include "Poco/Net/HTTPServerParams.h"

#include "Poco/Util/OptionSet.h"

#include "Poco/Net/HTTPRequestHandler.h"

#include <iostream>
#include <string>


#include "../Some_handlers/MyHendlers.h"
#include "../debug/debug.h"

#define IP "0.0.0.0"



/**
 * @brief Класс описывающий сервес
 */
class HTTP_best_Server : public Poco::Util::ServerApplication
{
    public:
        HTTP_best_Server(): prvt_helpRequest(false) {}
        
        ~HTTP_best_Server(){}

    private:

        void initialize(Application &self)
        {
            loadConfiguration();
            ServerApplication::initialize(self);
        }


        void uninitialize()
        {
            ServerApplication::uninitialize();
        }

        void defineOptions(Poco::Util::OptionSet &options)
        {
            ServerApplication::defineOptions(options);
        }



    /**
     * @brief Основная функция работы сервера 
     * Реализуется соединение, ответ клиенту и прием данных
     * @return int  - Код ошибки в случае какой либо оказии (критично)
     */
    int main([[maybe_unused]] const std::vector<std::string> &argv);             ///< приписываем магический maybe_unused без которого ничего не работает



    bool prvt_helpRequest;                  ///< Какая то магическая переменная

};






#endif





