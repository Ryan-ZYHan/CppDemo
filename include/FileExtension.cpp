#include "FileExtension.h"

namespace FileExtension
{
    std::ofstream OpenTxt(const std::string &txtName, OpenMode openMode)
    {
        std::ofstream outputFile;
        switch (openMode)
        {
        case app:
            outputFile.open(txtName, std::ios::app);
            break;
        default:
            break;
        }

        // 检查文件是否成功打开
        if (outputFile.is_open())
        {
            return outputFile;
        }
        else
        {
            std::cout << "Unable to open file for writing." << std::endl;
            return std::ofstream(); // 返回默认构造的 ofstream 对象
        }
    }

    std::string findTTYUSB()
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
                    return filename;
                }
            }
            closedir(dir);
        }
        else
        {
        }

        return ""; // 返回空字符串表示未找到
    }
}