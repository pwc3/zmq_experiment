#include <stdexcept>

#include "AudioPacket.hpp"
#include "zmq_experiment.pb-c.h"

std::vector<uint8_t> AudioPacket::serialize() const
{
    PBAudioPacket packet = PBAUDIO_PACKET__INIT;
    packet.wav_filename = const_cast<char *>(wav_file.c_str());
    packet.n_samples = samples.size();
    packet.samples = const_cast<float *>(samples.data());

    auto length = pbaudio_packet__get_packed_size(&packet);
    std::vector<uint8_t> buffer(length);
    pbaudio_packet__pack(&packet, buffer.data());

    return buffer;
}

AudioPacket AudioPacket::deserialize(const std::vector<uint8_t> &data)
{
    PBAudioPacket *packet = pbaudio_packet__unpack(nullptr, data.size(), data.data());
    if (packet == nullptr)
    {
        throw std::runtime_error("Failed to deserialize AudioPacket");
    }

    AudioPacket audio_packet(
        std::string(packet->wav_filename),
        std::vector<float>(packet->samples, packet->samples + packet->n_samples));

    pbaudio_packet__free_unpacked(packet, nullptr);
    return audio_packet;
}