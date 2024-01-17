#ifndef __HYPERTHERM_H_
#define __HYPERTHERM_H_

#include <atomic>
#include "WeldMachine.h"
#include "SerialPort.h"

class Hypertherm : public WeldMachine
{
public:
    Hypertherm();          // 构造函数
    virtual ~Hypertherm(); // 析构函数

    /* 焊机功能的具体实现 */
    virtual int OpendDevice() override;
    virtual int CloseDevice() override;
    virtual int ArcOnSet(const vector<string> &param) override;
    virtual int ArcOffSet(const vector<string> &param) override;
    virtual int WeldSet(const vector<string> &param) override;
    virtual int MaterialsSet(const vector<string> &param) override;
    virtual int ArcOn() override;
    virtual int ArcOff() override;
    virtual int StartPushWire() override;
    virtual int StopPushWire() override;
    virtual int StartPullWire() override;
    virtual int StopPullWire() override;
    virtual int StartFlow() override;
    virtual int StopFlow() override;
    virtual int DeviceCheck() override;
    virtual string GetDeviceName() override;
    virtual void DataCollection() override;
    virtual bool IsArcOnSuccess() override;
    virtual WeldParam GetParams() override;

private:
    string m_modelName = "Hypertherm";              // Hypertherm型号名称
    int m_baudRate = 19200;                         // 波特率= 19200
    int m_dataBits = 8;                             // 数据位= 8
    int m_stopBits = 1;                             // 停止位= 1
    sp_parity m_parity = SP_PARITY_EVEN;            // 奇偶校验，偶校验
    SerialPort m_serialPort;                        // 串口通信对象
    std::atomic_char m_hyperthermRS485Data[31];     // 发送数据
    std::atomic_char m_tempHyperthermRS485Data[31]; // 临时数据
    std::atomic_int m_hyperthermRS485DataSize;      // 发送数据长度
    int m_connectMsgLength = 31;                    // 连接时报文长度= 31
    int m_flowMsgLength = 17;                       // 送气时报文长度= 17

    string m_boxIO=""; // 继电器连接的输出端口
private:
    std::string FindTTYUSB(); // 寻找当前连接的USB设备
};

#endif
