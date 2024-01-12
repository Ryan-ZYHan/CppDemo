#include "Handle.h"
#include "elog.h"
#include "HRSDK/HR_Pro.h"

int Handle::SetRobotModel(RobotModel robotModel)
{
    HR_LOG_Info("enter Handle::SetRobotModel.");
    m_robotModel = robotModel;

    HR_LOG_Info("leave Handle::SetRobotModel.");
    return 0;
}

int Handle::SetPressTimeThreshold(int pressTimeThreshold)
{
    if (pressTimeThreshold < 1000)
    {
        HR_LOG_Error("pressTimeThreshold is too small, pressTimeThreshold = %d", pressTimeThreshold);
        return -1;
    }
    m_pressTimeThreshold = pressTimeThreshold;
    return 0;
}

int Handle::SetDelayTime(int delayTime)
{
    if (delayTime != 50 || delayTime != 100 || delayTime != 200)
    {
        HR_LOG_Error("Wrong delayTime, delayTime = %d", delayTime);
        return -1;
    }
    m_delayTime = delayTime;
    return 0;
}

bool Handle::IsButtonPress()
{
    return m_pushFunctionFlag;
}

int Handle::GetButtonFunc()
{
    return m_pushFunctionIndex;
}

void Handle::GetButtonPressedIndexOf6ButtonHandleForPro(std::vector<int> endDI)
{
    for (int i = 1; i < 7; i++)
    {
        if (endDI == m_buttonMap[i])
        {
            m_buttonIndex = i;
            HR_LOG_Debug("button index is %d", i);
            return;
        }
    }
    HR_LOG_Debug("wrong button press.");
}

void Handle::SetEndDO()
{
    HRIF_SetEndDO(0, 0, 2, 0); // 锁存线置低
    for (int i = 0; i < 8; i++)
    {
        HRIF_SetEndDO(0, 0, 1, m_endDO[i]); // 置数据位
        HRIF_SetEndDO(0, 0, 0, 1);          // 时钟线置高
        HRIF_SetEndDO(0, 0, 0, 0);          // 时钟线置低
    }
    HRIF_SetEndDO(0, 0, 2, 1); // 锁存线置高
}

void Handle::OnButtonReleaseAction()
{
    if (0 == m_buttonIndex)
    {
        return;
    }
    if (m_buttonIndex > 0)
    {
        HR_LOG_Debug("button %d release.", m_buttonIndex);
        for (int i = 0; i < 8; i++)
        {
            m_endDO[i] = 0;
        }
        SetEndDO();
    }

    switch (m_buttonIndex)
    {
    case 1:
        if (m_pressTime < m_pressTimeThreshold) // 短按
        {
            m_pushFunctionIndex = AddLine;
        }
        else // 长按
        {
            m_pushFunctionIndex = AddCircularArc;
        }
        m_pushFunctionFlag = true;
        break;
    case 2:
        if (m_pressTime < m_pressTimeThreshold) // 短按
        {
            m_pushFunctionIndex = AddStraightWeldingTemplate;
        }
        else // 长按
        {
            m_pushFunctionIndex = AddArcWeldingTemplate;
        }
        m_pushFunctionFlag = true;
        break;
    case 3:
        // 停止送丝
        break;
    case 4:
        // 停止退丝
        break;
    case 5:
        m_pushFunctionIndex = CursorDown;
        m_pushFunctionFlag = true;
        break;
    case 6:
        m_pushFunctionIndex = CursorUp;
        m_pushFunctionFlag = true;
        break;
    default:
        break;
    }
    m_pressTime = 0;
    m_buttonIndex = 0;
}

void Handle::OnButtonPressAction(std::vector<int> endDI)
{
    GetButtonPressedIndexOf6ButtonHandleForPro(endDI);
    if (m_buttonIndex > 0)
    {
        m_endDO[8 - m_buttonIndex] = 1;
        SetEndDO();
    }

    switch (m_buttonIndex)
    {
    case 1:
        m_pressTime += m_delayTime;
        break;
    case 2:
        m_pressTime += m_delayTime;
        break;
    case 3:
        // 送丝
        break;
    case 4:
        // 退丝
        break;
    case 5:
        break;
    case 6:
        break;
    default:
        break;
    }
}

void Handle::ExeHandleAction(std::vector<int> endDI)
{
    if (endDI == m_buttonDefault) // 如果信号是松开的时候
    {
        OnButtonReleaseAction();
    }
    else // 如果按下
    {
        OnButtonPressAction(endDI);
    }
}