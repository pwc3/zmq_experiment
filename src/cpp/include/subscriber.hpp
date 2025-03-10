#pragma once

#include "message.hpp"
#include <zmq.hpp>
#include <iostream>

class Subscriber
{
public:
    Subscriber() : context(1), socket(context, zmq::socket_type::pull)
    {
        socket.connect("tcp://localhost:5555"); // Connects to Python Publisher
    }

    Message subscribe()
    {
        zmq::message_t zmq_message;
        auto result = socket.recv(zmq_message, zmq::recv_flags::none);
        if (!result)
        {
            throw std::runtime_error("Failed to receive message from socket");
        }

        std::vector<uint8_t> data(static_cast<uint8_t *>(zmq_message.data()),
                                  static_cast<uint8_t *>(zmq_message.data()) + zmq_message.size());

        return Message::deserialize(data);
    }

private:
    zmq::context_t context;
    zmq::socket_t socket;
};
