#include "cache.h"

#include <ignite/thin/ignite_client.h>
#include <ignite/thin/ignite_client_configuration.h>



static ignite::thin::IgniteClient _client;
static ignite::thin::cache::CacheClient<id_cache_t, std::string> _cache;



namespace database
{

    Cache Cache::get()
    {
        static Cache tmp;
        return tmp;
    }


    void Cache::put(const id_cache_t id_cache,std::string person_s)
    {
        _cache.Put(id_cache, person_s);
    }


    void Cache::get_p(const id_cache_t id_cache,std::string &person_s)
    {
        print_debug("get_fom cache\n");
        try
        {
            person_s = _cache.Get(id_cache);
        }
        catch(const std::exception& e)
        {
            std::cerr <<" Error <get from cache>"<< e.what() << '\n';
        }
        
    }





    Cache::Cache()
    {
        ignite::thin::IgniteClientConfiguration cfg;
        cfg.SetEndPoints(KEY_CAHCE);
        cfg.SetPartitionAwareness(true);

        try
        {
            _client = ignite::thin::IgniteClient::Start(cfg);
            _cache = _client.GetOrCreateCache<id_cache_t, std::string>(TABLE_NAME);
        }
        catch (ignite::IgniteError* err)
        {
            std::cout << "error:" << err->what() << std::endl;
            throw;
        }

    }

}