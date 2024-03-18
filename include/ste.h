#ifndef __STE_H_
#define __STE_H_

#include <vector>
#include <string>

namespace ste 
{
    /*
        @brief 根据符号将字符串分段
        @param s 待分割字符串
        @param delimiter 分割符
        @return 字符串容器
    */
    std::vector<std::string> SplitString(const std::string& s, char delimiter) ;
}
#endif