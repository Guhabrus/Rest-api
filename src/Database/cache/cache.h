#ifndef CACHE_H
#define CACHE_H


// #include <ignite/thin/ignite_client.h>
// #include <ignite/thin/ignite_client_configuration.h>
// #include <ignite/thin/cache/cache_peek_mode.h>

 
#include "../../debug/debug.h"
#include "../../config/config.h"

typedef std::string id_cache_t;

namespace database
{
    class Cache
    {
        public:

        /**
         * @brief Функция для получения объекта класса
         * 
         * @return Cache объект класса соответсвенно
         */
        static Cache get();        

        /**
         * @brief Функция записи в кеш
         * 
         * @param person_s сущность person в виде строки
         * @param login    логин сущности person (уникальное поле)
         */
        void put(std::string login,const std::string person_s);

        /**
         * @brief Get the from cache object
         * 
         * @param person_s сущность person в виде строки
         * @param login    логин сущности person (уникальное поле)
         */
        void  get_p(std::string login,std::string &person_s);

        private:

        Cache();
    };
}


#endif