cmake_minimum_required(VERSION 3.2)
project(best_server C CXX)

SET (EXAMPLE_BINARY "event_server")
SET (WRITTER_BINARY "consumer")



find_package(OpenSSL)
find_package(Threads)
find_package(ZLIB)
find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON Crypto NetSSL)
find_package(CppKafka REQUIRED)
find_package(Boost COMPONENTS filesystem system program_options regex REQUIRED)
# find_package(Java 1.8 REQUIRED)
# find_package(JNI REQUIRED)


if(NOT ${Poco_FOUND})
    message(FATAL_ERROR "Poco C++ Libraries not found.")
endif()

if(NOT ${Boost_FOUND})
    message(FATAL_ERROR "Boost C++ Libraries not found.")
endif()


if(NOT ${OpenSSL_FOUND})
    message(FATAL_ERROR "Open SSl C++ Libraries not found.")
endif()

if(NOT ${CppKafka_FOUND})
    message(FATAL_ERROR "Kafka C++ Libraries not found.")
endif()


# if(NOT ${JNI_FOUND})
#     message(FATAL_ERROR "Ignite ot found.")
# endif()

# if(NOT ${Java_FOUND})
#     message(FATAL_ERROR "JAVA not found.")
# endif()

# include_directories(SYSTEM ${IGNITE_INCLUDE_DIR} ${JNI_INCLUDE_DIRS})
include_directories(${Poco_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIR})

add_executable(${EXAMPLE_BINARY} src/main.cpp src/Server/web_server.cpp src/Some_handlers/MyHendlers.cpp src/Database/Person/person.cpp src/Database/cache/cache.cpp)        
add_executable(${WRITTER_BINARY} src/kafka/consumer_main.cpp src/kafka/kafka_q.cpp src/Database/Person/person.cpp  )        

target_include_directories(${EXAMPLE_BINARY} PRIVATE "${CMAKE_BINARY_DIR}")
target_include_directories(${WRITTER_BINARY} PRIVATE "${CMAKE_BINARY_DIR}")

target_compile_options(${EXAMPLE_BINARY} PRIVATE -Wall -Wextra -pedantic -Werror )
target_compile_options(${WRITTER_BINARY} PRIVATE -Wall -Wextra -pedantic -Werror )


target_link_libraries(${EXAMPLE_BINARY} PRIVATE 
                             ${CMAKE_THREAD_LIBS_INIT} 
                             ${Poco_LIBRARIES}
                             "PocoData"
                             "PocoDataMySQL"
                             "rdkafka++"
                             CppKafka::cppkafka
                            #  ${IGNITE_JNI_LIB}
                            #  "ignite-thin-client"
                            #  "ignite-binary"
                            #  "ignite-common"
                            ${Boost_LIBRARIES}
                            ZLIB::ZLIB)


target_link_libraries(${WRITTER_BINARY} PRIVATE 
                             ${CMAKE_THREAD_LIBS_INIT} 
                             ${Poco_LIBRARIES}
                             "PocoData"
                             "PocoDataMySQL"
                             "rdkafka++"
                             CppKafka::cppkafka
                             ${Boost_LIBRARIES}
                             ZLIB::ZLIB)


set_target_properties(${EXAMPLE_BINARY} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${EXAMPLE_BINARY} PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

set_target_properties(${WRITTER_BINARY} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${WRITTER_BINARY} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
