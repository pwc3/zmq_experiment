#include <iostream>
#include <string>

#include "Publisher.hpp"
#include "Subscriber.hpp"

std::vector<float> generate_samples(int i);
void run_publisher();
void run_subscriber();

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <pub|sub>" << std::endl;
        return 1;
    }

    std::string mode = argv[1];

    if (mode == "pub")
    {
        run_publisher();
    }
    else if (mode == "sub")
    {
        run_subscriber();
    }
    else
    {
        std::cerr << "Invalid argument: " << mode << std::endl;
        std::cerr << "Usage: " << argv[0] << " <pub|sub>" << std::endl;
        return 1;
    }

    return 0;
}

std::vector<float> generate_samples(int i)
{
    std::vector<float> samples;
    for (int f = i * 10; f < (i + 1) * 10; f++)
    {
        samples.push_back(static_cast<float>(f));
    }
    return samples;
}

void run_publisher()
{
    Publisher pub;
    std::cout << "Created publisher" << std::endl;

    for (int i = 0; i < 10; i++)
    {
        std::ostringstream filename;
        filename << "test-" << std::setw(2) << std::setfill('0') << i << ".wav";

        AudioPacket packet(
            std::filesystem::path(filename.str()),
            generate_samples(i));

        std::cout << "Publishing packet " << i << std::endl;
        pub.publish(packet);
        std::cout << "Published packet " << i << std::endl;
    }
}

void run_subscriber()
{
    Subscriber sub;
    std::cout << "Created subscriber" << std::endl;

    sub.subscribe(
        [](const AudioPacket &packet)
        {
            std::cout << "Received packet: wav_file="
                      << packet.get_wav_file().string()
                      << ", samples={";

            auto size = packet.get_samples().size();
            for (size_t i = 0; i < size; ++i)
            {
                bool has_more = i < size - 1;
                std::cout << packet.get_samples()[i] << (has_more ? ", " : "");
            }

            std::cout << "}" << std::endl;
            return true;
        });
}