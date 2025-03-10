#pragma once

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
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
        // Calculate the total buffer size
        uint64_t count = samples.size();
        size_t total_size = sizeof(message_type) + sizeof(count) + count * sizeof(float);

        // Create a buffer to hold the entire message.
        std::vector<uint8_t> buffer(total_size);
        size_t offset = 0;

        // Copy the type
        std::memcpy(buffer.data() + offset, &message_type, sizeof(MessageType));
        offset += sizeof(message_type);

        // Copy the count
        std::memcpy(buffer.data() + offset, &count, sizeof(uint64_t));
        offset += sizeof(count);

        // Copy the samples
        if (count > 0)
        {
            std::memcpy(buffer.data() + offset, samples.data(), count * sizeof(float));
        }

        std::cout << "Serializing message: type=" << static_cast<int>(message_type) << " count=" << count << " samples=";
        for (const auto &sample : samples)
        {
            std::cout << sample << " ";
        }
        std::cout << std::endl;

        std::cout << "Message serialized as: ";
        for (const auto &byte : buffer)
        {
            std::cout << "\\x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
        }
        std::cout << std::endl;

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