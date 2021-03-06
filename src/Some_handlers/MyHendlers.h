#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/JSON/Stringifier.h"

#include <iostream>

#include "../Database/Person/person.h"
#include "../debug/debug.h"

enum Metod
{
    GET,
    POST,
    UNKNOWN
};

/**
 * @brief Класс обработчик запросов
 */
class RequestHendler:public Poco::Net::HTTPRequestHandler
{
    public:
        RequestHendler(const std::string &html_requestt): prvt_html_requestt(html_requestt){}
    

        /**
         * @brief Переопределенная фунция обработки запросов
         * 
         * @param req --> запрос сервера
         * @param resp --> ответ сервера
         */
        virtual void handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp);

        /**
         * @brief функция получения класса метода
         * @param metod_s
         * @return Metod тип метода запроса
         */
        Metod classMetod(const  std::string metod_s);

    private:
        
        std::string prvt_html_requestt;


       
};


class HTTPbestHandFact: public Poco::Net::HTTPRequestHandlerFactory
{
    public:
    HTTPbestHandFact(const std::string &html_requestt): prvt_html_requestt(html_requestt)
    {}

    Poco::Net::HTTPRequestHandler* createRequestHandler([[maybe_unused]]const Poco::Net::HTTPServerRequest& request)
    {
        if("/person"==request.getURI())
        {
            print_debug("----/person\n");
            return new RequestHendler(prvt_html_requestt);
        }
        else 
            return new RequestHendler(prvt_html_requestt);
    }
    

    private:

    std::string prvt_html_requestt;
};





