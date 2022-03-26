#include "MyHendlers.h"



#define LOGIN           "login"
#define FIRST_NAME      "first_name"
#define SECOND_NAME     "second_name"
#define AGE_PERSON      "age"

void RequestHendler::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
    Poco::Net::HTMLForm html_request(req, req.stream());

    resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

    resp.setChunkedTransferEncoding(true);

    resp.setContentType("application/json");

    std::ostream& out = resp.send();

    if(html_request.has("add"))
    {
        
        if(html_request.has(LOGIN))
        {
            
            if(html_request.has(FIRST_NAME))
            {
                
                if(html_request.has(SECOND_NAME))
                {
                    
                    if(html_request.has(AGE_PERSON))
                    {
                        database::Person man;
                        if(database::Result::SUCCES != man.set_login(html_request.get(LOGIN)))                          //TODO  сделать вывод конкретной ошибки из enum
                        {
                            out<<"<h1> Wrong login <h1>";                                   
                            return;
                        }
                            

                        if(database::Result::SUCCES != man.set_first_name(html_request.get(FIRST_NAME)))
                        {
                            out<<"<h1> Wrong first name <h1>";                                   
                            return;
                        }
                            

                        if(database::Result::SUCCES != man.set_second_name(html_request.get(SECOND_NAME)))
                        {
                            out<<"<h1> Wrong second name <h1>";                                   
                            return;
                        }
                            

                        if(database::Result::SUCCES != man.set_age(std::stoi(html_request.get(AGE_PERSON))))
                        {
                            out<<"<h1> Wrong age <h1>";                                   
                            return;
                        }
                            
                         
                        man.set_login(html_request.get(LOGIN));
                        man.set_first_name(html_request.get(FIRST_NAME)); 
                        man.set_second_name(html_request.get(SECOND_NAME));
                        man.set_age(std::stoi(html_request.get(AGE_PERSON)));

                        print_debug(" login =%s  first_name = %sm second_name = %s, age = %d\n",man.get_login().c_str(),man.get_first_name().c_str(),man.get_second_name().c_str(),man.get_age());
                        
                        uint8_t retcode =  man.save_to_database();
                        
                        if(!retcode)
                        {
                            out<<"<h1> SUCCES <h1>";
                        }
                        else 
                            out<<"<h1> error -  <h1>"<<retcode;

                        print_debug("Succes\n");
                    }
                }
            }
        }
    }
    else if(html_request.has("search"))
    {
        print_debug("мы в search \n");
        try
        {
            std::string login_request = html_request.get(LOGIN);

            print_debug("login request = %s",login_request.c_str());

            database::Person man = database::Person::find_by_login(login_request);

            Poco::JSON::Stringifier::stringify(man.converte_to_json(),out);
        }
        catch(...)
        {
            
            out<<"<h1> Do not find ((((( <h1>";    
        }
        

        
    }
    else if(html_request.has("login"))
    {
        std::vector<database::Person> *clients_list = new std::vector<database::Person>;

        database::Person::get_all_database(clients_list);

        Poco::JSON::Array json_client_list;

        while(!clients_list->empty())
        {
            json_client_list.add(clients_list->back().converte_to_json());

            clients_list->pop_back();
        }
        

        Poco::JSON::Stringifier::stringify(json_client_list, out);
        
        delete clients_list;

    }

    out.flush();
    print_debug("Response sent for URL = %s",req.getURI().c_str());
    
    
}