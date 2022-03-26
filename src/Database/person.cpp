#include "person.h"
#include "string.h"
#include "../debug/debug.h"
#include "Poco/Data/Statement.h"
#include "../config/config.h"



namespace database
{
    Poco::JSON::Object::Ptr Person::converte_to_json()
    {
        Poco::JSON::Object::Ptr json_objct = new Poco::JSON::Object();
        json_objct->set("login",this->login);
        json_objct->set("first name",this->first_name);
        json_objct->set("second name",this->second_name);
        json_objct->set("age",this->age);

        return json_objct;
    }

    Result Person::set_first_name(std::string first_name)
    {
        if(MAX_SIZE_STR < first_name.length())
            return TOO_LONG;

        else if(MIN_SIZE_STR > first_name.length())
            return TOO_SHORT;

        else if((first_name.find("@") != std::string::npos) || (first_name.find("!") != std::string::npos)  || \
            (first_name.find("#") != std::string::npos) || (first_name.find("%") != std::string::npos) ||       \
            (first_name.find("$") != std::string::npos))
            return INCORRECT;


        this->first_name = first_name;

        return SUCCES;
    }


    Result Person::set_second_name(std::string second_name)
    {
        if(MAX_SIZE_STR < second_name.length())
            return TOO_LONG;

        else if(MIN_SIZE_STR > second_name.length())
            return TOO_SHORT;

        else if((second_name.find("@") != std::string::npos) || (second_name.find("!") != std::string::npos)  || \
            (second_name.find("#") != std::string::npos) || (second_name.find("%") != std::string::npos) ||       \
            (second_name.find("$") != std::string::npos))
            return INCORRECT;

        this->second_name = second_name;

        return SUCCES;
    }

    Result Person::set_login(std::string login)
    {
        if(MAX_SIZE_STR < login.length())
            return TOO_LONG;

        else if(MIN_SIZE_STR > login.length() )
            return TOO_SHORT;

        else if((login.find("@") != std::string::npos) || (login.find("!") != std::string::npos)  || \
            (login.find("#") != std::string::npos) || (login.find("%") != std::string::npos) ||       \
            (login.find("$") != std::string::npos))
            return INCORRECT;

        this->login = login;

        return SUCCES;
    }


    Result Person::set_age(uint8_t age)
    {
        if(MAX_AGE < age)
            return TOO_LONG;

        else if(MIN_AGE > age)
            return TOO_SHORT;

        this->age = age;

        return SUCCES;
    }


   void Person::init_connetc_to_database()
    {
       try
       {
           Poco::Data::Session session = database::Database::get().create_session();

           Poco::Data::Statement drop_stat(session);
       }
       catch(Poco::Data::MySQL::ConnectionException &e)
       {
            std::cerr << e.what() << '\n';
            throw;
       }   
    }

    uint8_t Person::save_to_database()
    {
        

        try
        {
            print_debug("start connection\n");
            Poco::Data::Session session = database::Database::get().create_session();
            
            Poco::Data::Statement msg(session);

            print_debug("start writtin\n");

            msg<< "INSERT INTO " TABLE_NAME" (login, first_name, second_name, age) VALUES(?, ?, ?, ?)",    
            PUT_TO_DATABASE(login),
            PUT_TO_DATABASE(first_name),
            PUT_TO_DATABASE(second_name),
            PUT_TO_DATABASE(age);

            msg.execute();

            // Poco::Data::Statement select(session);
            return Result::SUCCES;
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw;
            return Result::UNKNOWN;
        }
        
    }


    Person Person::find_by_login(std::string login_f)
    {
        Person find_person;
        try
        {
            print_debug("start connection\n");
            Poco::Data::Session session = database::Database::get().create_session();
            
            Poco::Data::Statement msg(session);
            
            print_debug("start finding\n");
            
            msg<<"SELECT login, first_name, second_name, age FROM " TABLE_NAME " where login=?",
    
                GET_FROM_DATABASE(find_person.login),
                GET_FROM_DATABASE(find_person.first_name),
                GET_FROM_DATABASE(find_person.second_name),
                GET_FROM_DATABASE(find_person.age),
                PUT_TO_DATABASE(login_f);
                OPTION_RESEARCH(0,1);
            msg.execute();

            return find_person;
        }
        catch (...)
        {
            throw;
        }
        
        
        
    }





    void Person::get_all_database(std::vector<Person> *list_person)
    {


        try
        {
            print_debug("start connection\n");
            Poco::Data::Session session = database::Database::get().create_session();
            
            Poco::Data::Statement msg(session);
            
            Person tmp_man;

            print_debug("start finding\n");
            

            msg<<"SELECT login, first_name, second_name, age FROM " TABLE_NAME,
                GET_FROM_DATABASE(tmp_man.login),
                GET_FROM_DATABASE(tmp_man.first_name),
                GET_FROM_DATABASE(tmp_man.second_name),
                GET_FROM_DATABASE(tmp_man.age),
                OPTION_RESEARCH(0,1);
                
            while(!msg.done())
            {
                if(msg.execute())
                {
                    list_person->push_back(tmp_man);
                }
                
                    
            }
            print_debug("6\n");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw;
            return;
        }
        
        

        return;
    }







    Database::Database(){
        _connection_string+="host=localhost";
        
        _connection_string+=";user=";
        _connection_string+=SQL_USERNAME;
        
        _connection_string+=";db=";
        _connection_string+=BD_NAME;
        
        _connection_string+=";password=";
        _connection_string+=PASSWORD_SQL;
        
       
        Poco::Data::MySQL::Connector::registerConnector();
    }

    Database& Database::get(){
        
        static Database _instance;
        
        return _instance;
    }

    Poco::Data::Session Database::create_session(){
        
        return Poco::Data::Session(Poco::Data::SessionFactory::instance().create(Poco::Data::MySQL::Connector::KEY, _connection_string));
    }
}

