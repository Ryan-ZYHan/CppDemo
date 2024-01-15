#ifndef __HANDLE_H_
#define __HANDLE_H_

#include <map>
#include <cstring>
#include <vector>
#include "cJSON.h"

enum RobotModel // 机器人型号
{
    Elfin = 1,
    ElfinPro,
};

enum ButtonFunction // 按钮功能（推送前端的部分）
{
    AddLine = 1,                // 添加直线
    AddCircularArc,             // 添加圆弧
    AddStraightWeldingTemplate, // 添加直线焊接模板
    AddArcWeldingTemplate,      // 添加圆弧焊接模板
    CursorDown,                 // 光标下移
    CursorUp,                   // 光标上移
};

enum WeldFunction // 焊机功能
{
    StartPushWire = 1, // 开始送丝
    StopPushWire,      // 停止送丝
    StartPullWire,     // 开始抽丝
    StopPullWire,      // 停止抽丝
};

class Handle
{
public:
    Handle(/* args */);
    ~Handle();
    int SetRobotModel(RobotModel robotModel);          // 设置机器人型号
    int SetPressTimeThreshold(int pressTimeThreshold); // 设置按压时间阈值以区分长短按
    int SetDelayTime(int delayTime);                   // 设置周期时间
    bool IsPush();                                     // 是否推送
    int GetPushFunc();                                 // 获得按钮按下时向前端推送功能，返回见ButtonFunction
    int GetWeldFunc();                                 // 获得按钮按下时焊机执行功能，返回见WeldFunction，（后续5.0应将焊机功能放在该类中）
    int Push(cJSON *root);                             // 将按钮功能推送到前端
    void ExeHandleAction(std::vector<int> endDI);      // 执行手柄监听功能
private:
    int m_robotModel = 0;            // 机器人型号，0表示未设置型号
    int m_buttonIndex = 0;           // 按下的按钮，0表示没有按下，1-6分别对应按钮，左上->左下：1-3；右上->右下：6-4
    int m_pressTime = 0;             // 按压时间
    int m_pushFunctionIndex = 0;     // 向前端推送的功能索引
    bool m_pushFunctionFlag = false; // 是否向前端推送
    int m_pressTimeThreshold = 1000; // 按压时间阈值，单位：毫秒，默认1秒
    int m_delayTime = 50;            // 接收数据周期，10004、100014:50ms；10005、10015:100ms；10006、10016:200ms
    int m_weldFunction = 0;          // 按钮按下时焊机需要执行的功能

    int m_endDO[8] = {0, 0, 0, 0, 0, 0, 0, 0};       // 末端输出数组，前两位无效，3-8位置1时分别对应按钮6-1亮起
    std::vector<int> m_buttonDefault = {1, 1, 1, 1}; // 无按压时的末端输入信号
    std::vector<int> m_button1 = {0, 1, 1, 1};       // 按压按钮1时的末端输入信号
    std::vector<int> m_button2 = {1, 0, 1, 1};       // 按压按钮2时的末端输入信号
    std::vector<int> m_button3 = {0, 0, 1, 1};       // 按压按钮3时的末端输入信号
    std::vector<int> m_button4 = {1, 1, 0, 1};       // 按压按钮4时的末端输入信号
    std::vector<int> m_button5 = {0, 1, 0, 1};       // 按压按钮5时的末端输入信号
    std::vector<int> m_button6 = {1, 0, 0, 1};       // 按压按钮6时的末端输入信号
    std::map<int, std::vector<int>> m_buttonMap{     // 按钮序号和对应的末端信号映射
                                                {1, m_button1},
                                                {2, m_button2},
                                                {3, m_button3},
                                                {4, m_button4},
                                                {5, m_button5},
                                                {6, m_button6}};

private:
    void GetButtonPressedIndexOf6ButtonHandleForPro(std::vector<int> endDI); // 判断按压的按钮索引。endDI：末端信号
    void SetEndDO();                                                         // 设置末端输出
    void OnButtonReleaseAction();                                            // 按钮松开时的执行代码
    void OnButtonPressAction(std::vector<int> endDI);                        // 按钮按下时的执行代码
};
#endif