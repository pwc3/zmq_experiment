#include "../include/subscriber.hpp"

int main()
{
    Subscriber sub;
    std::cout << "Created subscriber" << std::endl;

    while (true)
    {
        Message message = sub.subscribe();
        std::cout << "Received: type=" << static_cast<int>(message.message_type)
                  << ", count=" << message.samples.size()
                  << ", values={";

        for (size_t i = 0; i < message.samples.size(); ++i)
        {
            std::cout << message.samples[i] << (i < message.samples.size() - 1 ? ", " : "");
        }

        std::cout << "}" << std::endl;

        if (message.message_type == MessageType::END)
        {
            std::cout << "Received END message, stopping" << std::endl;
            break;
        }
    }

    return 0;
}
