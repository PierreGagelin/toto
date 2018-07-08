//
// @brief Test file for the hello block
//

// Protobuf library
#include <google/protobuf/message_lite.h>

#include "toto_pb.pb.h"

#include "toto.hpp"

//
// @brief Basic usage of protobuf message and serialization
//
int main(int argc, char **argv)
{
    class toto_pb input;
    class toto_pb output;
    const char *toto_str = "Toto de l'ASTICOT";
    std::string buf;

    (void)argc;
    (void)argv;

    input.set_id1(1);
    input.set_id2(2);
    input.set_id3(3);
    input.set_id4(4);
    input.set_id5(5);
    input.set_toto(toto_str);
    ASSERT(input.id1() == 1);
    ASSERT(input.id2() == 2);
    ASSERT(input.id3() == 3);
    ASSERT(input.id4() == 4);
    ASSERT(input.id5() == 5);
    ASSERT(input.toto() == toto_str);

    ASSERT(input.SerializeToString(&buf) == true);
    ASSERT(output.ParseFromString(buf) == true);

    ASSERT(output.id1() == 1);
    ASSERT(output.id2() == 2);
    ASSERT(output.id3() == 3);
    ASSERT(output.id4() == 4);
    ASSERT(output.id5() == 5);
    ASSERT(output.toto() == toto_str);

    return 0;
}
