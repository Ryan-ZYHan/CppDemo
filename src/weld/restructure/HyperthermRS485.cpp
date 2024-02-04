#include <sstream>
#include <cstring>
#include "HyperthermRS485.h"
#include "elog.h"
#include "HRSDK/HR_Pro.h"

HyperthermRS485::HyperthermRS485()
{
    HR_LOG_Info("enter HyperthermRS485::HyperthermRS485.");
    HR_LOG_Info("leave HyperthermRS485::HyperthermRS485.");
}

HyperthermRS485::~HyperthermRS485()
{
    HR_LOG_Info("enter HyperthermRS485::~HyperthermRS485.");
    HR_LOG_Info("leave HyperthermRS485::~HyperthermRS485.");
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
        m_hyperthermRS485Data[i].store(m_connectData[i]);
    }
    m_hyperthermRS485DataSize.store(m_connectMsgLength);
    m_serialPort.write(m_hyperthermRS485Data, m_hyperthermRS485DataSize);
    /*需要增加是否连接成功的判断*/ 
    HR_LOG_Info("leave HyperthermRS485::OpendDevice");
    return 0;
}

int HyperthermRS485::CloseDevice()
{
    HR_LOG_Info("enter HyperthermRS485::CloseDevice.");
    for (int i = 0; i < m_connectMsgLength; ++i)
    {
        m_hyperthermRS485Data[i].store(m_disconnectData[i]);
    }
    m_hyperthermRS485DataSize.store(m_connectMsgLength);
    m_serialPort.write(m_hyperthermRS485Data, m_hyperthermRS485DataSize);
    memset(m_hyperthermRS485Data, 0, sizeof(m_hyperthermRS485Data)); // 数组清零
    m_serialPort.close();
    HR_LOG_Info("leave HyperthermRS485::CloseDevice.");
    return 0;
}

int HyperthermRS485::ArcOn()
{
    HR_LOG_Info("enter HyperthermRS485::ArcOn.");
    if(IsBoxIdEmpty())
    {
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
    if(IsBoxIdEmpty())
    {
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
        m_hyperthermRS485Data[i].store(m_startCheckFlowData[i]);
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
        m_hyperthermRS485Data[i].store(m_stopCheckFlowData[i]);
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
    HR_LOG_Waring("%s whhitout StartPushWire.",GetDeviceName().c_str());
    return 0;
}

int HyperthermRS485::StopPushWire()
{
     HR_LOG_Waring("%s whhitout StopPushWire.",GetDeviceName().c_str());
    return 0;
}

int HyperthermRS485::StartPullWire()
{
    HR_LOG_Waring("%s whhitout StartPullWire.",GetDeviceName().c_str());
    return 0;
}

int HyperthermRS485::StopPullWire()
{
    HR_LOG_Waring("%s whhitout StopPullWire.",GetDeviceName().c_str());
    return 0;
}

int HyperthermRS485::WeldSet(const vector<string> &param)
{
    HR_LOG_Info("enter HyperthermRS485::WeldSet.");
    /*数据处理*/
    SetParamValue(m_params.weldParams);
    m_hyperthermRS485DataSize.store(m_connectMsgLength);
    m_serialPort.write(m_hyperthermRS485Data, m_hyperthermRS485DataSize);
    HR_LOG_Info("leave HyperthermRS485::WeldSet.");
}

string HyperthermRS485::GetDeviceName()
{
    HR_LOG_Debug("enter HyperthermRS485::GetDeviceName, return %s",m_modelName.c_str());
    return m_modelName;
}

int HyperthermRS485::GetFault()
{
    HR_LOG_Debug("enter HyperthermRS485::GetFault, return %d",m_fault);
    return m_fault;
}

double HyperthermRS485::GetCurrent()
{
    HR_LOG_Debug("enter HyperthermRS485::GetCurrent, return %f",m_current);
    return m_current;
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

bool HyperthermRS485::IsBoxIdEmpty()
{
    if (m_boxIO == "")
    {
        HR_LOG_Error("box id is not configured, errorCode = %d.", BoxIDError);
        return true;
    }
    else 
    {
        HR_LOG_Info("box id = %s.",m_boxIO.c_str());
        return false;
    }
}

int HyperthermRS485::SetParamValue(BaseParams params)
{
    HR_LOG_Info("enter GTAW_Control::setHyperthermRS485ParamValue.");

    int hyperthermCurrent = params.current * 64;
    int hyperthermPressure = params.airPressure * 128;

    /* 设置电流 */
    std::stringstream sCur;
    sCur << std::hex << hyperthermCurrent;
    std::string charCurrent = sCur.str();
    charCurrent = charCurrent.length() < 4 ? '0' + charCurrent : charCurrent;
    for (int i = 19; i < 23; i++)
    {
        m_hyperthermRS485Data[i].store(toupper(charCurrent[i - 19]));
    }

    /* 设置气压 */
    std::stringstream sPre;
    sPre << std::hex << hyperthermPressure;
    std::string charPressure = sPre.str();
    int pLen = charPressure.length();
    if ((4 - pLen) > 0)
    {
        for (int i = 0; i < (4 - pLen); i++)
        {
            charPressure = '0' + charPressure;
        }
    }
    for (int i = 23; i < 27; i++)
    {
        m_hyperthermRS485Data[i].store(toupper(charPressure[i - 23]));
    }

    /* 计算LRC */
    char newHyperthermRS485Data[26];
    std::memcpy(newHyperthermRS485Data, m_hyperthermRS485Data + 1, 26);
    std::vector<unsigned char> hexs = Chars2Hexs(newHyperthermRS485Data, sizeof(newHyperthermRS485Data));
    std::stringstream sLRC;
    unsigned int lrcData = CalculateLRC(hexs);
    sLRC << std::hex << lrcData;
    std::string LRC = sLRC.str();
    LRC = LRC.length() < 2 ? '0' + LRC : LRC;
    m_hyperthermRS485Data[27].store(toupper(LRC[0]));
    m_hyperthermRS485Data[28].store(toupper(LRC[1]));
    HR_LOG_Info("leave GTAW_Control::setHyperthermRS485ParamValue.");
    return 0;
}

unsigned char HyperthermRS485::Char2Hex(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }
    else if (c >= 'a' && c <= 'f')
    {
        return c - 'a' + 10;
    }
    return 0; // 非法字符返回0
}

unsigned char HyperthermRS485::Chars2Hex(const char *chars)
{
    return (Char2Hex(chars[0]) << 4) | Char2Hex(chars[1]);
}

std::vector<unsigned char> HyperthermRS485::Chars2Hexs(const char chars[], int chars_size)
{
    std::vector<unsigned char> hexValues;
    for (int i = 0; i < chars_size / 2; ++i)
    {
        unsigned char hex = Chars2Hex(&chars[i * 2]);
        hexValues.push_back(hex);
    }
    return hexValues;
}

unsigned int HyperthermRS485::CalculateLRC(const std::vector<unsigned char> &data)
{
    unsigned int sum = 0;

    // 1.计算数组每个值的总和
    for (const auto &byte : data)
    {
        sum += byte;
    }

    // 2.根据规则调整总和值
    if (sum <= 0xFF)
    {
        sum = 0xFF - sum;
    }
    else
    {
        sum = 0xFF - (sum & 0xFF);
    }

    // 3.加1
    sum += 1;

    return sum;
}
