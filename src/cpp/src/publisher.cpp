#include "../include/publisher.hpp"

std::vector<float> generate_samples(int i)
{
    std::vector<float> samples;
    for (int f = i * 10; f < (i + 1) * 10; f++)
    {
        samples.push_back(static_cast<float>(f));
    }
    return samples;
}

int main()
{
    Publisher pub;
    std::cout << "Created publisher" << std::endl;

    for (int i = 0; i < 10; i++)
    {
        MessageType type;
        if (i == 0)
        {
            type = MessageType::START;
        }
        else if (i == 9)
        {
            type = MessageType::END;
        }
        else
        {
            type = MessageType::CONTINUE;
        }

        std::cout << "Publishing message " << i << std::endl;
        pub.publish({type, generate_samples(i)});
        std::cout << "Published message " << i << std::endl;
    }

    std::cout << "Done" << std::endl;
    return 0;
}
