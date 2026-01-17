#include <iostream>
#include <string>
#include <cstdlib>
#include "Subnet.hpp"

bool parseSubnetInput(const std::string &input, int &isCIDR)
{
    size_t i;

    for (i = 0; i < input.size(); ++i)
    {
        char c = input[i];
        if (!((c >= '0' && c <= '9') || c == '.' || c == '/'))
        {
            std::cout << "Invalid input format." << std::endl;
            return false;
        }
    }

    if (input[0] == '/')
    {
        for (i = 1; i < input.size(); ++i)
        {
            if (!(input[i] >= '0' && input[i] <= '9'))
            {
                std::cout << "Invalid CIDR notation." << std::endl;
                return false;
            }
        }

        int cidr = std::atoi(input.substr(1).c_str());
        if (cidr < 0 || cidr > 32)
        {
            std::cout << "Invalid CIDR notation." << std::endl;
            return false;
        }

        std::cout << "CIDR notation detected: /" << cidr << std::endl;
        isCIDR = 1;
    }
    else
    {
        std::cout << "Subnet mask detected: " << input << std::endl;

        size_t dotCount = 0;
        for (i = 0; i < input.size(); ++i)
            if (input[i] == '.')
                dotCount++;

        if (dotCount != 3)
        {
            std::cout << "Invalid subnet mask format." << std::endl;
            return false;
        }

        size_t start = 0;
        size_t end = input.find('.');
        int octetCount = 0;

        while (end != std::string::npos)
        {
            std::string octetStr = input.substr(start, end - start);

            for (i = 0; i < octetStr.size(); ++i)
            {
                if (!(octetStr[i] >= '0' && octetStr[i] <= '9'))
                {
                    std::cout << "Invalid subnet mask format." << std::endl;
                    return false;
                }
            }

            int octet = std::atoi(octetStr.c_str());
            if (octet < 0 || octet > 255)
            {
                std::cout << "Invalid subnet mask format." << std::endl;
                return false;
            }

            octetCount++;
            start = end + 1;
            end = input.find('.', start);
        }

        std::string octetStr = input.substr(start);
        for (i = 0; i < octetStr.size(); ++i)
        {
            if (!(octetStr[i] >= '0' && octetStr[i] <= '9'))
            {
                std::cout << "Invalid subnet mask format." << std::endl;
                return false;
            }
        }

        int octet = std::atoi(octetStr.c_str());
        if (octet < 0 || octet > 255)
        {
            std::cout << "Invalid subnet mask format." << std::endl;
            return false;
        }

        octetCount++;
        if (octetCount != 4)
        {
            std::cout << "Invalid subnet mask format." << std::endl;
            return false;
        }

        isCIDR = 0;
    }
    return true;
}

void processCidrNotation(const std::string &input, Subnet &subnet)
{
    int cidr = std::atoi(input.substr(1).c_str());
    unsigned char bytes[4] = {0, 0, 0, 0};

    for (int i = 0; i < cidr; ++i)
        bytes[i / 8] |= (1 << (7 - (i % 8)));

    subnet.setFirstByte(bytes[0]);
    subnet.setSecondByte(bytes[1]);
    subnet.setThirdByte(bytes[2]);
    subnet.setFourthByte(bytes[3]);
}

void processSubnetMask(const std::string &input, Subnet &subnet)
{
    size_t start = 0;
    size_t end = input.find('.');
    int octetIndex = 0;

    while (end != std::string::npos)
    {
        int octet = std::atoi(input.substr(start, end - start).c_str());

        if (octetIndex == 0)
            subnet.setFirstByte((unsigned char)octet);
        else if (octetIndex == 1)
            subnet.setSecondByte((unsigned char)octet);
        else if (octetIndex == 2)
            subnet.setThirdByte((unsigned char)octet);

        octetIndex++;
        start = end + 1;
        end = input.find('.', start);
    }

    int octet = std::atoi(input.substr(start).c_str());
    subnet.setFourthByte((unsigned char)octet);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: ./subnetCounter <255.255.255.0>" << std::endl;
        std::cout << "Usage: ./subnetCounter /24" << std::endl;
        return 1;
    }

    std::string input = argv[1];
    int isCIDR = -1;

    if (!parseSubnetInput(input, isCIDR))
        return 1;

    Subnet subnet;

    if (isCIDR == 1)
        processCidrNotation(input, subnet);
    else
        processSubnetMask(input, subnet);

    printSubnetInfo(subnet);
    printSubnetSplits(subnet);
    return 0;
}
