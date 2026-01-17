#include "Subnet.hpp"

static int calculateCIDR(const Subnet &subnet)
{
    unsigned char bytes[4] = {
        subnet.getFirstByte(),
        subnet.getSecondByte(),
        subnet.getThirdByte(),
        subnet.getFourthByte()
    };

    int cidr = 0;
    for (int i = 0; i < 4; ++i)
    {
        for (int bit = 7; bit >= 0; --bit)
            cidr += (bytes[i] >> bit) & 1;
    }
    return cidr;
}

static void printByteBinary(unsigned char byte)
{
    for (int i = 7; i >= 0; --i)
        std::cout << ((byte >> i) & 1);
}

void printSubnetInfo(const Subnet &subnet)
{
    unsigned char b1 = subnet.getFirstByte();
    unsigned char b2 = subnet.getSecondByte();
    unsigned char b3 = subnet.getThirdByte();
    unsigned char b4 = subnet.getFourthByte();

    int cidr = calculateCIDR(subnet);

    std::cout << "\n================ SUBNET INFO ================\n\n";

    std::cout << "Decimal mask : "
              << static_cast<int>(b1) << "."
              << static_cast<int>(b2) << "."
              << static_cast<int>(b3) << "."
              << static_cast<int>(b4) << std::endl;

    std::cout << "CIDR notation: /" << cidr << "\n\n";

    std::cout << "Binary mask  :\n";
    printByteBinary(b1); std::cout << ".";
    printByteBinary(b2); std::cout << ".";
    printByteBinary(b3); std::cout << ".";
    printByteBinary(b4); std::cout << std::endl;

    std::cout << "\n=============================================\n";
}
