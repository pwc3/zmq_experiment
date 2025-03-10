#pragma once

#include "message.hpp"
#include <zmq.hpp>
#include <iostream>

class Publisher
{
public:
    Publisher() : context(1), socket(context, zmq::socket_type::push)
    {
        socket.bind("tcp://*:5555"); // Bind to same port as Python
    }

    void publish(const Message &message)
    {
        std::vector<uint8_t> data = message.serialize();
        zmq::message_t zmq_message(data.data(), data.size());
        socket.send(zmq_message, zmq::send_flags::none);
    }

private:
    zmq::context_t context;
    zmq::socket_t socket;
};
