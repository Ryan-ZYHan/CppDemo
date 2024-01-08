#include "SerialPort.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <map>
using std::cout;
using std::endl;
using std::map;
using std::string;

// 正确的返回值：8B 9F 9D 67 2E EE EE 3E 9F 9F 9F 99 99 79 79 7D

int main()
{
    // 打开一个文本文件以写入方式
    std::ofstream outputFile("output.txt", std::ios::app);

    // 检查文件是否成功打开
    if (outputFile.is_open())
    {
    }
    else
    {
        std::cout << "Unable to open file for writing." << std::endl;
    }

    // 和宗命令
    map<string, string> hezongCMD =
        {
            {"readWeldCurrent", "\x01\x03\x00\x04\x00\x02\x85\xCA"},

        };

    int nRet = 0;
    const char *port_name = "/dev/ttyUSB0";
    SerialPort serialPort(port_name);
    bool isOpen = serialPort.open();
    // serialPort.configure(19200, 8, 1, SP_PARITY_EVEN);//海宝切割机
    serialPort.configure(9600, 8, 1, SP_PARITY_NONE); // 和宗焊机

    // const char *readdenglizi = ":010430100003B8\r\n";
    // const char *yuanchengkongzhi = ":0110308000030600010FC0000066\r\n";
    // const char *tuichuyuancheng = ":0110308000030600000000000036\r\n";
    // // const char *writeData = yuanchengkongzhi;
    // const char *writeData = readdenglizi;
    // // const char *writeData = tuichuyuancheng;
    // // std::string cur = "远程控制";
    // std::string cur = "读取等离子电源输出";
    // // std::string cur= "退出远程控制";
    string cmd = "readWeldCurrent";
    string order = "\x01\x03\x00\x04\x00\x02\x85\xCA";
    const char writeData2[] = { 1, 3, 0, 4, 0, 2, static_cast<char>(133), static_cast<char>(202) };
    const char *writeData = writeData2;
    outputFile << "cmd:" << cmd << endl;
    cout << "cmd:" << cmd << endl;
    cout << "order:" << order << endl;

    // size_t dataSize = strlen(writeData);
    size_t dataSize = sizeof(writeData);
    nRet = serialPort.write(writeData, dataSize);
    cout << "write size:" << nRet << endl;

    char readData[100];
    unsigned char unsignedReadData[100];
    int intVar[100];
    nRet = serialPort.read(readData, 100);
    cout << "read size:" << dataSize << endl;//如果是海宝就是nret
    // cout << "recv dataSize:" << dataSize << endl;

    for (uint i = 0; i < nRet; i++)
    {
        unsigned char unsignedCharVar = static_cast<unsigned char>(readData[i]);
        unsignedReadData[i] = unsignedCharVar;
        int val = static_cast<int>(unsignedCharVar);
        intVar[i] = val;
        cout << "result:" << unsignedCharVar << "," << val << "," << std::hex << std::setfill('0') << std::setw(2) << intVar[i] << endl;
        // 将整数值写入文件
        outputFile << val << ",";
    }
    outputFile << endl;
    for (uint i = 0; i < nRet; i++)
    {
        outputFile << std::hex << std::setfill('0') << std::setw(2) << intVar[i] << " ";
    }
    outputFile << endl;

    // 关闭文件流
    outputFile.close();
    serialPort.close();
}
