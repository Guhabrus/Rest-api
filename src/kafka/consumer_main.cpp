
#include <iostream>


#include "kafka_q.h"

int main(int argc, char *argv[])
{

    std::cout<<"Hello i am consumer"<<std::endl;

    Kafka_consumer consumer;

    return consumer.run(argc, argv);
}