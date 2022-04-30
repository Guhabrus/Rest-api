#include "person.h"
#include "string.h"
#include "../debug/debug.h"
#include "Poco/Data/Statement.h"
#include "../config/config.h"

#include <cstdio>


namespace database
{
    Poco::JSON::Object::Ptr Person::converte_to_json()
    {
        Poco::JSON::Object::Ptr json_objct = new Poco::JSON::Object();
        json_objct->set("login",this->login);
        json_objct->set("first name",this->first_name);
        json_objct->set("last name",this->last_name);
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


    Result Person::set_last_name(std::string last_name)
    {
        if(MAX_SIZE_STR < last_name.length())
            return TOO_LONG;

        else if(MIN_SIZE_STR > last_name.length())
            return TOO_SHORT;

        else if((last_name.find("@") != std::string::npos) || (last_name.find("!") != std::string::npos)  || \
            (last_name.find("#") != std::string::npos) || (last_name.find("%") != std::string::npos) ||       \
            (last_name.find("$") != std::string::npos))
            return INCORRECT;

        this->last_name = last_name;

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
            
            std::string str_docker = "INSERT INTO " TABLE_NAME " ( " LOGIN " , " FIRST_NAME " , " LAST_NAME " , " AGE_PERSON " ) VALUES(?, ?, ?, ?)";
            

            str_docker += "-- sharding:" + Database::get_num_shard(login);
            

            print_debug("start writtin\n");

            msg<<str_docker,
            PUT_TO_DATABASE(login),
            PUT_TO_DATABASE(first_name),
            PUT_TO_DATABASE(last_name),
            PUT_TO_DATABASE(age);

            msg.execute();

            print_debug("1\n");
            return Result::SUCCES;
            
        }
        catch(const std::exception& e)
        {
            print_debug("2\n");
            std::cerr << e.what() << '\n';
            throw;
            
        }
        
    }


  


    Person Person::find_by_login(std::string login_f)
    {
        
        try
        {
            Person find_person;
            print_debug("start connection\n");
            Poco::Data::Session session = database::Database::get().create_session();
            
            Poco::Data::Statement msg(session);
            
            print_debug("start finding\n");
            
            std::string str_docker = "SELECT " LOGIN " , " FIRST_NAME " , " LAST_NAME " , " AGE_PERSON " FROM " TABLE_NAME " where " LOGIN "=?";

            str_docker+=str_docker += "-- sharding:" + Database::get_num_shard(login_f);


            msg<<str_docker,
                GET_FROM_DATABASE(find_person.login),
                GET_FROM_DATABASE(find_person.first_name),
                GET_FROM_DATABASE(find_person.last_name),
                GET_FROM_DATABASE(find_person.age),
                PUT_TO_DATABASE(login_f);
                OPTION_RESEARCH(0,1);
            msg.execute();

            return find_person;
        }
        catch (...)
        {
            print_debug("test test \n");
            throw;
        }
        
    }

    void Person::request_all(std::string first_name, std::string last_name, std::vector<Person> *list_clients, boost::mutex *mtx_list, std::string num_shard)
    {
        Person find_person;
            
        print_debug("start connection\n");
        Poco::Data::Session session = database::Database::get().create_session();
        
        Poco::Data::Statement msg(session);
        
        print_debug("start finding\n");

        std::string str_docker = "SELECT " LOGIN " , "  FIRST_NAME " , " LAST_NAME " , " AGE_PERSON " FROM " TABLE_NAME " where " FIRST_NAME " LIKE ? and " LAST_NAME " LIKE ?";
        
        str_docker += ("-- sharding:" + num_shard);

        msg<<str_docker,
    
            GET_FROM_DATABASE(find_person.login),
            GET_FROM_DATABASE(find_person.first_name),
            GET_FROM_DATABASE(find_person.last_name),
            GET_FROM_DATABASE(find_person.age),
            PUT_TO_DATABASE(first_name),
            PUT_TO_DATABASE(last_name),
            OPTION_RESEARCH(0,1);
        
        
        
        
        while (!msg.done())
        {
            if(msg.execute())
            {
                boost::lock_guard<boost::mutex> lock(*mtx_list);        list_clients->push_back(find_person);
            }
                
        }
    }

    uint8_t Person::get_all_prl(std::string first_name, std::string last_name, std::vector<Person> *list_clients)
    {
        try
        {
            boost::mutex mtx_list;
            

            std::vector<boost::thread> thread_list;
            for(size_t indx_shard = 0; indx_shard<TOTAL_SHARD; indx_shard++)
            {
                thread_list.push_back(boost::thread(request_all, first_name, last_name,list_clients,&mtx_list, std::to_string(indx_shard) ) );
            }
            

            for(size_t indx_shard = 0; indx_shard<TOTAL_SHARD; indx_shard++)
            {
                if(thread_list.back().joinable())
                {
                    thread_list.back().join();
                    thread_list.pop_back();
                }
                
            }
            print_debug(" Все ок, что то нашли \n");
            return 0;
            
        }
        catch(...)
        {
            print_debug("УПС что то пошло не так при поиcке ... \n");
            throw;
        }
        return 1;
        
    }





    void Person::get_all_prl_database(std::vector<Person> *list_person)
    {


        try
        {
            print_debug("start connection\n");
            Poco::Data::Session session = database::Database::get().create_session();
            
            Poco::Data::Statement msg(session);
            
            Person tmp_man;

            print_debug("start finding\n");
            

            msg<<"SELECT " LOGIN " , " FIRST_NAME " , " LAST_NAME " , " AGE_PERSON " FROM " TABLE_NAME,
                GET_FROM_DATABASE(tmp_man.login),
                GET_FROM_DATABASE(tmp_man.first_name),
                GET_FROM_DATABASE(tmp_man.last_name),
                GET_FROM_DATABASE(tmp_man.age),
                OPTION_RESEARCH(0,1);
                
            while(!msg.done())
            {
                if(msg.execute())
                {
                    list_person->push_back(tmp_man);
                }
                
                    
            }
       
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw;
            return;
        }
        
        

        return;
    }







    Database::Database()
    {
        // // srand(1);

        _connection_string+="host=";
        _connection_string+=HOST_IP ;

        _connection_string+=";port=";
        _connection_string+=PORT;

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




    num_shard Database::get_num_shard(std::string login)
    {
        
       return std::to_string(std::hash<std::string>{} (login) %TOTAL_SHARD); 
    }

}

