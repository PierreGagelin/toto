
#include <string>

extern "C"
{
#include "toto_pb.pb-c.h"
}

//
// @brief Check descriptor and print a message
//
static void toto_pb_print(TotoPb *msg)
{
    assert(toto_pb__descriptor.fields[0].type == PROTOBUF_C_TYPE_ENUM);
    assert(std::string(toto_pb__descriptor.fields[0].name) == "type");

    assert(toto_pb__descriptor.fields[1].type == PROTOBUF_C_TYPE_STRING);
    assert(std::string(toto_pb__descriptor.fields[1].name) == "toto");

    assert(toto_pb__descriptor.fields[2].type == PROTOBUF_C_TYPE_INT32);
    assert(toto_pb__descriptor.fields[2].label == PROTOBUF_C_LABEL_REPEATED);
    assert(std::string(toto_pb__descriptor.fields[2].name) == "ids");

    printf("Message information [name=%s]\n", toto_pb__descriptor.name);
    printf("Field information [index=%u ; name=%s ; value=%d]\n", 0u, toto_pb__descriptor.fields[0].name, msg->type);
    printf("Field information [index=%u ; name=%s ; value=%s]\n", 1u, toto_pb__descriptor.fields[1].name, msg->toto);
    for (size_t j = 0; j < msg->n_ids; ++j)
    {
        printf("Field information [index=%u.%zu ; name=%s ; value=%d]\n", 2u, j, toto_pb__descriptor.fields[2].name, msg->ids[j]);
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
    assert(size <= sizeof(buffer));

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
    assert(size <= sizeof(buffer));

    toto_oneof__pack(&input, buffer);

    output = toto_oneof__unpack(NULL, size, buffer);

    assert(output->msg_type_case == TOTO_ONEOF__MSG_TYPE_B);

    toto_oneof__free_unpacked(output, NULL);
}

int main(int, char **)
{
    test_pack();

    test_oneof();

    return 0;
}
