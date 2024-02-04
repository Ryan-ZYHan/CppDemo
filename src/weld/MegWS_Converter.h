#ifndef __MEGWS_CONVERTER_H_
#define __MEGWS_CONVERTER_H_

enum WeldMode //焊接模式
{
    DC = 1, //直流
    Pulse, //脉冲
};

enum WireMaterial //焊丝材料
{
    CarbonSteel = 1, //碳钢
    StainlessSteel, //不锈钢
    AlSi, //铝硅
    AlMg, //铝镁
};

enum WireDiameter // 焊丝直径
{

};

class MegWS_Converter // 麦格米特送丝速度转电流
{
public:
    MegWS_Converter(/* args */);
    ~MegWS_Converter();
private:
    int m_numWeldingModes = 2;
};

MegWS_Converter::MegWS_Converter(/* args */)
{
}

MegWS_Converter::~MegWS_Converter()
{
}

#endif