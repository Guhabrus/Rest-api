#include "MyHendlers.h"





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
                
                if(html_request.has(LAST_NAME))
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
                            

                        if(database::Result::SUCCES != man.set_last_name(html_request.get(LAST_NAME)))
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
                        man.set_last_name(html_request.get(LAST_NAME));
                        man.set_age(std::stoi(html_request.get(AGE_PERSON)));

                        print_debug(" login =%s  first_name = %sm last_name = %s, age = %d\n",man.get_login().c_str(),man.get_first_name().c_str(),man.get_last_name().c_str(),man.get_age());
                        
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
        print_debug("мы в search - ищем всех по имени и фамилии \n");
        if(html_request.has(FIRST_NAME))
        {
            if(html_request.has(LAST_NAME))
            {
                try
                {
                    std::string first_name_request = html_request.get(FIRST_NAME);
                    std::string last_name_request = html_request.get(LAST_NAME);
                    Poco::JSON::Array json_client_list;

                    print_debug("first_name request = %s\n",first_name_request.c_str());
                    print_debug("second_name request = %s\n",last_name_request.c_str());

                    std::vector<database::Person> *list_clients  = new std::vector<database::Person>;

                    if(database::Person::find_by_first_and_last_name(first_name_request, last_name_request, list_clients))
                    {
                        out<<"<h1> Упс что то пошло не так при поиске <h1>";
                    }

                    if(list_clients->empty()) out<<" <h1> Ничего не удалось найти <h1>";

                    while (!list_clients->empty())
                    {
                        json_client_list.add(list_clients->back().converte_to_json());
                        list_clients->pop_back();
                        print_debug("1.\n");
                    }
                    Poco::JSON::Stringifier::stringify(json_client_list, out);
                    delete list_clients;
                }
                catch(...)
                {
                    
                    out<<"<h1> Do not find ((((( <h1>";    
                }
            }
            else
            {
                out<<"<h1> Товарищ, вы забыли ввести фамилию   <h1>";
            }
        }
        else
        {
            out<<"<h1> Товарищ, вы забыли ввести имя   <h1>";
        }
        
        
    }
    else if(html_request.has("login"))              
    {

        print_debug("Ищем человек по логину \n");
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

    out.flush();
    print_debug("Response sent for URL = %s",req.getURI().c_str());
    
    
}