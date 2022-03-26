#ifndef CONFIG_H
#define CONFIG_H

#include <string>


#define TABLE_NAME      " clients "          ///< Имя таблицыя
#define BD_NAME         " best_server "      ///< Имя БД
#define SQL_USERNAME    " sqluser "         ///< Логин в БД
#define PASSWORD_SQL    " Kukusale8691! "    ///< Пароль к БД


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