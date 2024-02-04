#ifndef __WELDMACHINE_H_
#define __WELDMACHINE_H_

#include <vector>
#include <string>
#include "Constant.h"
#include "ErrorCode.h"

using std::string;
using std::vector;

class WeldMachine
{
public:
    virtual int OpendDevice() = 0;                             // 连接设备
    virtual int CloseDevice() = 0;                             // 关闭设备
    virtual int ArcOnSet(const vector<string> &param) = 0;     // 起弧设置
    virtual int ArcOffSet(const vector<string> &param) = 0;    // 收弧设置
    virtual int WeldSet(const vector<string> &param) = 0;      // 焊机设置
    virtual int MaterialsSet(const vector<string> &param) = 0; // 材料设置
    virtual int ArcOn() = 0;                                   // 起弧
    virtual int ArcOff() = 0;                                  // 收弧
    virtual int StartPushWire() = 0;                           // 开始送丝
    virtual int StopPushWire() = 0;                            // 停止送丝
    virtual int StartPullWire() = 0;                           // 开始抽丝
    virtual int StopPullWire() = 0;                            // 停止抽丝
    virtual int StartFlow() = 0;                               // 开始送气
    virtual int StopFlow() = 0;                                // 停止送气
    virtual int DeviceCheck() = 0;                             // 设备检查
    virtual string GetDeviceName() = 0;                        // 获取设备名
    virtual void DataCollection() = 0;                         // 数据采集
    virtual bool IsArcOnSuccess() = 0;                         // 起弧是否成功
    virtual Params GetParams() = 0;                         // 焊机数据（应该包括设置电流电压等参数，实时电流电压等参数，故障码等）
    virtual ~WeldMachine() = default;
};

#endif
