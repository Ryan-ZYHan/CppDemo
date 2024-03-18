/**
 *  @brief 用于IO通讯方式，模拟量曲线设置和IO口配置
 */
#ifndef __IOCONNECTION_H_
#define __IOCONNECTION_H_

#include <string>

using std::string;

struct Curve
{
    AnalogRange vi; // vi曲线结构
    AnalogRange vv; // vv曲线结构
};

struct IoConfiguration
{
    /* 输出 */
    IoInfo arcOn;        // 起弧
    IoInfo wirePush;     // 送丝
    IoInfo wirePull;     // 抽丝
    IoInfo gasDetection; // 送气检测

    /* 输入 */
    IoInfo welderReady;        // 焊机准备
    IoInfo arcDetection;       // 起弧检测
    IoInfo locateSuccess;      // 寻位成功
    IoInfo robotEmergencyStop; // 机器人急停
};

struct AnalogRange
{
    string minAO;            // AO 端口
    double minValue[2];      //[0]:模拟量范围最小值；[1]:焊机范围最小值
    string maxAO;            // AO 端口
    double maxValue[2];      //[0]:模拟量范围最大值；[1]:焊机范围最大值
    int mode = VOLTAGE_MODE; // 模拟量模式。（当前为电压模式）
};

enum AoMode
{
    VOLTAGE_MODE = 1, // 电压模式
    CURRENT_MODE = 2, // 电流模式
};

struct IoInfo
{
    string ioName; // 端口
    int value;     // 功能对应电平值
};

class IoConnection
{
public:
    IoConnection();
    ~IoConnection();

private:
    int SetCurve(string param);           // 设置曲线对应关系
    int SetIoConfiguration(string param); // 设置IO端口

    int OpendDevice();   // 连接设备
    int CloseDevice();   // 关闭设备
    int ArcOn();         // 起弧
    int ArcOff();        // 收弧
    int StartPushWire(); // 开始送丝
    int StopPushWire();  // 停止送丝
    int StartPullWire(); // 开始抽丝
    int StopPullWire();  // 停止抽丝
    int StartFlow();     // 开始送气
    int StopFlow();      // 停止送气
private:
    int SetCurrentVoltage(double current, double voltage);                                         // 设置电流电压
    double ConvertCurrent(double current);                                                         // 电流值转换
    double ConvertVoltage(double voltage);                                                         // 电压值转换
    double ConvertRange(double aoMin, double aoMax, double weldMin, double weldMax, double value); // 范围转换
    int R2G_Output(string ioName,int value); //数字信号输出
private:
    Curve m_curve;                     // vi、vv曲线参数
    IoConfiguration m_ioConfiguration; // io参数
};

#endif