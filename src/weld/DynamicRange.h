/*
    @brief 处理麦格米特焊机电流电压的动态范围
*/
#ifndef __DYNAMICRANGE_H_
#define __DYNAMICRANGE_H_

#include <vector>
#include <string>
#include <map>
#include "cJSON.h"

using std::map;
using std::string;

struct Range
{
    double minCurrent;
    double maxCurrent;
    map<int, ModeRange> modeRanges;
};

struct ModeRange
{
    double min;
    double max;
};

enum Mode
{
    DC_UNITIZATION = 0,       // 直流一元化
    PULSE_UNITIZATION = 1,    // 脉冲一元化
    JOB = 2,                  // JOB 模式
    INTERMITTENT_WELDING = 3, // 断续焊
    DC_RESPECTIVELY = 4,      // 直流分别模式
};

class DynamicRange
{

public:
    DynamicRange(/* args */);
    ~DynamicRange();
    void Confige(cJSON *deviceParamJson);
    unsigned int ComputeCurrent(double current); //电流计算
    unsigned int ComputeRespectivelyVoltage(double voltage); //分别模式电压计算
    unsigned int ComputeUnifiedVoltage(double voltage,int mode); //一元化电压计算

public:
    Range m_range;

private:
    unsigned int MapValue(double value, double min, double max);                // 数据映射
    std::vector<std::string> SplitString(const std::string &s, char delimiter); // 分割字符串
};

#endif