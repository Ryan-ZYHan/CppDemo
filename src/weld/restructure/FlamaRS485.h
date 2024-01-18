#ifndef __FLAMARS485_H_
#define __FLAMARS485_H_
#include "WeldMachine.h"
class FlamaRS485 : public WeldMachine
{
public:
    FlamaRS485();
    virtual ~FlamaRS485();
    /* 焊机功能的具体实现 */
    virtual int OpendDevice() override;                             // 连接设备
    virtual int CloseDevice() override;                             // 关闭设备
    virtual int ArcOnSet(const vector<string> &param) override;     // 起弧设置
    virtual int ArcOffSet(const vector<string> &param) override;    // 收弧设置
    virtual int WeldSet(const vector<string> &param) override;      // 焊机设置
    virtual int MaterialsSet(const vector<string> &param) override; // 材料设置
    virtual int ArcOn() override;                                   // 起弧
    virtual int ArcOff() override;                                  // 收弧
    virtual int StartPushWire() override;                           // 开始送丝
    virtual int StopPushWire() override;                            // 停止送丝
    virtual int StartPullWire() override;                           // 开始抽丝
    virtual int StopPullWire() override;                            // 停止抽丝
    virtual int StartFlow() override;                               // 开始送气
    virtual int StopFlow() override;                                // 停止送气
    virtual int DeviceCheck() override;                             // 设备检查
    virtual string GetDeviceName() override;                        // 获取设备名
    virtual void DataCollection() override;                         // 数据采集
    virtual bool IsArcOnSuccess() override;                         // 起弧是否成功
    virtual WeldParam GetParams() override;
};


#endif