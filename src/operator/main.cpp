#include <iostream>
#include <cstdint>
#include <bitset>

int BitOperat()
{
    uint8_t data = 0b10100000;
    uint8_t mask =0b00001000;
    uint8_t result = data | mask;

    // 输出结果
    std::cout << "Original data: " << std::bitset<8>(data) << std::endl; // 输出原始数据
    std::cout << "Mask:          " << std::bitset<8>(mask) << std::endl; // 输出掩码
    std::cout << "Result:        " << std::bitset<8>(result) << std::endl; // 输出结果
}

int main()
{
    BitOperat();
    return 0;
}