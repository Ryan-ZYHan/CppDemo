#ifndef __FILEEXTENSION_H_
#define __FILEEXTENSION_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <dirent.h>

enum OpenMode
{
    app,//追加
};

namespace FileExtension
{
    std::ofstream OpenTxt(const std::string &txtName, OpenMode openMode); //打开txt文件

    std::string findTTYUSB(); // 寻找/dec路径下usb设备名，未找到范围空字符串
}
#endif