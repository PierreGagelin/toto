FROM ubuntu:latest

RUN apt update
RUN apt install -y gcc
RUN apt install -y g++
RUN apt install -y cmake
RUN apt install -y make
RUN apt install -y protobuf-compiler
RUN apt install -y libprotobuf-dev
RUN apt install -y protobuf-c-compiler
RUN apt install -y libprotobuf-c-dev
RUN apt install -y python3
RUN apt install -y python3-pip
RUN python3 -m pip install protobuf

RUN apt install -y gdb

CMD ["bash"]
