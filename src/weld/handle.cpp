#include <iostream>
#include <algorithm>
#include <map>
#include <array>
#include <thread>
#include <chrono>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <bitset>
#include <iostream>
#include <nlohmann/json.hpp>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "HRSDK/HR_Pro.h"
#include "HRSDK/HR_RobotStruct.h"
using json = nlohmann::json;

std::string m_ipAddress = "10.20.60.182";
int port = 10004;
int buttonIndex = 0;
int endDO[8] = {0, 0, 0, 0, 0, 0, 0, 0};
std::vector<int> buttonDefault = {1, 1, 1, 1};
std::vector<int> button1 = {0, 1, 1, 1};
std::vector<int> button2 = {1, 0, 1, 1};
std::vector<int> button3 = {0, 0, 1, 1};
std::vector<int> button4 = {1, 1, 0, 1};
std::vector<int> button5 = {0, 1, 0, 1};
std::vector<int> button6 = {1, 0, 0, 1};

std::map<int, std::vector<int>> buttonMap{
    {1, button1},
    {2, button2},
    {3, button3},
    {4, button4},
    {5, button5},
    {6, button6}};

int GetButtonPressedIndexOf6ButtonHandleForPro(std::vector<int> endDI)
{
    for (int i = 1; i < 7; i++)
    {
        if (endDI == buttonMap[i])
        {
            cout << "第" << i << "个按钮被按下" << endl;
            return i;
        }
    }
    return -1; // 组合键或未知情况
}

void SetEndDO()
{
    // cout << "writeDO" << endDO[0] << "," << endDO[1] << "," << endDO[2] << "," << endDO[3] << ","
    //      << endDO[4] << "," << endDO[5] << "," << endDO[6] << "," << endDO[7] << "," << endl;
    HRIF_SetEndDO(0, 0, 2, 0); // 锁存线置低
    for (int i = 0; i < 8; i++)
    {
        HRIF_SetEndDO(0, 0, 1, endDO[i]); // 置数据位
        HRIF_SetEndDO(0, 0, 0, 1);        // 时钟线置高
        HRIF_SetEndDO(0, 0, 0, 0);        // 时钟线置低
    }
    HRIF_SetEndDO(0, 0, 2, 1); // 锁存线置高
}

void HandleFunc(std::vector<int> endDI)
{
    if (endDI == buttonDefault) // 如果信号是松开的时候
    {
        if (buttonIndex > 0)
        {
            cout << "第" << buttonIndex << "个按钮松开" << endl;
            for (int i = 0; i < 8; i++)
            {
                endDO[i] = 0;
            }
            SetEndDO();
        }

        switch (buttonIndex)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            break;
        }
        buttonIndex = 0;
    }
    else // 如果按下
    {
        buttonIndex = GetButtonPressedIndexOf6ButtonHandleForPro(endDI);
        if (buttonIndex > 0)
        {
            endDO[8 - buttonIndex] = 1;
            SetEndDO();
        }

        switch (buttonIndex)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default:
            break;
        }
    }
}

bool SocketConnect(int &sockfd)
{
    const char *serverIP = m_ipAddress.c_str();
    int portNumber = port;
    cout << "IP = " << m_ipAddress.c_str() << ", port = " << portNumber << endl;

    // 关闭现有的套接字连接（如果存在）
    if (sockfd != -1)
    {
        close(sockfd);
    }

    // 创建新的套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        // 处理套接字创建失败的情况
        // HR_LOG_Info( "Create Socket Error!");
        return false;
    }

    // 连接到服务器端
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portNumber);
    if (inet_pton(AF_INET, serverIP, &(serverAddr.sin_addr)) <= 0)
    {
        // HR_LOG_Info( "Invalid IP Address!");
        close(sockfd);
        return false;
    }

    int connectResult = connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (connectResult == -1)
    {
        // 处理连接失败的情况
        // HR_LOG_Info( "Socket Connect Error!");
        close(sockfd); // 关闭新套接字
        return false;
    }

    return true;
}

bool ReceiveDataFromSocket(int &sockfd, _ST_RTInfo &info)
{
    try
    {
        // 两倍的内存
        int bufferSize = 2 * sizeof(info);
        char buffer[bufferSize];
        // 接收数据
        ssize_t bytesRead = recv(sockfd, buffer, bufferSize, 0);
        if (bytesRead == -1)
        {
            if (!SocketConnect(sockfd))
            {
                // m_subscribedTag = -1;
                return false;
            }
        }

        // 拆解包
        int dataSizeOffset = 8; // 数据长度的位置在第9到第12字节
        int dataByteSize = 4;   // 四个字节用于存数据长度
        if (bytesRead < dataSizeOffset + dataByteSize)
        {
            // std::cerr << "Invalid packet" << std::endl;
            // close(sockfd);
            return false;
        }

        // 获得包头位置(使用int指针查找)
        std::bitset<32> searchBitset("00000000000000000000000001001100"); // "LTBR"的二进制表示
        // int* intBuffer = reinterpret_cast<int*>(buffer); // 将buffer转换为int指针
        int headerOffset = -1; // 未找到"LTBR"字符串
        for (int i = 0; i < bufferSize / sizeof(int); i++)
        {
            std::bitset<32> byteBitset(static_cast<unsigned char>(buffer[i]));
            if (byteBitset == searchBitset)
            {
                headerOffset = i * sizeof(int);
                break;
            }
        }
        if (headerOffset == -1)
        {
            return false;
        }
        // std::cout << "headerOffset int:" << headerOffset2 << std::endl;

        // 获取数据长度
        int dataSize; // 数据长度
        if (bytesRead < headerOffset + dataSizeOffset + dataByteSize)
        {
            // std::cout << "数据缺失，没有数据长度" << std::endl;
            return false;
        }
        std::memcpy(&dataSize, buffer + headerOffset + dataSizeOffset, dataByteSize);
        // std::cout << "dataSize:" << dataSize << std::endl;

        if (bytesRead < headerOffset + dataSizeOffset + dataByteSize + dataSize)
        {
            // std::cout   << "数据不完整"
            //             << "bytesRead: " << bytesRead
            //             << "headerOffset" << headerOffset
            //             << "dataSizeOffset" << dataSizeOffset
            //             << "dataByteSize" << dataByteSize
            //             << "dataSize" << dataSize
            //             <<  std::endl;
            // close(sockfd);
            return false;
        }

        if (dataSize < 0)
        {
            cout << "datasize < 0" << endl;
            return false;
        }
        // else
        // {
        //     cout << "datasize = " << dataSize << endl;
        // }
        // dataSize = 872;
        // 存储数据到结构体
        std::memcpy(&info, buffer + headerOffset + dataSizeOffset + dataByteSize, dataSize);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool RecevieJsonEndDIFromSocket(int &sockfd, std::vector<int> &endDI)
{
    char buffer[4096]; // 缓冲区大小

    // 从套接字读取数据
    int bytesRead = read(sockfd, buffer, sizeof(buffer));
    if (bytesRead <= 0)
    {
        std::cerr << "Error reading data" << std::endl;
        return false;
    }
    // 复制从第12个位置开始的数据到新的缓冲区
    int startPos = 12;                        // 起始位置
    int newDataLength = bytesRead - startPos; // 需要复制的数据长度
    // for(int i=3000;i<bytesRead;i++)
    // {
    //     std::cout << buffer[i] << "," ;
    // }
    // std::cout  << "buffer over"<< endl;

    // 将接收到的数据转换为字符串
    std::string receivedData(buffer+startPos, newDataLength);
    // 解析 JSON 数据
    try
    {
        json jsonData = json::parse(receivedData);

        // 获取 EndIO 对象
        auto endIO = jsonData["EndIO"];

        // 获取 EndDI 数组
        auto EndDI = endIO["EndDI"];

        // 打印 EndDI 数组的内容
        // std::cout << "EndDI: " << EndDI.dump() << std::endl;

        endDI = EndDI.get<std::vector<int>>();

        return true;
    }
    catch (const json::parse_error &e)
    {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return false;
    }
}

// int main()
// {
//     HRIF_Connect(0, m_ipAddress.c_str(), 10003);
//     // for(int i=2;i<8;i++)
//     // {
//     //     // endDO[i] = 1;
//     //     endDO[2] = 1;
//     //     SetEndDO();
//     //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
//     // }

//     int sockfd = 0;
//     if (!SocketConnect(sockfd))
//     {
//         // m_subscribedTag = -1;
//         cout << "socket error!" << endl;
//         return 0;
//     }

//     while (true)
//     {
//         // std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 读取数据的固定周期时间

//         _ST_RTInfo robotInfo; // 获取机器人状态信息
//         if (ReceiveDataFromSocket(sockfd, robotInfo))
//         {
//             std::vector<int> endDIVec(std::begin(robotInfo.m_RT_EndIO.nrEndDI), std::end(robotInfo.m_RT_EndIO.nrEndDI));
//             // cout << "readDI" << endDIVec[0] << "," << endDIVec[1] << "," << endDIVec[2] << "," << endDIVec[3] << "," << endl;
//             HandleFunc(endDIVec);
//             // cout << "writeDO" << endDO[0] << "," << endDO[1] << "," << endDO[2] << "," << endDO[3] << ","
//             //      << endDO[4] << "," << endDO[5] << "," << endDO[6] << "," << endDO[7] << "," << endl;
//             // cout << "readDO" << robotInfo.m_RT_EndIO.nrEndDO[0] << "," << robotInfo.m_RT_EndIO.nrEndDO[1] << ","
//             //      << robotInfo.m_RT_EndIO.nrEndDO[2] << "," << robotInfo.m_RT_EndIO.nrEndDO[3] << "," << endl;
//         }
//         else
//         {
//             continue;
//         }
//     }

//     // 关闭套接字
// close(sockfd);
// }
/*---------------------------------------------------------------------------------------------------------*/

int main()
{
    HRIF_Connect(0, m_ipAddress.c_str(), 10003);

    int sockfd = 0;
    if (!SocketConnect(sockfd))
    {
        cout << "socket error!" << endl;
        return 0;
    }

    while (true)
    {
        // std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 读取数据的固定周期时间
        std::vector<int> endDIVec;
        if (RecevieJsonEndDIFromSocket(sockfd, endDIVec))
        {
            // std::vector<int> endDIVec(std::begin(robotInfo.m_RT_EndIO.nrEndDI), std::end(robotInfo.m_RT_EndIO.nrEndDI));
            // cout << "readDI" << endDIVec[0] << "," << endDIVec[1] << "," << endDIVec[2] << "," << endDIVec[3] << "," << endl;
            HandleFunc(endDIVec);
            // cout << "writeDO" << endDO[0] << "," << endDO[1] << "," << endDO[2] << "," << endDO[3] << ","
            //      << endDO[4] << "," << endDO[5] << "," << endDO[6] << "," << endDO[7] << "," << endl;
            // cout << "readDO" << robotInfo.m_RT_EndIO.nrEndDO[0] << "," << robotInfo.m_RT_EndIO.nrEndDO[1] << ","
            //      << robotInfo.m_RT_EndIO.nrEndDO[2] << "," << robotInfo.m_RT_EndIO.nrEndDO[3] << "," << endl;
        }
        else
        {
            continue;
        }
    }

    // 关闭套接字
    close(sockfd);
}