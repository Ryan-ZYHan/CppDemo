/* 测试和宗的通讯 */


#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <map>
#include <string>
#include <dirent.h>
#include "Checkout.h"
#include "FileExtension.h"
#include "SerialPort.h"
#include "Change.h"
using namespace Change;
using namespace Checkout;
using namespace FileExtension;
using std::cout;
using std::endl;
using std::map;
using std::string;

void Connect(SerialPort _serialPort)
{
    char FlamaRS485Data[59];
    FlamaRS485Data[0] = '\x01';               // 设备号
    FlamaRS485Data[1] = '\x10';               // 写功能码
    FlamaRS485Data[2] = '\x01';               // 高地址位，写数据时固定为01
    FlamaRS485Data[3] = '\x00';               // 低地址位，从0开始
    FlamaRS485Data[4] = '\x00';               // 数据个数高地址位
    FlamaRS485Data[5] = '\x19';               // 数据个数抵地址位，25个寄存器都写
    FlamaRS485Data[6] = '\x32';               // 字节数，数据个数的两倍，50
    FlamaRS485Data[(2 * 0) + 7] = '\x03';     // 波特率,0：地址，7：偏移，1：低地址
    FlamaRS485Data[(2 * 0) + 1 + 7] = '\x01'; // 设备号
    FlamaRS485Data[(2 * 1) + 7] = '\x01';     // 设置为外部通讯控制
    FlamaRS485Data[(2 * 1) + 1 + 7] = '\x01'; // 设置通讯模拟 枪开关控制
    for (uint i = 2; i < 25; i++)
    {
        FlamaRS485Data[(2 * i) + 7] = '\x00';
        FlamaRS485Data[(2 * i) + 1 + 7] = '\x00';
    }
    FlamaRS485Data[57] = '\x5f';
    FlamaRS485Data[58] = '\x6a';
    int writeSize = _serialPort.write(FlamaRS485Data, 59);
    cout << "writeSize:" << writeSize << endl;
}

void ReadData(SerialPort _serialPort,int startAddress,int byteSize)
{
    cout << "startAddress = " << startAddress << ",byteSize = " << byteSize << endl ;
    char writeData[] = {'\x01', '\x03', '\x00', startAddress, '\x00', byteSize, '\x84', '\x05'};
    uint8_t crc[2];
    Checkout::CalculateCRC(writeData, 6, crc);
    writeData[6] = static_cast<char>(crc[0]);
    writeData[7] = static_cast<char>(crc[1]);
    int writeSize = _serialPort.write(writeData, 8);
    cout << "writeSize:" << writeSize << endl;
    usleep(100 * 1000);
    char readData[47];
    int readSize = _serialPort.read(readData, 47);
    cout << "readSize:" << readSize << endl;
    if(readSize >0)
    {
        cout << "result:";
        for (int i=0;i<readSize;i++)
        {
            cout << Int2Hex(static_cast<int>(readData[i])) << ",";
        }
        cout << endl;
    }
}

void ReadAllData(SerialPort _serialPort)
{
    char writeData[] = {'\x01', '\x03', '\x00', '\x00', '\x00', '\x15', '\x84', '\x05'};
    int writeSize = _serialPort.write(writeData, 8);
    cout << "writeSize:" << writeSize << endl;
    usleep(100 * 1000);
    char readData[47];
    int readSize = _serialPort.read(readData, 47);
    cout << "readSize:" << readSize << endl;
    if(readSize >0)
    {
        cout << "result:";
        for (int i=0;i<readSize;i++)
        {
            cout << Int2Hex(static_cast<int>(readData[i])) << ",";
        }
        cout << endl;
    }
}

int main()
{
    std::string foundFile = findTTYUSB();

    if (!foundFile.empty())
    {
        cout << "RS485 portname = " << foundFile.c_str() << endl;
    }
    else
    {
        cout << "no usb device!" << endl;
    }
    foundFile = "/dev/" + foundFile;
    const char *port_name = foundFile.c_str();
    // const char *port_name = "/dev/ttyS1";

    SerialPort _serialPort(port_name);
    bool isOpen = _serialPort.open(); // 打开串口
    if (!isOpen)
    {
        cout << "open fail" << endl;
    }
    _serialPort.configure(9600, 8, 1, SP_PARITY_NONE); // 和宗焊机设置

    Connect(_serialPort);
    usleep(100*1000);

    ReadAllData(_serialPort);
    usleep(100*1000);

    ReadData(_serialPort,4,2);
    usleep(100*1000);    
}
