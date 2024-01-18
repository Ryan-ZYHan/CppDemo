#ifndef __HYPERTHERMRS485_H_
#define __HYPERTHERMRS485_H_

#include <atomic>
#include "WeldMachine.h"
#include "SerialPort.h"

class HyperthermRS485 : public WeldMachine
{
public:
    HyperthermRS485();
    virtual ~HyperthermRS485();

    /* 焊机功能的具体实现 */
    virtual int OpendDevice() override;// 连接设备
    virtual int CloseDevice() override;// 关闭设备
    virtual int ArcOnSet(const vector<string> &param) override;// 起弧设置
    virtual int ArcOffSet(const vector<string> &param) override;// 收弧设置
    virtual int WeldSet(const vector<string> &param) override;// 焊机设置
    virtual int MaterialsSet(const vector<string> &param) override;// 材料设置
    virtual int ArcOn() override;// 起弧
    virtual int ArcOff() override;// 收弧
    virtual int StartPushWire() override;// 开始送丝
    virtual int StopPushWire() override;// 停止送丝
    virtual int StartPullWire() override;// 开始抽丝
    virtual int StopPullWire() override;// 停止抽丝
    virtual int StartFlow() override;// 开始送气
    virtual int StopFlow() override;// 停止送气
    virtual int DeviceCheck() override;// 设备检查
    virtual string GetDeviceName() override;// 获取设备名
    virtual void DataCollection() override;// 数据采集
    virtual bool IsArcOnSuccess() override;// 起弧是否成功
    virtual WeldParam GetParams() override;

public:
    int GetFault();      // 获取错误码
    double GetCurrent(); // 获取电流
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

    string m_boxIO = "";  // 继电器连接的输出端口
    int m_fault = 0;      // 错误码
    double m_current = 0; // 电流
    bool m_currentMonitoringFlag = false; //电流监测标记.true：开启电流监测
private:
    std::string FindTTYUSB(); // 寻找当前连接的USB设备
    int ReadFault();          // 读错误码
    int ReadCurrent();        // 读电流
    bool MonitorCurrent();    // 监测电流。false：电流异常
};

#endif
