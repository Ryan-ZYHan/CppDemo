#include <dirent.h>
#include "HyperthermRS485.h"
#include "elog.h"
#include "HRSDK/HR_Pro.h"

HyperthermRS485::HyperthermRS485()
{

}

HyperthermRS485::~HyperthermRS485()
{
    
}

int HyperthermRS485::OpendDevice()
{
    HR_LOG_Info("enter HyperthermRS485::OpendDevice");
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
    HR_LOG_Info("leave HyperthermRS485::OpendDevice");
    return 0;
}

int HyperthermRS485::CloseDevice()
{
    HR_LOG_Info("enter HyperthermRS485::CloseDevice.");
    for (int i = 0; i < m_connectMsgLength; ++i)
    {
        m_hyperthermRS485Data[i].store(":0110308000030600000000000036\r\n"[i]);
    }
    m_hyperthermRS485DataSize.store(m_connectMsgLength);
    m_serialPort.write(m_hyperthermRS485Data, m_hyperthermRS485DataSize);
    memset(m_hyperthermRS485Data, 0, sizeof(m_hyperthermRS485Data)); // 数组清零
    m_serialPort.close();
    HR_LOG_Info("leave HyperthermRS485::CloseDevice.");
}

int HyperthermRS485::ArcOn()
{
    HR_LOG_Info("enter HyperthermRS485::ArcOn.");
    if (m_boxIO == "")
    {
        HR_LOG_Error("box id is not configured, errorCode = %d.", BoxIDError);
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
    HR_LOG_Info("leave HyperthermRS485::ArcOn.");
    return 0;
}

int HyperthermRS485::ArcOff()
{
    HR_LOG_Info("enter HyperthermRS485::ArcOff.");
    if (m_boxIO == "")
    {
        HR_LOG_Error("box id is not configured, errorCode = %d.", BoxIDError);
        return BoxIDError;
    }

    int nBit = m_boxIO[2] - '0';
    if (m_boxIO[0] == 'C')
    {
        HRIF_SetBoxCO(0, nBit, 0);
    }
    else
    {
        HRIF_SetBoxDO(0, nBit, 0);
    }
    HR_LOG_Info("leave HyperthermRS485::ArcOff.");
    return 0;
}

int HyperthermRS485::StartFlow()
{
    HR_LOG_Info("enter HyperthermRS485::StartFlow.");
    for (int i = 0; i < m_flowMsgLength; i++)
    {
        m_hyperthermRS485Data[i].store(":01053180FF004A\r\n"[i]);
    }
    m_hyperthermRS485DataSize.store(m_flowMsgLength);
    m_serialPort.write(m_hyperthermRS485Data, m_flowMsgLength);
    HR_LOG_Info("leave HyperthermRS485::StartFlow.");
    return 0;
}

int HyperthermRS485::StopFlow()
{
    HR_LOG_Info("enter HyperthermRS485::StopFlow.");

    for (int i = 0; i < m_flowMsgLength; i++)
    {
        m_hyperthermRS485Data[i].store(":01053180000049\r\n"[i]);
    }
    m_hyperthermRS485DataSize.store(m_flowMsgLength);
    m_serialPort.write(m_hyperthermRS485Data, m_flowMsgLength);

    HR_LOG_Info("leave HyperthermRS485::StopFlow.");
    return 0;
}

void HyperthermRS485::DataCollection()
{
    ReadFault();
    ReadCurrent();
}

int HyperthermRS485::DeviceCheck()
{
    m_serialPort.write(m_hyperthermRS485Data,m_hyperthermRS485DataSize.load());
    if(m_currentMonitoringFlag)
    {
        bool state = MonitorCurrent();
    }
}

int HyperthermRS485::StartPushWire()
{
    HR_LOG_Error("Hypertherm::StartPushWire : hyperterm whhitout this function.");
    return 0;
}
int HyperthermRS485::StopPushWire()
{
    HR_LOG_Error("Hypertherm::StopPushWire : hyperterm whhitout this function.");
    return 0;
}
int HyperthermRS485::StartPullWire()
{
    HR_LOG_Error("Hypertherm::StartPullWire : hyperterm whhitout this function.");
    return 0;
}
int HyperthermRS485::StopPullWire()
{
    HR_LOG_Error("Hypertherm::StopPullWire : hyperterm whhitout this function.");
    return 0;
}

int HyperthermRS485::GetFault()
{
    return m_fault;
}

double HyperthermRS485::GetCurrent()
{
    return m_current;
}

std::string HyperthermRS485::FindTTYUSB()
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

int HyperthermRS485::ReadFault()
{
    char faultwrite[17];
    for (int i = 0; i < 17; i++)
    {
        faultwrite[i] = ":0104301A0001B0\r\n"[i];
    }
    m_serialPort.write(faultwrite, 17);

    char falutData[100];
    int readSize;
    readSize = m_serialPort.read(falutData, 100);

    char faultChar[4];
    memcpy(faultChar, falutData + 7, 4);
    unsigned int fault = strtoul(faultChar, nullptr, 16);
    m_fault = fault;
}

int HyperthermRS485::ReadCurrent()
{
    char write[17];
    for (int i = 0; i < 17; i++)
    {
        write[i] = ":010430180002B1\r\n"[i];
    }
    m_serialPort.write(write, 17);

    char readData[100];
    int readSize = m_serialPort.read(readData, 100);

    char result[4];
    memcpy(result, readData + 7, 4);
    unsigned int valueCurrent = strtoul(result, nullptr, 16);
    double current = ((double)valueCurrent) / 64;
    m_current = current;
}

bool HyperthermRS485::MonitorCurrent()
{
    int count = 20;
    double arcCurrent = 0;
    for (int i = 0; i < count; i++)
    {
        arcCurrent += m_current;
        usleep(100 * 1000);
    }
    if (0 == arcCurrent)
    {
        return false;
    }
    else
    {
        return true;
    }
}

