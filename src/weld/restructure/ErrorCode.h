#ifndef __ERRORCODE_H_
#define __ERRORCODE_H_

enum OpendDeviceError
{
    /* 串口 */
    NoUSBDevice = 60100, //没有USB设备
    SerialPortOpenFail, //串口打开失败
};

enum ArcOnError
{
    BoxIDError = 60200, //电箱端口错误
};

#endif