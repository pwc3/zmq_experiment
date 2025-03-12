#include "Publisher.hpp"

#include <filesystem>
#include <ostream>

Publisher::Publisher() : context(1), socket(context, zmq::socket_type::push)
{
    socket.bind("tcp://*:5555");
}

Publisher::~Publisher()
{
    socket.close();
}

void Publisher::publish(const AudioPacket &packet)
{
    auto serialized = packet.serialize();
    zmq::message_t zmq_message(serialized.data(), serialized.size());
    socket.send(zmq_message, zmq::send_flags::none);
}
