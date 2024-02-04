#ifndef __RS485_H_ 
#define __RS485_H_

#include <string>
#include <dirent.h> //寻找Linux系统路径
using std::string;

class RS485
{
public:
    RS485();
    ~RS485();
    string FindTTYUSB();
    int Init();
};

RS485::RS485()
{
}

RS485::~RS485()
{
}

std::string RS485::FindTTYUSB()
{
    std::string devDir = "/dev";
    std::string targetString = "ttyUSB";

    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(devDir.c_str())) != nullptr)
    {
        while ((ent = readdir(dir)) != nullptr)
        {
            std::string filename(ent->d_name);
            if (filename.find(targetString) != std::string::npos)
            {
                closedir(dir);
                return devDir + "/" + filename;
            }
        }
        closedir(dir);
    }

    return ""; // 返回空字符串表示未找到
}

#endif