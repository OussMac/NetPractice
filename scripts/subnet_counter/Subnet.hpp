#ifndef SUBNET_HPP
#define SUBNET_HPP

#include <string>
#include <iostream>

class Subnet {
private:
    unsigned char first_byte;
    unsigned char second_byte;
    unsigned char third_byte;
    unsigned char fourth_byte;
public:
    Subnet();
    ~Subnet();
    void setFirstByte(unsigned char byte) { first_byte = byte; }
    unsigned char getFirstByte() const { return first_byte; }
    void setSecondByte(unsigned char byte) { second_byte = byte; }
    unsigned char getSecondByte() const { return second_byte; }
    void setThirdByte(unsigned char byte) { third_byte = byte; }
    unsigned char getThirdByte() const { return third_byte; }
    void setFourthByte(unsigned char byte) { fourth_byte = byte; }
    unsigned char getFourthByte() const { return fourth_byte; }
};

void printSubnetInfo(const Subnet &subnet);
void printSubnetSplits(const Subnet &subnet);

#endif // SUBNET_HPP