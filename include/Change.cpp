#include "Change.h"
#include <sstream>
namespace Change
{
    unsigned char Char2Hex(char c)
    {
        if (c >= '0' && c <= '9')
        {
            return c - '0';
        }
        else if (c >= 'A' && c <= 'F')
        {
            return c - 'A' + 10;
        }
        else if (c >= 'a' && c <= 'f')
        {
            return c - 'a' + 10;
        }
        return 0; // 非法字符返回0
    }

    unsigned int Char2HexForInt(char c)
    {
        if (c >= '0' && c <= '9')
        {
            return c - '0';
        }
        else if (c >= 'A' && c <= 'F')
        {
            return c - 'A' + 10;
        }
        else if (c >= 'a' && c <= 'f')
        {
            return c - 'a' + 10;
        }
        return 0; // 非法字符返回0
    }
    
    unsigned char Chars2Hex(const char *chars)
    {
        // unsigned value  = Char2HexForInt(chars[0]) *16 +Char2HexForInt(chars[1]);
        // return static_cast<char>(value);
        return (Char2Hex(chars[0]) << 4) | Char2Hex(chars[1]);
    }

    std::vector<unsigned char> Chars2Hexs(const char chars[],int chars_size)
    {
        std::vector<unsigned char> hexValues;
        for (size_t i = 0; i < chars_size / 2; ++i)
        {
            unsigned char hex = Chars2Hex(&chars[i * 2]);
            hexValues.push_back(hex);
        }
        return hexValues;
    }

    std::string Int2Hex(int value)
    {
        std::stringstream ss;
        ss << std::hex << value;
        return ss.str();
    }

   
}
