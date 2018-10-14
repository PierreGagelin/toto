//
// @brief Test file for the hello block
//

// Protobuf library
#include <google/protobuf/message_lite.h>
#include <google/protobuf/text_format.h>

#include "toto_pb.pb.h"

#include "toto.hpp"

// Fill a message
static void proto_fill(class toto_pb &msg)
{
    msg.set_toto("hello world");

    for (int i = 0; i < 4; ++i)
    {
        msg.add_ids(2 * i);
    }
}

// Check a message
static void proto_check(class toto_pb &msg)
{
    ASSERT(msg.toto() == "hello world");

    for (int i = 0; i < msg.ids_size(); ++i)
    {
        ASSERT(msg.ids(i) == (2 * i));
    }
}

static void proto_text()
{
    class toto_pb input;
    class toto_pb output;
    std::string buffer;

    proto_fill(input);

    ASSERT(google::protobuf::TextFormat::PrintToString(input, &buffer) == true);
    DEBUG("Formatted message to text [out=%s]", buffer.c_str());

    ASSERT(google::protobuf::TextFormat::ParseFromString(buffer, &output) == true);
    proto_check(output);
}

//
// @brief Use descriptor to inspect the message and reflection to retrieve values
//
static void proto_inspect()
{
    class toto_pb msg;

    proto_fill(msg);

    const google::protobuf::Descriptor *desc = msg.GetDescriptor();
    const google::protobuf::Reflection *refl = msg.GetReflection();
    int fieldCount = desc->field_count();

    DEBUG("Message information [name=%s]", desc->full_name().c_str());

    for (int i = 0; i < fieldCount; ++i)
    {
        const google::protobuf::FieldDescriptor *field = desc->field(i);
        if ((field->type() == google::protobuf::FieldDescriptor::TYPE_STRING) && (field->is_repeated() == false))
        {
            DEBUG("Field information [index=%d ; name=%s ; type=%s ; value=%s]", i, field->name().c_str(), field->type_name(), refl->GetString(msg, field).c_str());
        }
        else if ((field->type() == google::protobuf::FieldDescriptor::TYPE_INT32) && (field->is_repeated() == true))
        {
            int count = refl->FieldSize(msg, field);
            for (int j = 0; j < count; ++j)
            {
                DEBUG("Field information [index=%d.%d ; name=%s ; type=%s ; value=%d]", i, j, field->name().c_str(), field->type_name(), refl->GetRepeatedInt32(msg, field, j));
            }
        }
    }
}

//
// @brief Serialize and parse a message
//
static void proto_serialize_parse()
{
    class toto_pb input;
    class toto_pb output;
    std::string buf;

    proto_fill(input);

    ASSERT(input.SerializeToString(&buf) == true);
    ASSERT(output.ParseFromString(buf) == true);

    proto_check(output);
}

//
// @brief Basic usage of protobuf message and serialization
//
int main(int, char **)
{
    proto_serialize_parse();
    proto_inspect();
    proto_text();

    return 0;
}
