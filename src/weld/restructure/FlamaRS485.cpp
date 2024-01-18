#include "FlamaRS485.h"
#include "elog.h"

FlamaRS485::FlamaRS485()
{
}

FlamaRS485::~FlamaRS485()
{
}

int FlamaRS485::OpendDevice() // 连接设备
{
    HR_LOG_Info("enter FlamaRS485::OpendDevice.");
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

    m_serialPort.configure(m_baudRate, m_dataBits, m_stopBits, m_parity); // 和宗焊机串口配置
    HR_LOG_Info("enter FlamaRS485::OpendDevice.");
}
int FlamaRS485::CloseDevice()                                 // 关闭设备
    int ArcOnSet(const vector<string> &param)     // 起弧设置
    int ArcOffSet(const vector<string> &param)    // 收弧设置
    int WeldSet(const vector<string> &param)      // 焊机设置
    int MaterialsSet(const vector<string> &param) // 材料设置
    int ArcOn()                                   // 起弧
    int ArcOff()                                  // 收弧
    int StartPushWire()                           // 开始送丝
    int StopPushWire()                            // 停止送丝
    int StartPullWire()                           // 开始抽丝
    int StopPullWire()                            // 停止抽丝
    int StartFlow()                               // 开始送气
    int StopFlow()                                // 停止送气
    int DeviceCheck()                             // 设备检查
    string GetDeviceName()                        // 获取设备名
    void DataCollection()                         // 数据采集
    bool IsArcOnSuccess()                         // 起弧是否成功
    WeldParam GetParams()