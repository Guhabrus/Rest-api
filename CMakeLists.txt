cmake_minimum_required(VERSION 3.2)
project(best_server C CXX)
SET (EXAMPLE_BINARY "SERV1")



find_package(Boost 1.67.0 REQUIRED COMPONENTS thread system iostreams)
find_package(OpenSSL)
find_package(Threads)
find_package(ZLIB)
find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON Crypto NetSSL)
find_package(Java 1.8 REQUIRED)
find_package(JNI REQUIRED)


if(NOT ${Poco_FOUND})
    message(FATAL_ERROR "Poco C++ Libraries not found.")
endif()

if(NOT ${Boost_FOUND})
    message(FATAL_ERROR "Boost C++ Libraries not found.")
endif()


if(NOT ${OpenSSL_FOUND})
    message(FATAL_ERROR "Poco C++ Libraries not found.")
endif()

if(NOT ${JNI_FOUND})
    message(FATAL_ERROR "Ignite ot found.")
endif()

if(NOT ${Java_FOUND})
    message(FATAL_ERROR "JAVA not found.")
endif()

include_directories(SYSTEM ${IGNITE_INCLUDE_DIR} ${JNI_INCLUDE_DIRS})
include_directories(${Poco_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIR})

add_executable(${EXAMPLE_BINARY} src/main.cpp src/Server/web_server.cpp src/Some_handlers/MyHendlers.cpp src/Database/Person/person.cpp src/Database/cache/cache.cpp)        

target_include_directories(${EXAMPLE_BINARY} PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(${EXAMPLE_BINARY} PRIVATE -Wall -Wextra -pedantic -Werror )


target_link_libraries(${EXAMPLE_BINARY} PRIVATE 
                             ${CMAKE_THREAD_LIBS_INIT} 
                             ${Poco_LIBRARIES}
                             "PocoData"
                             "PocoDataMySQL"
                             ${IGNITE_JNI_LIB}
                             "ignite-thin-client"
                             "ignite-binary"
                             "ignite-common"
                            ${Boost_LIBRARY_DIRS}
                             ZLIB::ZLIB)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

# set_target_properties(${EXAMPLE_BINARY} PROPERTIES LINKER_LANGUAGE CXX)
# set_target_properties(${EXAMPLE_BINARY} 
#                      PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)


# install(TARGETS ${EXAMPLE_BINARY} RUNTIME DESTINATION bin)