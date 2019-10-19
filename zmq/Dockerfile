FROM debian:latest

RUN apt update
RUN apt install -y gcc
RUN apt install -y g++
RUN apt install -y libzmq3-dev
RUN apt install -y python3
RUN apt install -y python3-pip
RUN python3 -m pip install zmq

CMD ["bash"]
