#include <iostream>
#include <nlohmann/json.hpp>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using json = nlohmann::json;

std::string m_ipAddress = "10.20.60.140";
int port = 10004;



int main()
{
    int sockfd;
    struct sockaddr_in serverAddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "Error in socket creation" << std::endl;
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, m_ipAddress.c_str(), &serverAddr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Error in connection" << std::endl;
        return -1;
    }

    char buffer[4096]; // 缓冲区大小

    // 从套接字读取数据
    int bytesRead = read(sockfd, buffer, sizeof(buffer));
    // for (int i = 2400; i < 2494; i++)
    // {
    //     std::cout << buffer[i] << ",";
    // }
    if (bytesRead <= 0)
    {
        std::cerr << "Error reading data" << std::endl;
        return -1;
    }
    // 复制从第12个位置开始的数据到新的缓冲区
    int startPos = 12;                   // 起始位置
    int newDataLength = bytesRead - startPos; // 需要复制的数据长度
    char newBuffer[2482]; // 新的缓冲区，存储特定位置的数据
    std::memcpy(newBuffer, buffer + startPos, newDataLength);
    // std::cout << newBuffer[2481] << ",";
    // 解析 JSON 数据
    try
    {
        json jsonData = json::parse(newBuffer);

        // 获取 EndIO 对象
        auto endIO = jsonData["EndIO"];

        // 获取 EndDI 数组
        auto endDI = endIO["EndDI"];

        // 打印 EndDI 数组的内容
        std::cout << "EndDI: " << endDI.dump() << std::endl;
    }
    catch (const json::parse_error &e)
    {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }

    // 关闭套接字连接
    close(sockfd);

    return 0;
}
