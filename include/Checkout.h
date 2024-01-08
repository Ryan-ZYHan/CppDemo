#ifndef __CHECKOUT_H_
#define __CHECKOUT_H_
#include <iostream>
#include <vector>
namespace Checkout
{
    unsigned char CalculateLRC(const std::vector<unsigned char> &data); // 计算LRC码

    void CalculateCRC(const char data[], size_t size, uint8_t result[2]); // CRC-16算法

    void splitCRC(uint16_t crc, uint8_t result[2]); // 将CRC结果拆分为低八位和高八位，存储在int数组中
}

#endif