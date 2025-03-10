#pragma once

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

// MessageType Enum (Matches Python)
enum class MessageType : uint8_t
{
    FULL = 1,
    START = 2,
    CONTINUE = 3,
    END = 4
};

// Message Struct
struct Message
{
    MessageType message_type;
    std::vector<float> samples;

    // Serialize Message to Binary Format
    std::vector<uint8_t> serialize() const
    {
        uint64_t count = samples.size();
        size_t size = 1 + sizeof(uint64_t) + count * sizeof(float);
        std::vector<uint8_t> buffer(size);

        buffer[0] = static_cast<uint8_t>(message_type);
        std::memcpy(buffer.data() + 1, &count, sizeof(uint64_t));
        std::memcpy(buffer.data() + 1 + sizeof(uint64_t), samples.data(), count * sizeof(float));

        return buffer;
    }

    // Deserialize Message from Binary Format
    static Message deserialize(const std::vector<uint8_t> &data)
    {
        if (data.size() < (1 + sizeof(uint64_t)))
            throw std::runtime_error("Invalid data size");

        MessageType message_type = static_cast<MessageType>(data[0]);
        uint64_t count;
        std::memcpy(&count, data.data() + 1, sizeof(uint64_t));

        std::vector<float> samples(count);
        if (count > 0)
        {
            std::memcpy(samples.data(), data.data() + 1 + sizeof(uint64_t), count * sizeof(float));
        }

        return {message_type, samples};
    }
};