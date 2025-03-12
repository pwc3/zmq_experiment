#pragma once

#include "AudioPacket.hpp"
#include <functional>
#include <zmq.hpp>

class Subscriber
{
public:
    Subscriber();
    ~Subscriber();

    void subscribe(const std::function<bool(const AudioPacket &)> &callback);
    AudioPacket receive();

private:
    zmq::context_t context;
    zmq::socket_t socket;
};
