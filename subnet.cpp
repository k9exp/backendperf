#include <array>
#include <cstdint>
#include <iostream>

typedef std::array<uint8_t, 4> FourByte;

struct NetworkConfiguration {
    FourByte subnet_mask;
    FourByte ip_address;
    // FourByte default_gateway;
};

int main(){
    NetworkConfiguration sender {
        {255, 255, 255, 0}, // subnet mask
        {192, 168, 34, 1}, // ip address
    };

    NetworkConfiguration receiver {
        {255, 255, 255, 0}, // subnet mask
        {192, 168, 34, 2}, // ip address
    };

    auto find_network = [](const NetworkConfiguration &config) -> FourByte {
        return {
           (uint8_t) (config.subnet_mask[0] & config.ip_address[0]),
           (uint8_t) (config.subnet_mask[1] & config.ip_address[1]),
           (uint8_t) (config.subnet_mask[2] & config.ip_address[2]),
           (uint8_t) (config.subnet_mask[3] & config.ip_address[3]),
        };
    };

    std::cout << (
        find_network(sender) == find_network(receiver) ?
        "They belong to same subnet - Send data directly using MAC Address" :
        "They are in different subnets - Consult Default Gateway to go to router and find IP address..."
    ) << std::endl;

    return 0;
}
