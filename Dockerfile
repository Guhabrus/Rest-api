FROM ubuntu:20.04 as build
ARG DEBIAN_FRONTEND=noninteractive

#устанавливаем все необходимые пакеты

RUN apt-get update
RUN apt-get upgrade

RUN apt-get install -yq build-essential autoconf libtool git\
                            pkg-config gcc g++ cmake \
                            libssl-dev zlib1g-dev librdkafka-dev libmysqlclient-dev libboost-all-dev

#качаем и устанавливаем poco
RUN cd
RUN git clone -b master https://github.com/pocoproject/poco.git
RUN cd poco && mkdir cmake-build && cd cmake-build && cmake .. && cmake --build . --config Release && cmake --build . --target install



COPY . /Serv

WORKDIR /Serv

# RUN ls

EXPOSE 8080

# RUN pwd

RUN rm -r build

# RUN ls

RUN mkdir bin && cd bin && cmake .. && cmake --build . 

# RUN ls

# RUN pwd


ENV LD_LIBRARY_PATH=/usr/local/lib

CMD ["./bin/SERV1"]

