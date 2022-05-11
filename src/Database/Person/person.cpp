#include "person.h"
#include "string.h"
#include "../../debug/debug.h"



#include "Poco/Data/Statement.h"
#include <ignite/thin/cache/cache_peek_mode.h>

#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <cppkafka/cppkafka.h>

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>



namespace database
{
    Poco::JSON::Object::Ptr Person::converte_to_json()
    {
        Poco::JSON::Object::Ptr json_objct = new Poco::JSON::Object();
        json_objct->set("login",this->login);
        json_objct->set("first_name",this->first_name);
        json_objct->set("last_name",this->last_name);
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

    bool Person::save_to_database()
    {
        

        try
        {
            print_debug("start connection\n");
            Poco::Data::Session session = database::Database::get().create_session();
            
            Poco::Data::Statement msg(session);

            print_debug("start writtin\n");

            msg<< "INSERT INTO " TABLE_NAME " ( " LOGIN " , " FIRST_NAME " , " LAST_NAME " , " AGE_PERSON " ) VALUES(?, ?, ?, ?)",    
            PUT_TO_DATABASE(login),
            PUT_TO_DATABASE(first_name),
            PUT_TO_DATABASE(last_name),
            PUT_TO_DATABASE(age);

            msg.execute();

            // Poco::Data::Statement select(session);
            return true;
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw;
            return false;
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
            
            msg<<"SELECT " LOGIN " , " FIRST_NAME " , " LAST_NAME " , " AGE_PERSON " FROM " TABLE_NAME " where " LOGIN "=?",
    
                GET_FROM_DATABASE(find_person.login),
                GET_FROM_DATABASE(find_person.first_name),
                GET_FROM_DATABASE(find_person.last_name),
                GET_FROM_DATABASE(find_person.age),
                PUT_TO_DATABASE(login_f);
                OPTION_RESEARCH(0,1);
                
            if(!msg.execute()){throw std::logic_error("Not found");};

            return find_person;
        }
        catch (...)
        {
            print_debug("test test \n");
            throw;
        }
        
    }

    uint8_t Person::find_person(std::string first_name, std::string last_name, std::vector<Person> *list_clients)
    {
        try
        {
            Person find_person;
            
            print_debug("start connection\n");
            Poco::Data::Session session = database::Database::get().create_session();
            
            Poco::Data::Statement msg(session);
            
            print_debug("start finding\n");

            
            msg<<"SELECT " LOGIN " , "  FIRST_NAME " , " LAST_NAME " , " AGE_PERSON " FROM " TABLE_NAME " where " FIRST_NAME " LIKE ? and " LAST_NAME " LIKE ?", 
        
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
                    list_clients->push_back(find_person);
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





    void Person::get_all_database(std::vector<Person> *list_person)
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

    bool Person::from_str(const std::string person_str, Person *man)
    {
        try
        {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(person_str);
            Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

            man->login       = object->getValue<std::string>(LOGIN);
            man->first_name  = object->getValue<std::string>(FIRST_NAME);
            man->last_name   = object->getValue<std::string>(LAST_NAME);
            man->age         = object->getValue<uint8_t>(AGE_PERSON);
            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    
    }

#ifdef CAHCE
   
    void Person::save_to_cache()
    {
        std::stringstream ss;
        Poco::JSON::Stringifier::stringify(converte_to_json(), ss);
        std::string person_s = ss.str();
        database::Cache::get().put(login, person_s);

    }

    bool Person::get_from_cache(const id_cache_t id_cache, Person *man)
    {
        try
        {
            std::string result;     result.clear();
            database::Cache::get().get_p(id_cache, result);

            if( !result.empty())
            {
                print_debug("get from cache result = %s\n", result.c_str());
                from_str(result, man);
                print_debug("берем из кеша\n");
                return true;
            }
            else 
            {
                print_debug(" ничего не найдено в кеше\n");
            }

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        return false;
    }

#endif



#ifdef KAFKA

    bool Person::send_kafka()
    {
        try
        {
            cppkafka::Configuration config = {{"metadata.broker.list", KAFKA_HOST}};

            static cppkafka::Producer producer(config);

            std::stringstream str_strm;

            Poco::JSON::Stringifier::stringify(converte_to_json(), str_strm);
            std::string kafka_msg = str_strm.str();

            static boost::mutex mtx_sig;
            boost::lock_guard<boost::mutex> lock(mtx_sig);
            bool send_flag = true;
            
            while(send_flag)
            {
                try
                {
                    producer.produce(cppkafka::MessageBuilder(NAME_PROC).partition(0).payload(kafka_msg ) );
                    send_flag = false;
                    print_debug("отправили в кафку\n");
                }
                catch(...)
                {
                    print_debug("не получилось отправить\n");
                }
                
                
            }
            

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            
        }
        return false;
       
        

    }
#endif




    Database::Database(){
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
}

