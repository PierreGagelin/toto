
extern "C"
{
#include "toto_pb.pb-c.h"
}

#include "toto.hpp"

//
// @brief Check descriptor and print a message
//
static void toto_pb_print(TotoPb *msg)
{
    ASSERT(toto_pb__descriptor.fields[0].type == PROTOBUF_C_TYPE_ENUM);
    ASSERT(toto_pb__descriptor.fields[0].label == PROTOBUF_C_LABEL_NONE);
    ASSERT(std::string(toto_pb__descriptor.fields[0].name) == "type");

    ASSERT(toto_pb__descriptor.fields[1].type == PROTOBUF_C_TYPE_STRING);
    ASSERT(toto_pb__descriptor.fields[1].label == PROTOBUF_C_LABEL_NONE);
    ASSERT(std::string(toto_pb__descriptor.fields[1].name) == "toto");

    ASSERT(toto_pb__descriptor.fields[2].type == PROTOBUF_C_TYPE_INT32);
    ASSERT(toto_pb__descriptor.fields[2].label == PROTOBUF_C_LABEL_REPEATED);
    ASSERT(std::string(toto_pb__descriptor.fields[2].name) == "ids");

    DEBUG("Message information [name=%s]", toto_pb__descriptor.name);
    DEBUG("Field information [index=%u ; name=%s ; value=%d]", 0u, toto_pb__descriptor.fields[0].name, msg->type);
    DEBUG("Field information [index=%u ; name=%s ; value=%s]", 1u, toto_pb__descriptor.fields[1].name, msg->toto);
    for (size_t j = 0; j < msg->n_ids; ++j)
    {
        DEBUG("Field information [index=%u.%zu ; name=%s ; value=%d]", 2u, j, toto_pb__descriptor.fields[2].name, msg->ids[j]);
    }
}

static void test_pack()
{
    int32_t ids[] = {0, 2, 4, 6};
    char str[] = "hello world";
    TotoPb input;
    TotoPb *output;
    uint8_t buffer[256];

    toto_pb__init(&input);

    input.type = TOTO_PB__TOTO_ENUM__TOTO_TWO;
    input.toto = str;
    input.ids = ids;
    input.n_ids = (sizeof(ids) / sizeof(ids[0]));

    size_t size = toto_pb__get_packed_size(&input);
    ASSERT(size <= sizeof(buffer));

    toto_pb__pack(&input, buffer);

    output = toto_pb__unpack(NULL, size, buffer);

    toto_pb_print(output);

    toto_pb__free_unpacked(output, NULL);
}

static void test_oneof()
{
    TotoOneof input;
    TotoOneof *output;
    uint8_t buffer[256];
    char hello[] = "hello world";

    toto_oneof__init(&input);

    input.msg_type_case = TOTO_ONEOF__MSG_TYPE_B;
    input.b = hello;

    size_t size = toto_oneof__get_packed_size(&input);
    ASSERT(size <= sizeof(buffer));

    toto_oneof__pack(&input, buffer);

    output = toto_oneof__unpack(NULL, size, buffer);

    ASSERT(output->msg_type_case == TOTO_ONEOF__MSG_TYPE_B);

    toto_oneof__free_unpacked(output, NULL);
}

int main(int, char **)
{
    test_pack();

    test_oneof();

    return 0;
}
