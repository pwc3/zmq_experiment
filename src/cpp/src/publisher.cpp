#include "../include/publisher.hpp"
#include <thread>
#include <chrono>

int main()
{
    Publisher pub;
    std::cout << "C++ Publisher started..." << std::endl;

    pub.publish({MessageType::START, {1.1f, 2.2f, 3.3f}});
    std::this_thread::sleep_for(std::chrono::seconds(1));

    pub.publish({MessageType::CONTINUE, {4.4f, 5.5f}});
    std::this_thread::sleep_for(std::chrono::seconds(1));

    pub.publish({MessageType::END, {6.6f}});
    std::this_thread::sleep_for(std::chrono::seconds(1));

    pub.publish({MessageType::FULL, {}});
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "C++ Publisher finished sending data." << std::endl;
    return 0;
}
