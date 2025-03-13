#include "Subscriber.hpp"

#include <string>

Subscriber::Subscriber() : context(1), socket(context, zmq::socket_type::pull)
{
    socket.connect("tcp://localhost:5555"); // Connects to Python Publisher
}

Subscriber::~Subscriber()
{
    socket.close();
}

void Subscriber::subscribe(const std::function<bool(const AudioPacket &)> &callback)
{
    while (true)
    {
        AudioPacket packet = receive();
        if (!callback(packet))
        {
            break;
        }
    }
}

AudioPacket Subscriber::receive()
{
    zmq::message_t zmq_message;
    auto result = socket.recv(zmq_message, zmq::recv_flags::none);

    if (!result)
    {
        throw std::runtime_error("Failed to receive message from socket");
    }

    auto buffer = static_cast<uint8_t *>(zmq_message.data());
    auto data = std::vector(buffer, buffer + zmq_message.size());
    return AudioPacket::deserialize(data);
}
