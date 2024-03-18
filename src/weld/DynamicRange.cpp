#include <sstream>
#include "elog.h"
#include "DynamicRange.h"

using std::vector;

#define GetJsonValueString(item, key1) \
    cJSON_GetObjectItem(item, key1)->valuestring
#define GetJsonValueDouble(item, key1) \
    cJSON_GetObjectItem(item, key1)->valuedouble
#define GetJsonValueInt(item, key1) \
    cJSON_GetObjectItem(item, key1)->valueint

DynamicRange::DynamicRange(/* args */)
{
}

DynamicRange::~DynamicRange()
{
}

void DynamicRange::Confige(cJSON *deviceParamJson)
{
    HR_LOG_Info("enter DynamicRange::Confige");
    string eRange = GetJsonValueString(deviceParamJson, "E_range");
    vector<string> ranges = SplitString(eRange, ';');
    cJSON *currentRangeParamJson = cJSON_Parse(ranges[0].c_str());
    m_range.minCurrent = GetJsonValueDouble(currentRangeParamJson, "min");
    m_range.maxCurrent = GetJsonValueDouble(currentRangeParamJson, "max");

    for (int i = 1; i < ranges.size(); i++)
    {
        cJSON *modeRangeParamJson = cJSON_Parse(ranges[i].c_str());
        int mode = GetJsonValueInt(modeRangeParamJson, "mode");
        m_range.modeRanges[mode].min = GetJsonValueInt(modeRangeParamJson, "min");
        m_range.modeRanges[mode].max = GetJsonValueInt(modeRangeParamJson, "max");
    }
    HR_LOG_Info("leave DynamicRange::Confige");
}

unsigned int DynamicRange::ComputeCurrent(double current)
{
    HR_LOG_Info("enter DynamicRange::ComputeCurrent.");
    unsigned int computeCurrent = MapValue(current, m_range.minCurrent, m_range.maxCurrent);
    HR_LOG_Info("current = %f, computeCurrent = %d.", current, computeCurrent);
    HR_LOG_Info("leave DynamicRange::ComputeCurrent.");
    return computeCurrent;
}

unsigned int DynamicRange::ComputeRespectivelyVoltage(double voltage)
{
    HR_LOG_Info("enter DynamicRange::ComputeRespectivelyVoltage.");
    unsigned int computeVoltage = MapValue(voltage, m_range.modeRanges[DC_RESPECTIVELY].min, m_range.modeRanges[DC_RESPECTIVELY].max);
    HR_LOG_Info("voltage = %f, computeVoltage = %d.", voltage, computeVoltage);
    HR_LOG_Info("leave DynamicRange::ComputeRespectivelyVoltage.");
    return computeVoltage;
}
unsigned int DynamicRange::ComputeUnifiedVoltage(double voltage,int mode)
{
    HR_LOG_Info("enter DynamicRange::ComputeUnifiedVoltage.");
    unsigned int computeVoltage = MapValue(voltage, m_range.modeRanges[mode].min, m_range.modeRanges[mode].max);
    HR_LOG_Info("voltage = %f, computeVoltage = %d.", voltage, computeVoltage);
    HR_LOG_Info("leave DynamicRange::ComputeUnifiedVoltage.");
    return computeVoltage;
}

unsigned int DynamicRange::MapValue(double value, double min, double max)
{
    if (value < min)
    {
        return 0;
    }
    else if (value > max)
    {
        return 65535;
    }
    else
    {
        return static_cast<unsigned int>((static_cast<double>(value - min) / (max - min)) * 65535);
    }
}

std::vector<std::string> DynamicRange::SplitString(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}