#ifndef __CHANGE_H_
#define __CHANGE_H_
#include <iostream>
#include <vector>
#include <string>
namespace Change
{
    unsigned char Char2Hex(char c); //将0-f的字符转换成16进制
    unsigned int Char2HexForInt(char c); //将0-f的字符转换成16进制，返回int
    unsigned char Chars2Hex(const char* chars);// 将两个字符转换为一个十六进制数
    std::vector<unsigned char> Chars2Hexs(const char chars[],int chars_size); // 将一个字符数组每两位转成一个16进制数，返回一个16进制数组
    std::string Int2Hex(int value); //将10进制转位16进制
}
#endif