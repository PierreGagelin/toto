#!/usr/local/bin/python3

import zmq

client_ctx = zmq.Context.instance()
client_sock = client_ctx.socket(zmq.PAIR)

server_ctx = zmq.Context.instance()
server_sock = server_ctx.socket(zmq.PAIR)

poller = zmq.Poller()
poller.register(client_sock, zmq.POLLIN)
poller.register(server_sock, zmq.POLLIN)

server_sock.bind('tcp://127.0.0.1:5555')
client_sock.connect('tcp://127.0.0.1:5555')

client_sock.send_string('hello world')

# Poll the sockets
events = dict(poller.poll(100))
if server_sock in events.keys():
    print("Polling: OK")
else:
    print("Polling: KO")
print("{}".format(events))

message = server_sock.recv_string()

print(message)
