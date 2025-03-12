#include <stdexcept>

#include "AudioPacket.hpp"
#include "zmq_experiment.pb.h"

std::string AudioPacket::serialize() const
{
    PBAudioPacket packet;
    packet.set_wav_filename(wav_file.string());
    packet.mutable_samples()->Add(samples.begin(), samples.end());

    std::string serialized;
    if (!packet.SerializeToString(&serialized))
    {
        throw std::runtime_error("Failed to serialize AudioPacket");
    }

    return serialized;
}

AudioPacket AudioPacket::deserialize(const std::string &data)
{
    PBAudioPacket packet;
    if (!packet.ParseFromString(data))
    {
        throw std::runtime_error("Failed to parse AudioPacket");
    }

    return AudioPacket(
        packet.wav_filename(),
        std::vector<float>(packet.samples().begin(), packet.samples().end()));
}