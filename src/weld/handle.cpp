#include "Handle.h"
#include "elog.h"
#include "HRSDK/HR_Pro.h"
#include "GTAW_Control.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

extern GTAW_Control GTAW;

Handle::Handle()
{
}

Handle::~Handle()
{
    close(m_sockfd);
}

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

int Handle::SetHandleEnable(bool handleEnable)
{
    HR_LOG_Info("enter Handle::SetHandleEnable.");
    m_handleEnable = handleEnable;
    HR_LOG_Info("leave Handle::SetHandleEnable. m_handleEnable = %d.", m_handleEnable);
}

bool Handle::IsPush()
{
    return m_pushFunctionFlag;
}

int Handle::GetPushFunc()
{
    return m_pushFunctionIndex;
}

int Handle::GetWeldFunc()
{
    return m_weldFunction;
}

int Handle::Push(cJSON *root)
{
    if (m_pushFunctionFlag)
    {
        cJSON_AddNumberToObject(root, "buttonFunction", m_pushFunctionIndex);
        m_pushFunctionFlag = false;
        m_pushFunctionIndex = 0;
        m_buttonIndex = 0;
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

void Handle::Start()
{
    if (m_handleEnable)
    {
        std::vector<int> endDIVec;
        if (RecevieEndDI(endDIVec))
        {
            ExeHandleAction(endDIVec);
            switch (GetWeldFunc())
            {
            case WeldFunction::StartPushWire:
                GTAW.StartPushWire();
                break;
            case WeldFunction::StopPushWire:
                GTAW.StopPushWire();
                break;
            case WeldFunction::StartPullWire:
                GTAW.StartPullWire();
                break;
            case WeldFunction::StopPullWire:
                GTAW.StopPullWire();
                break;
            default:
                break;
            }
        }
    }
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
        m_weldFunction = 0;
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
        m_weldFunction = StopPushWire; // 停止送丝
        break;
    case 4:
        m_weldFunction = StopPullWire; // 停止退丝
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
        m_weldFunction = 0;
        break;
    case 2:
        m_pressTime += m_delayTime;
        m_weldFunction = 0;
        break;
    case 3:
        m_weldFunction = StartPushWire;
        break;
    case 4:
        m_weldFunction = StartPullWire;
        break;
    case 5:
        m_weldFunction = 0;
        break;
    case 6:
        m_weldFunction = 0;
        break;
    default:
        break;
    }
}

bool Handle::SocketConnect()
{
    const char *serverIP = m_ipAddress.c_str();
    int portNumber = m_port;

    // 关闭现有的套接字连接（如果存在）
    if (m_sockfd != -1)
    {
        close(m_sockfd);
    }

    // 创建新的套接字
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sockfd == -1)
    {
        HR_LOG_Info("Create Socket Error!");
        return false;
    }

    // 连接到服务器端
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portNumber);
    if (inet_pton(AF_INET, serverIP, &(serverAddr.sin_addr)) <= 0)
    {
        HR_LOG_Info("Invalid IP Address!");
        close(m_sockfd);
        return false;
    }

    int connectResult = connect(m_sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (connectResult == -1)
    {
        HR_LOG_Info("Socket Connect Error!");
        close(m_sockfd);
        return false;
    }

    return true;
}

void Handle::GetEndDIFromString(std::vector<int> &endDI, string charArray)
{
    // 要查找的目标字符串
    std::string targetString = "EndDI";

    // 在原始字符串中查找目标字符串
    size_t pos = charArray.find(targetString);

    if (pos != std::string::npos)
    {
        // 找到目标字符串后，找到中括号的位置
        size_t startBracket = charArray.find('[', pos);
        size_t endBracket = charArray.find(']', startBracket);

        if (startBracket != std::string::npos && endBracket != std::string::npos)
        {
            // 提取中括号内的内容
            std::string content = charArray.substr(startBracket + 1, endBracket - startBracket - 1);

            // 将内容解析为整数并存储到 std::vector<int> 中
            std::vector<int> endDI;
            size_t start = 0;
            size_t commaPos = content.find(',');

            while (commaPos != std::string::npos)
            {
                endDI.push_back(std::stoi(content.substr(start, commaPos - start)));
                start = commaPos + 1;
                commaPos = content.find(',', start);
            }

            // 处理最后一个数字
            endDI.push_back(std::stoi(content.substr(start)));
        }
    }
}

bool Handle::RecevieEndDI(std::vector<int> &endDI)
{
    char buffer[4096]; // 缓冲区大小

    // 从套接字读取数据
    int bytesRead = read(m_sockfd, buffer, sizeof(buffer));
    if (bytesRead <= 0)
    {
        return false;
    }
    // 复制从第12个位置开始的数据到新的缓冲区
    int startPos = 12;                        // 起始位置
    int newDataLength = bytesRead - startPos; // 需要复制的数据长度

    std::string receivedData(buffer + startPos, newDataLength);
    GetEndDIFromString(endDI, receivedData);
}