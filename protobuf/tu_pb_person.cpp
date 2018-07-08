//
// @brief Test file for the hello block
//

// Protobuf library
#include <google/protobuf/message_lite.h>                  // SerializeToZeroCopyStream, ParseFromZeroCopyStream
#include <google/protobuf/io/zero_copy_stream.h>           // ZeroCopyInputStream, ZeroCopyOutputStream
#include <google/protobuf/io/zero_copy_stream_impl_lite.h> // StringOutputStream, ArrayInputStream

#include "test.pb.h"

#include "toto.hpp"

//
// @brief Basic usage of protobuf message and serialization
//
int main(int argc, char **argv)
{
    class person p_in;
    class person p_out;
    google::protobuf::io::ZeroCopyInputStream *input;
    google::protobuf::io::ZeroCopyOutputStream *output;
    std::string s_out;

    (void)argc;
    (void)argv;

    p_in.set_id1(1);
    p_in.set_id2(2);
    p_in.set_id3(3);
    p_in.set_id4(4);
    p_in.set_id5(5);
    ASSERT(p_in.id1() == 1);
    ASSERT(p_in.id2() == 2);
    ASSERT(p_in.id3() == 3);
    ASSERT(p_in.id4() == 4);
    ASSERT(p_in.id5() == 5);

    p_in.set_toto("Toto de l'ASTICOT");
    ASSERT(p_in.toto() == "Toto de l'ASTICOT");

    // Serialize the message into the output file
    output = new google::protobuf::io::StringOutputStream(&s_out);
    ASSERT(p_in.SerializeToZeroCopyStream(output));

    // Parse the message from the input file
    input = new google::protobuf::io::ArrayInputStream(s_out.c_str(), s_out.length());
    ASSERT(p_out.ParseFromZeroCopyStream(input));

    ASSERT(p_out.id1() == 1);
    ASSERT(p_out.id2() == 2);
    ASSERT(p_out.id3() == 3);
    ASSERT(p_out.id4() == 4);
    ASSERT(p_out.id5() == 5);
    ASSERT(p_out.toto() == std::string("Toto de l'ASTICOT"));

    delete input;
    delete output;

    return 0;
}
