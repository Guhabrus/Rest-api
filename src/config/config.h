#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <iostream>
#include "../debug/debug.h"

#define TABLE_NAME      " clients "        ///< Имя таблицыя
#define BD_NAME         "best_server"      ///< Имя proxysql
#define SQL_USERNAME    "sqluser"          ///< Логин в proxysql
#define PASSWORD_SQL    "Kukusale8691!"    ///< Пароль к proxysql
#define PORT            "6033"             ///< Порт подключения к proxysql
#define HOST_IP         "127.0.0.1"        ///< Локальный IP

#define TOTAL_SHARD     3                  ///< Кол-во БД (нужно чтобы равномерно шардирвоать)              

class  Config{
    private:
        
        std::string _host;
        std::string _port;
        std::string _login;
        std::string _password;
        std::string _database;

    public:

        Config(int argc, char* argv[])
        {
            for(int i=0;i<argc; i++)
                print_debug("argc = %d, argv = %s\n", i,argv[i]);
        }
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