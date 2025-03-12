#pragma once

#include "AudioPacket.hpp"
#include <zmq.hpp>

class Publisher
{
public:
    Publisher();
    ~Publisher();

    void publish(const AudioPacket &packet);

private:
    zmq::context_t context;
    zmq::socket_t socket;
};
