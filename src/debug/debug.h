#ifndef DEBUG_H
#define DEBUG_H


//#define PRINT_DEBUG

#ifdef PRINT_DEBUG

    #define print_debug(...) printf(__VA_ARGS__);

#else
    #define print_debug(...) do{}while(0)

#endif



#endif