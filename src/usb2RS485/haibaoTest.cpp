#include "FileExtension.h"
#include "Change.h"
#include "Checkout.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
using namespace FileExtension;
using namespace Change;
using namespace Checkout;
int main()
{
    /* 计算LRC */
    char yuanchengkongzhi[] = {':','0','1','1','0','3','0','8','0','0','0','0','3','0','6','0',
    '0','0','1','0','F','C','0','0','0','0','0','6','6','\r','\n'};
    char newyuanchengkongzhi[26];
    std::memcpy(newyuanchengkongzhi,yuanchengkongzhi+1,26);
    // newyuanchengkongzhi[26] = '\0';
    std::vector<unsigned char> hexs = Chars2Hexs(newyuanchengkongzhi,sizeof(newyuanchengkongzhi));
    unsigned char lrc_hex = CalculateLRC(hexs);
    std::stringstream ss;
    ss << std::hex << static_cast<uint16_t>(CalculateLRC(hexs));
    std::cout << "LRC=0x" << lrc_hex << std::endl;
    std::cout << "LRC=0x" << ss.str() << std::endl;

    /* 转16进制 */
    int num = 4160;
    std::string hexStr = Int2Hex(num);
    return 0;
}