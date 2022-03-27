#include <string>
#include <vector>

#include <Poco/JSON/Object.h>
#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/SessionFactory.h>


#define PUT_TO_DATABASE(ARGV)     Poco::Data::Keywords::use(ARGV)              ///< Записать в БД
#define GET_FROM_DATABASE(ARGV)   Poco::Data::Keywords::into(ARGV)             ///< Взять из БД 
#define OPTION_RESEARCH(...)      Poco::Data::Keywords::range(__VA_ARGS__)     ///< Задать опции поиска по БД 

#define MAX_SIZE_STR    20      ///< максимальная длинна строки (логин ..)
#define MIN_SIZE_STR    2       ///< минимальная длинная троки (логин ...)
#define MAX_AGE         254     ///< максимальный возраст
#define MIN_AGE         18      ///< минимальный возраст

#define LOGIN           "login"
#define FIRST_NAME      "first_name"
#define LAST_NAME       "last_name"
#define AGE_PERSON      "age"

namespace database
{


    enum Result
    {
        SUCCES,             ///< успешно
        TOO_LONG,           ///< слишком много
        TOO_SHORT,          ///< слишком мало
        INCORRECT,          ///< некоректное
        UNKNOWN             ///< неизвестаня ошибка
    };

    class Person
    {

        public:
            Person(){}

            Person(std::string login, std::string first_name, std::string last_name,uint8_t age)
            {
                this->login = login;
                this->first_name = first_name;
                this->last_name=last_name;
                this->age = age;
            }        

             /**
             * @brief Функция конвертации объекта в json формат
             * 
             * @return Poco::JSON::Object::Ptr 
             */
            Poco::JSON::Object::Ptr converte_to_json();


            
            

            std::string get_login()      {return login;}
            std::string get_first_name() {return first_name;}
            std::string get_last_name(){return last_name;}
            uint8_t     get_age()        {return age;}

            /**
             * @brief Set the login object
             * 
             * @param login - логин товарища
             * @return Result - результат записи 0- успешно, 1 - слишком длинный логин, 
             * 2 - слишком корроткий логин
             * 3 - содержит недопустимые символы
             */
            Result set_login(std::string login);

            /**
             * @brief Set the first_name object
             * 
             * @param first_name - имя товарища
             * @return Result - результат записи 0- успешно, 1 - слишком длинное имя, 
             * 2 - слишком корроткое имя
             * 3 - содержит недопустимые символы
             */
            Result set_first_name(std::string first_name);

            /**
             * @brief Set the last_name object
             * 
             * @param last_name фамилия товарища
             * @return Result - результат записи 0- успешно, 1 - слишком длинное имя, 
             * 2 - слишком корроткое имя
             * 3 - содержит недопустимые символы
             */
            Result set_last_name(std::string last_name);

            /**
             * @brief Set the age object
             * 
             * @param age - возраст товарища
             * @return Result результат записи 0- успешно, 1 - слишком большой возраст (255-), 
             * 2 - слишком маленикий возраст (18+)
             * 3 - содержит недопустимые символы
             */
            Result set_age(uint8_t age);


            static Person test(){                   //TODO не забыть удалить (нужна была для отладки)
                Person ex;  
                ex.set_age(22);
                ex.set_first_name("maks");
                ex.set_login("guhab");
                ex.set_last_name("kukushkin");
                return ex;
            }

           /**
            * @brief сохраняет данные в базу данных (пока она void поток сделать возврат кода результата)
            * 
            * @return uint8_t код ошибки
            */
            uint8_t save_to_database();

            /**
             * @brief функция поиска обхекта по логину
             * 
             * @param login -> уникальный логик по которому будет идти поиск
             * @return Person -> найденный объект
             */
            static  Person find_by_login(std::string login_f);


            /**
             * @brief Поиск персонажей по мени и фамилии (last_name)
             * 
             * @param first_name  - Имя по которому будет осуществляться поиск
             * @param last_name  - Фамилия по которому будет осуществляться поиск
             * @param last_name  - Список найденных клиентов
             * @return код ошибки: 0 - успешно, остальное не очень
             */
            static uint8_t find_by_first_and_last_name(std::string first_name, std::string last_name, std::vector<Person> *list_clients);


            /**
             * @brief забрать все объекты из базы данных
             * 
             * @param list_person указатель на список объектов в которые будут положенны все клиенты
             */
            static void get_all_database(std::vector<Person> *list_person);



            void init_connetc_to_database();

        private:
            
            std::string login;                                          
            std::string first_name;
            std::string last_name;
            uint8_t age;

    };






    /**
     * @brief класс для соединения с mysql (каюсь реализацию взял у вас)
     * 
     */
    class Database{
        private:
            std::string _connection_string;
            Database();
        public:
            static Database& get();
            Poco::Data::Session create_session();
    };

}


