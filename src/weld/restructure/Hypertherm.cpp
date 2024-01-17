#include <dirent.h>
#include "Hypertherm.h"
#include "elog.h"
#include "HRSDK/HR_Pro.h"

int Hypertherm::OpendDevice()
{
    HR_LOG_Info("enter Hypertherm::OpendDevice");
    /* 初始化串口通信 */
    std::string foundFile = FindTTYUSB();
    if (!foundFile.empty())
    {
        HR_LOG_Info("RS485 portname = %s", foundFile.c_str());
    }
    else
    {
        HR_LOG_Error("no usb device fail. errorCode = %d.", NoUSBDevice);
        return NoUSBDevice;
    }

    const char *port_name = foundFile.c_str();
    m_serialPort.SetPortName(port_name); // 设置串口名
    bool isOpen = m_serialPort.open();   // 打开串口
    if (!isOpen)
    {
        HR_LOG_Error("RS485 connect fail. errorCode = %d.", SerialPortOpenFail);
        return SerialPortOpenFail;
    }

    m_serialPort.configure(m_baudRate, m_dataBits, m_stopBits, m_parity); // 海宝切割机串口配置
    for (int i = 0; i < m_connectMsgLength; ++i)
    {
        m_hyperthermRS485Data[i].store(":0110308000030600010FC0000066\r\n"[i]);
    }
    m_hyperthermRS485DataSize.store(m_connectMsgLength);
    m_serialPort.write(m_hyperthermRS485Data, m_hyperthermRS485DataSize);
    // 需要增加是否连接成功的判断
    HR_LOG_Info("leave Hypertherm::OpendDevice");
    return 0;
}

int Hypertherm::CloseDevice()
{
    HR_LOG_Info("enter Hypertherm::CloseDevice.");
    for (int i = 0; i < m_connectMsgLength; ++i)
    {
        m_hyperthermRS485Data[i].store(":0110308000030600000000000036\r\n"[i]);
    }
    m_hyperthermRS485DataSize.store(m_connectMsgLength);
    m_serialPort.write(m_hyperthermRS485Data, m_hyperthermRS485DataSize);
    memset(m_hyperthermRS485Data, 0, sizeof(m_hyperthermRS485Data)); // 数组清零
    m_serialPort.close();
    HR_LOG_Info("leave Hypertherm::CloseDevice.");
}

int Hypertherm::ArcOn()
{
    HR_LOG_Info("enter Hypertherm::ArcOn.");
    if(m_boxIO == "")
    {
        HR_LOG_Error("box id is not configured, errorCode = %d.",BoxIDError);
        return BoxIDError;
    }

    int nBit = m_boxIO[2] - '0';
    if (m_boxIO[0] == 'C')
    {
        HRIF_SetBoxCO(0, nBit, 1);
    }
    else
    {
        HRIF_SetBoxDO(0, nBit, 1);
    }
    HR_LOG_Info("leave Hypertherm::ArcOn.");
    return 0;
}

std::string Hypertherm::FindTTYUSB()
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