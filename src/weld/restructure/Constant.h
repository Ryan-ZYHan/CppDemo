#ifndef __CONSTANT_H_
#define __CONSTANT_H_

struct Params
{
    WeldParams weldParams;
    ArcOnParams arcOnParams;
    ArcOffParams arcOffParams;
};

struct BaseParams
{
    int current;     // 电流
    int voltage;     // 电压
    int airPressure; // 气压
};

struct WeldParams : BaseParams
{
};

struct ArcOnParams : BaseParams
{
    /* data */
};

struct ArcOffParams : BaseParams
{
    /* data */
};

#endif