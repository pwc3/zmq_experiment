#pragma once

#include <filesystem>
#include <cstdint>
#include <vector>

// Message Struct
class AudioPacket
{
public:
    AudioPacket(const std::filesystem::path &wav_file, std::vector<float> samples)
        : wav_file(wav_file), samples(samples) {}

    const std::filesystem::path &get_wav_file() const { return wav_file; }
    const std::vector<float> &get_samples() const { return samples; }

    std::vector<uint8_t> serialize() const;
    static AudioPacket deserialize(const std::vector<uint8_t> &data);

private:
    std::filesystem::path wav_file;
    std::vector<float> samples;
};