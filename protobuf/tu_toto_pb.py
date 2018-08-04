
import sys

# Protobuf generated file
import toto_pb_pb2

# Disable bytecode
sys.dont_write_bytecode = 1

message = toto_pb_pb2.toto_pb()

print("{}".format(message.HasField("id1")))
message.id1 = 1
print("{}".format(message.HasField("id1")))
