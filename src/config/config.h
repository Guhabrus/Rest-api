#ifndef CONFIG_H
#define CONFIG_H


//#define CACHE
#define KAFKA

#include <string>


#define TABLE_NAME      "clients"        ///< Имя таблицыя
#define BD_NAME         "best_server"      ///< Имя proxysql
#define SQL_USERNAME    "sqluser"          ///< Логин в proxysql
#define PASSWORD_SQL    "Kukusale8691!"    ///< Пароль к proxysql
#define PORT            "3306"             ///< Порт подключения к proxysql
#define HOST_IP         "127.0.0.1"        ///< Локальный IP
#define NAME_PROC       "event_server"


#ifdef CACHE
    #define KEY_CAHCE       "127.0.0.1:10800,127.0.0.1:10900"  ///< 
#endif

#ifdef KAFKA
    #define KAFKA_HOST       "127.0.0.1:9092"
#endif



class  Config{
    private:
        Config();
        std::string _host;
        std::string _port;
        std::string _login;
        std::string _password;
        std::string _database;

    public:
        static Config& get();

        std::string& port();
        std::string& host();
        std::string& login();
        std::string& password();
        std::string& database();

        const std::string& get_port() const ;
        const std::string& get_host() const ;
        const std::string& get_login() const ;
        const std::string& get_password() const ;
        const std::string& get_database() const ;
};

#endif