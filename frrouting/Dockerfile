FROM debian:latest

RUN apt update
RUN apt install -y curl
RUN apt install -y gnupg
RUN apt install -y lsb-release
RUN apt install -y software-properties-common


RUN curl -s https://deb.frrouting.org/frr/keys.asc | apt-key add -
RUN add-apt-repository "deb https://deb.frrouting.org/frr $(lsb_release -s -c) frr-stable"

RUN apt update
RUN apt install -y frr
RUN apt install -y frr-pythontools

RUN apt install -y procps
RUN apt install -y telnet

CMD ["bash"]
