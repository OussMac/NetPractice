#include <iostream>
#include "Subnet.hpp"

static int countCIDR(const Subnet &subnet)
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

void printSubnetSplits(const Subnet &subnet)
{
    int cidr = countCIDR(subnet);

    int baseCidr = 24;

    if (cidr <= baseCidr)
        return;

    int borrowedBits = cidr - baseCidr;
    int subnetCount = 1 << borrowedBits;

    std::cout << "\n=========== SUBNET SPLIT VISUAL ===========\n\n";
    std::cout << "CIDR: /" << cidr << std::endl;
    std::cout << "Borrowed bits from host: " << borrowedBits << std::endl;
    std::cout << "Number of subnets: " << subnetCount << "\n\n";

    std::cout << "Network split (binary):\n\n";

    for (int i = 0; i < subnetCount; ++i)
    {
        for (int bit = borrowedBits - 1; bit >= 0; --bit)
            std::cout << ((i >> bit) & 1);

        for (int j = 0; j < 8 - borrowedBits; ++j)
            std::cout << "x";

        std::cout << std::endl;
    }

    std::cout << "\nEach added bit:\n";
    std::cout << "- doubles the number of networks\n";
    std::cout << "- halves the host range\n";
    std::cout << "- creates a real boundary\n";

    std::cout << "\n==========================================\n";
}
