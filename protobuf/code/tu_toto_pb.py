#!/usr/bin/env python3

import sys

# Protobuf generated file
import toto_pb_pb2
import google.protobuf.text_format
import google.protobuf.json_format

# Disable bytecode
sys.dont_write_bytecode = 1

message = toto_pb_pb2.toto_pb()

message.toto = "hello world"

message.type = toto_pb_pb2.toto_pb.TOTO_ONE

message.ids.append(1)
message.ids.append(2)
message.ids.append(3)
message.ids.append(4)

# Text formatting
text_out = google.protobuf.text_format.MessageToString(message)
print(text_out)

# JSON formatting
json_out = google.protobuf.json_format.MessageToJson(message)
print(json_out)
