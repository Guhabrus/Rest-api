#include "kafka_q.h"
#include "../debug/debug.h"
#include "../Database/Person/person.h"

namespace po = boost::program_options;

bool run_sig = true;
Retcode Kafka_consumer::run(int argc_, char *argv_[])
{
    po::options_description desc{"Options"};
    
    
    try
    {
        desc.add_options()("help,h", "This screen")
        ("read,",          po::value<std::string>()->required(), "set ip address for read requests")  
        ("write,",         po::value<std::string>()->required(), "set ip address for write requests") 
        ("port," ,         po::value<std::string>()->required(), "databaase port")                    
        ("login,",         po::value<std::string>()->required(), "database login")                     
        ("password,",      po::value<std::string>()->required(), "database password")                  
        ("database,",      po::value<std::string>()->required(), "database name")                    
        ("queue,",         po::value<std::string>()->required(), "queue url")                        
        ("topic,",         po::value<std::string>()->required(), "topic name")                       
        ("group_id,",      po::value<std::string>()->required(), "consumer group_id name")           
        ("cache_servers,", po::value<std::string>()->required(), "iginite cache servers");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return Retcode::BAD_INPUT;
    }
    
    
    

    po::variables_map pars_line;
    po::store(po::parse_command_line(argc_,argv_, desc), pars_line);


    if(!pars_cmd(pars_line))
        return Retcode::BAD_INPUT;

    signal(SIGINT, [](int){run_sig = false  ;});

    cppkafka::Configuration config = {
            {"metadata.broker.list", this->queue},
            {"group.id", this->group_id},
            {"enable.auto.commit", false}};


    cppkafka::Consumer consumer(config);

    consumer.set_assignment_callback([](const cppkafka::TopicPartitionList &partitions)
                                         { std::cout << "Got assigned: " << partitions << std::endl; });


     consumer.set_revocation_callback([](const cppkafka::TopicPartitionList &partitions)
                                         { std::cout << "Got revoked: " << partitions << std::endl; });

    consumer.subscribe({this->topic});

    try
    {
        while(run_sig)
        {
            
            cppkafka::Message msg_consumer = consumer.poll();
            
            if(msg_consumer)
            {
                print_debug("сообщение есть\n");
                if(msg_consumer.get_error())
                {
                    if(!msg_consumer.is_eof())
                        std::cout<<" we have some error"<<std::endl;
                }
                else
                {
                    std::string msg_load = msg_consumer.get_payload();

                    print_debug(" суть сообщения %s\n", msg_load.c_str());

                    database::Person man;
                    if(! database::Person::from_str(msg_load, &man))
                    {
                        print_debug("не получилось распарсить\n");
                        std::cerr<<" <Error> - "<<Retcode::BAD_CONTENT<<std::endl;
                        //return Retcode::BAD_CONTENT;
                    }
                    if(!man.save_to_database())
                    {
                        std::cerr<<" <Error> - "<<Retcode::BAD_SAVE<<std::endl;
                    }

                    consumer.commit(msg_consumer);
                }
                
            }

        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    

    return Retcode::SUCCES;
}


bool Kafka_consumer:: pars_cmd(boost::program_options::variables_map pars_line_)
{
    try
    {
        if(pars_line_.count(READ_PARS))
        {
            this->read_ip = pars_line_[READ_PARS].as<std::string>();
            print_debug("<kafka pars_cmd>---> read ip = %s\n",this->read_ip.c_str() );
        }

        if(pars_line_.count(WRITE_PARS))
        {
            this->writte_ip = pars_line_[WRITE_PARS].as<std::string>();
            print_debug("<kafka pars_cmd>---> writte ip = %s\n",this->writte_ip.c_str() );
        }

        if(pars_line_.count(PORT_PARS))
        {
            this->port = pars_line_[PORT_PARS].as<std::string>();
            print_debug("<kafka pars_cmd>---> port = %s\n",this->port.c_str());
        }

        if(pars_line_.count(LOGIN_PARS))
        {
            this->login = pars_line_[LOGIN_PARS].as<std::string>();
            print_debug("<kafka pars_cmd>---> login = %s\n",this->login.c_str() );
        }

        if(pars_line_.count(PASSWORD_PARS))
        {
            this->password = pars_line_[PASSWORD_PARS].as<std::string>();
            print_debug("<kafka pars_cmd>---> password = %s\n",this->password.c_str() );
        }

        if(pars_line_.count(DATABASE_PARS))
        {
            this->database = pars_line_[DATABASE_PARS].as<std::string>();
            print_debug("<kafka pars_cmd>---> database = %s\n",this->database.c_str() );
        }

        if(pars_line_.count(QUEUE_PARS))
        {
            this->queue = pars_line_[QUEUE_PARS].as<std::string>();
            print_debug("<kafka pars_cmd>---> queue = %s\n",this->queue.c_str() );
        }


        if(pars_line_.count(TOPIC_PARS))
        {
            this->topic = pars_line_[TOPIC_PARS].as<std::string>();
            print_debug("<kafka pars_cmd>---> topic = %s\n",this->topic.c_str() );
        }


        if(pars_line_.count(GROUP_ID_PARS))
        {
            this->group_id = pars_line_[GROUP_ID_PARS].as<std::string>();
            print_debug("<kafka pars_cmd>---> group id = %s\n",this->group_id.c_str() );
        }

        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
    
}