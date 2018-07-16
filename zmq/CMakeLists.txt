
configure_file(tu_zmq.py tu_zmq.py COPYONLY)
add_test(NAME tu_zmq_py COMMAND ./tu_zmq.py)
