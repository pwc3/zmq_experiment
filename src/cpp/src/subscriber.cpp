#include "../include/subscriber.hpp"

int main()
{
    Subscriber sub;
    std::cout << "C++ Subscriber started..." << std::endl;

    while (true)
    {
        Message message = sub.subscribe();
        std::cout << "Received: Type=" << static_cast<int>(message.message_type)
                  << ", Count=" << message.samples.size()
                  << ", Values={";

        for (size_t i = 0; i < message.samples.size(); ++i)
        {
            std::cout << message.samples[i] << (i < message.samples.size() - 1 ? ", " : "");
        }
        std::cout << "}" << std::endl;
    }

    return 0;
}