#include "elog.h"
#include "cJSON.h"

#include "IoConnection.h"
#include "GTAW_Control.h"

extern GTAW_Control GTAW;

#define GetJsonValueString(item, key1) \
    cJSON_GetObjectItem(item, key1)->valuestring
#define GetJsonValueDouble(item, key1) \
    cJSON_GetObjectItem(item, key1)->valuedouble
#define GetJsonValueInt(item, key1) \
    cJSON_GetObjectItem(item, key1)->valueint

IoConnection::IoConnection(/* args */)
{
}

IoConnection::~IoConnection()
{
}

int IoConnection::SetCurve(string param)
{
    HR_LOG_Info("enter IoConnection::SetCurve.");
    cJSON *rootJson = cJSON_Parse(param.c_str());
    cJSON *curveJson = cJSON_GetObjectItem(rootJson, "curve");
    cJSON *viJson = cJSON_GetObjectItem(curveJson, "vi");
    cJSON *viMinJson = cJSON_GetObjectItem(viJson, "min");
    m_curve.vi.minAO = GetJsonValueString(viMinJson, "key");
    m_curve.vi.minValue[0] = cJSON_GetArrayItem((cJSON_GetObjectItem(viMinJson, "value")->child), 0)->valuedouble;
    m_curve.vi.minValue[1] = cJSON_GetArrayItem((cJSON_GetObjectItem(viMinJson, "value")->child), 1)->valuedouble;
    cJSON *viMaxJson = cJSON_GetObjectItem(viJson, "max");
    m_curve.vi.maxAO = GetJsonValueString(viMaxJson, "key");
    m_curve.vi.maxValue[0] = cJSON_GetArrayItem((cJSON_GetObjectItem(viMaxJson, "value")->child), 0)->valuedouble;
    m_curve.vi.maxValue[1] = cJSON_GetArrayItem((cJSON_GetObjectItem(viMaxJson, "value")->child), 1)->valuedouble;
    cJSON *vvJson = cJSON_GetObjectItem(curveJson, "vv");
    cJSON *vvMinJson = cJSON_GetObjectItem(vvJson, "min");
    m_curve.vv.minAO = GetJsonValueString(vvMinJson, "key");
    m_curve.vv.minValue[0] = cJSON_GetArrayItem((cJSON_GetObjectItem(vvMinJson, "value")->child), 0)->valuedouble;
    m_curve.vv.minValue[1] = cJSON_GetArrayItem((cJSON_GetObjectItem(vvMinJson, "value")->child), 1)->valuedouble;
    cJSON *vvMaxJson = cJSON_GetObjectItem(vvJson, "max");
    m_curve.vv.maxAO = GetJsonValueString(vvMaxJson, "key");
    m_curve.vv.maxValue[0] = cJSON_GetArrayItem((cJSON_GetObjectItem(vvMaxJson, "value")->child), 0)->valuedouble;
    m_curve.vv.maxValue[1] = cJSON_GetArrayItem((cJSON_GetObjectItem(vvMaxJson, "value")->child), 1)->valuedouble;
    HR_LOG_Info("leave IoConnection::SetCurve.");
}

int IoConnection::SetIoConfiguration(string param)
{
    HR_LOG_Info("enter IoConnection::SetIoConfiguration.");
    cJSON *rootJson = cJSON_Parse(param.c_str());
    cJSON *ioJson = cJSON_GetObjectItem(rootJson, "io");

    cJSON *outputJson = cJSON_GetObjectItem(ioJson, "output");
    m_ioConfiguration.arcOn.ioName = GetJsonValueString(cJSON_GetObjectItem(outputJson, "arcOn"), "key");
    m_ioConfiguration.arcOn.value = GetJsonValueInt(cJSON_GetObjectItem(outputJson, "arcOn"), "value");
    m_ioConfiguration.wirePush.ioName = GetJsonValueString(cJSON_GetObjectItem(outputJson, "wirePush"), "key");
    m_ioConfiguration.wirePush.value = GetJsonValueInt(cJSON_GetObjectItem(outputJson, "wirePush"), "value");
    m_ioConfiguration.wirePull.ioName = GetJsonValueString(cJSON_GetObjectItem(outputJson, "wirePull"), "key");
    m_ioConfiguration.wirePull.value = GetJsonValueInt(cJSON_GetObjectItem(outputJson, "wirePull"), "value");
    m_ioConfiguration.gasDetection.ioName = GetJsonValueString(cJSON_GetObjectItem(outputJson, "gasDetection"), "key");
    m_ioConfiguration.gasDetection.value = GetJsonValueInt(cJSON_GetObjectItem(outputJson, "gasDetection"), "value");

    cJSON *inputJson = cJSON_GetObjectItem(ioJson, "input");
    m_ioConfiguration.welderReady.ioName = GetJsonValueString(cJSON_GetObjectItem(inputJson, "welderReady"), "key");
    m_ioConfiguration.welderReady.value = GetJsonValueInt(cJSON_GetObjectItem(inputJson, "welderReady"), "value");
    m_ioConfiguration.arcDetection.ioName = GetJsonValueString(cJSON_GetObjectItem(inputJson, "arcDetection"), "key");
    m_ioConfiguration.arcDetection.value = GetJsonValueInt(cJSON_GetObjectItem(inputJson, "arcDetection"), "value");
    m_ioConfiguration.locateSuccess.ioName = GetJsonValueString(cJSON_GetObjectItem(inputJson, "locateSuccess"), "key");
    m_ioConfiguration.locateSuccess.value = GetJsonValueInt(cJSON_GetObjectItem(inputJson, "locateSuccess"), "value");
    m_ioConfiguration.robotEmergencyStop.ioName = GetJsonValueString(cJSON_GetObjectItem(inputJson, "robotEmergencyStop"), "key");
    m_ioConfiguration.robotEmergencyStop.value = GetJsonValueInt(cJSON_GetObjectItem(inputJson, "robotEmergencyStop"), "value");
    HR_LOG_Info("leave IoConnection::SetIoConfiguration.");
}

int IoConnection::ArcOn()
{
    HR_LOG_Info("enter IoConnection::ArcOn.");
    R2G_Output(m_ioConfiguration.arcOn.ioName,m_ioConfiguration.arcOn.value);
    HR_LOG_Info("IO = %s, value = %d",m_ioConfiguration.arcOn.ioName,m_ioConfiguration.arcOn.value);
    HR_LOG_Info("leave IoConnection::ArcOn.");
}

int IoConnection::ArcOff()
{
    HR_LOG_Info("enter IoConnection::ArcOff.");
    R2G_Output(m_ioConfiguration.arcOn.ioName,1-m_ioConfiguration.arcOn.value);
    HR_LOG_Info("leave IoConnection::ArcOff.");
}

int IoConnection::StartPushWire()
{
    HR_LOG_Info("enter IoConnection::StartPushWire.");
    R2G_Output(m_ioConfiguration.wirePush.ioName,m_ioConfiguration.wirePush.value);
    HR_LOG_Info("leave IoConnection::StartPushWire.");
}

int IoConnection::StopPushWire()
{
    HR_LOG_Info("enter IoConnection::StopPushWire.");
    R2G_Output(m_ioConfiguration.wirePush.ioName,1-m_ioConfiguration.wirePush.value);
    HR_LOG_Info("leave IoConnection::StopPushWire.");
}

int IoConnection::StartPullWire()
{
    HR_LOG_Info("enter IoConnection::StartPullWire.");
    R2G_Output(m_ioConfiguration.wirePull.ioName,m_ioConfiguration.wirePull.value);
    HR_LOG_Info("leave IoConnection::StartPullWire.");
}

int IoConnection::StopPullWire()
{
    HR_LOG_Info("enter IoConnection::StopPullWire.");
    R2G_Output(m_ioConfiguration.wirePull.ioName,1-m_ioConfiguration.wirePull.value);
    HR_LOG_Info("leave IoConnection::StopPullWire.");
}

int IoConnection::StartFlow()
{
    HR_LOG_Info("enter IoConnection::StartFlow.");
    R2G_Output(m_ioConfiguration.gasDetection.ioName,m_ioConfiguration.gasDetection.value);
    HR_LOG_Info("leave IoConnection::StartFlow.");
}

int IoConnection::StopFlow()
{
    HR_LOG_Info("enter IoConnection::StopFlow.");
    R2G_Output(m_ioConfiguration.gasDetection.ioName,1-m_ioConfiguration.gasDetection.value);
    HR_LOG_Info("leave IoConnection::StopFlow.");
}

int IoConnection::R2G_Output(string ioName,int value)
{
    if(ioName[0] == "C")
    {
        GTAW.R2G_CO_signal(atoi(ioName[2]),value);
    }
    else if(ioName[0] == "D")
    {
        GTAW.R2G_DO_signal(atoi(ioName[2]),value);
    }
    else
    {
        HR_LOG_Error("IO name error. ioname = %s.",ioName.c_str());
    }
    HR_LOG_Info("ioname = %s, value = %d.",ioName.c_str(),value);
}

int IoConnection::SetCurrentVoltage(double current, double voltage)
{
    HR_LOG_Info("enter IoConnection::SetCurrentVoltage.");
    double transCurrent = ConvertCurrent(current);
    GTAW.R2G_AO_signal(atoi(m_curve.vi.ioName[2]), m_curve.vi.mode, transCurrent); // 设置电流

    double transVoltage = ConvertVoltage(voltage);
    GTAW.R2G_AO_signal(atoi(m_curve.vv.ioName[2]), m_curve.vv.mode, transVoltage); // 设置电压
    
    HR_LOG_Info("current = %f, voltage = %f, transCurrent = %f, transVoltage = %f ",
                current, voltage, transCurrent, transVoltage);
    HR_LOG_Info("leave IoConnection::SetCurrentVoltage. ")
}

double IoConnection::ConvertCurrent(double current)
{
    return ConvertRange(m_curve.vi.minValue[0], m_curve.vi.maxValue[0], m_curve.vi.minValue[1], m_curve.vi.maxValue[1], current);
}

double IoConnection::ConvertVoltage(double voltage)
{
    return ConvertRange(m_curve.vv.minValue[0], m_curve.vv.maxValue[0], m_curve.vv.minValue[1], m_curve.vv.maxValue[1], voltage);
}

double IoConnection::ConvertRange(double aoMin, double aoMax, double weldMin, double weldMax, double value)
{
    HR_LOG_Info("enter IoConnection::ConvertRange.");
    if (value >= weldMin && cValue <= weldMax)
    {
        return aoMin + (aoMax - aoMin) * (cValue - weldMin) / (weldMax - weldMin);
    }
    else if (value < weldMin)
    {
        return aoMin;
    }
    else if (value > weldMax)
    {
        return aoMax;
    }
    HR_LOG_Info("leave IoConnection::ConvertRange.");
}
