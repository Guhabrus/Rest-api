#ifndef KAFKA_H
#define KAFKA_H

#include <boost/program_options.hpp>
#include <iostream>
#include <csignal>
#include <cppkafka/consumer.h>
#include <cppkafka/configuration.h>
#include <string>


#define READ_PARS       "read"
#define WRITE_PARS      "write"
#define PORT_PARS       "port"
#define LOGIN_PARS      "login"
#define PASSWORD_PARS   "password"
#define DATABASE_PARS   "database"
#define QUEUE_PARS      "queue"
#define TOPIC_PARS      "topic"
#define GROUP_ID_PARS   "group_id"
#define CACHE_SERV_PARS "cache_servers"

enum Retcode
{
    SUCCES,         ///< балдежно
    BAD_INPUT,      ///< не удалось распарсить
    BAD_CONTENT,    ///< не удалось перевести в сущность person
    BAD_SAVE        ///< не удалось сохранить в БД
};

class Kafka_consumer
{
    public:
        Kafka_consumer(){}
        ~Kafka_consumer(){}

        /**
         * @brief функция старта работы consumer
         * 
         * @param argc_ 
         * @param argv_ 
         * @return Retcode код выполнения работы
         */
        Retcode run(int argc_, char *argv_[]);


    private:

        std::string read_ip;
        std::string writte_ip;
        std::string port;
        std::string login;
        std::string password;
        std::string database;
        std::string queue;
        std::string topic;
        std::string group_id;

      

        /**
         * @brief Функция распарсивания входные данных
         * 
         * @param pars_line  то что подали через ввод программе
         * @return true     если успешно
         * @return false    если неудачно
         */
        bool pars_cmd(boost::program_options::variables_map pars_line_);
};



#endif