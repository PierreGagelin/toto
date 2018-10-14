
extern "C"
{
#include "toto_pb.pb-c.h"
}

#include "toto.hpp"

//
// @brief Check descriptor and print a message
//
static void proto_print(TotoPb *msg)
{
    ASSERT(toto_pb__descriptor.fields[0].type == PROTOBUF_C_TYPE_STRING);
    ASSERT(toto_pb__descriptor.fields[0].label == PROTOBUF_C_LABEL_REQUIRED);
    ASSERT(std::string(toto_pb__descriptor.fields[0].name) == "toto");

    ASSERT(toto_pb__descriptor.fields[1].type == PROTOBUF_C_TYPE_INT32);
    ASSERT(toto_pb__descriptor.fields[1].label == PROTOBUF_C_LABEL_REPEATED);
    ASSERT(std::string(toto_pb__descriptor.fields[1].name) == "ids");

    DEBUG("Message information [name=%s]", toto_pb__descriptor.name);
    DEBUG("Field information [index=%u ; name=%s ; value=%s]", 0u, toto_pb__descriptor.fields[0].name, msg->toto);
    for (size_t j = 0; j < msg->n_ids; ++j)
    {
        DEBUG("Field information [index=%u.%zu ; name=%s ; value=%d]", 1u, j, toto_pb__descriptor.fields[1].name, msg->ids[j]);
    }
}

int main(int, char **)
{
    int32_t ids[] = {0, 2, 4, 6};
    char str[] = "hello world";
    TotoPb input;
    TotoPb *output;
    uint8_t buffer[256];

    toto_pb__init(&input);

    input.toto = str;
    input.ids = ids;
    input.n_ids = (sizeof(ids) / sizeof(ids[0]));

    size_t size = toto_pb__get_packed_size(&input);
    ASSERT(size <= sizeof(buffer));

    toto_pb__pack(&input, buffer);

    output = toto_pb__unpack(NULL, size, buffer);

    proto_print(output);

    toto_pb__free_unpacked(output, NULL);

    return 0;
}
