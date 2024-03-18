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

int Handle::SetRobotModel(int robotModel)
{
    HR_LOG_Info("enter Handle::SetRobotModel.");
    m_robotModel = robotModel;
    if (RobotModel::Elfin == m_robotModel)
    {
        m_buttonDefault[3] = 0;
        m_buttonMap[1][3] = 0;
        m_buttonMap[2][3] = 0;
        m_buttonMap[3][3] = 0;
        m_buttonMap[4][3] = 0;
        m_buttonMap[5][3] = 0;
        m_buttonMap[6][3] = 0;
    }
    else if (RobotModel::ElfinPro == m_robotModel)
    {
        m_buttonDefault[3] = 1;
        m_buttonMap[1][3] = 1;
        m_buttonMap[2][3] = 1;
        m_buttonMap[3][3] = 1;
        m_buttonMap[4][3] = 1;
        m_buttonMap[5][3] = 1;
        m_buttonMap[6][3] = 1;
    }
    else
    {
        HR_LOG_Error("robotModel error, robotModel = %d.", m_robotModel);
    }
    HR_LOG_Info("leave Handle::SetRobotModel, robotModel = %d.", m_robotModel);
    return 0;
}

int Handle::SetPressTimeThreshold(int pressTimeThreshold)
{
    if (pressTimeThreshold < 1000)
    {
        HR_LOG_Error("pressTimeThreshold is too small, pressTimeThreshold = %d", pressTimeThreshold);
        return PressTimeThresholdTooSmall;
    }
    m_pressTimeThreshold = pressTimeThreshold;
    return 0;
}

int Handle::SetDelayTime(int delayTime)
{
    if (delayTime != 50 || delayTime != 100 || delayTime != 200)
    {
        HR_LOG_Error("Wrong delayTime, delayTime = %d", delayTime);
        return WrongDelayTime;
    }
    m_delayTime = delayTime;
    return 0;
}

int Handle::SetHandleEnable(bool handleEnable)
{
    m_handleEnable = handleEnable;
    HR_LOG_Info("enter Handle::SetHandleEnable. m_handleEnable = %d.", m_handleEnable);
    return 0;
}

bool Handle::IsPush()
{
    return m_pushFunctionFlag;
}

int Handle::GetPushFunc()
{
    if (m_pushFunctionFlag)
    {
        m_pushFunctionFlag = false;
        m_buttonIndex = 0;
        HR_LOG_Info("Handle push = %d", m_pushFunctionIndex);
        return m_pushFunctionIndex;
    }
    else
    {
        m_pushFunctionIndex = 0;
        return 0;
    }
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
        HR_LOG_Info("Handle push %d", m_pushFunctionIndex);
        m_pushFunctionFlag = false;
        m_pushFunctionIndex = 0;
        m_buttonIndex = 0;
    }
    else
    {
        cJSON_AddNumberToObject(root, "buttonFunction", 0);
    }
    return 0;
}

bool Handle::ExeHandleAction(std::vector<int> endDI)
{
    if (endDI.size() != 4)
    {
        HR_LOG_Error("endDI size is %d. ", endDI.size());
        return false;
    }
    if (endDI == m_buttonDefault) // 如果信号是松开的时候
    {
        // auto start = std::chrono::high_resolution_clock::now();
        OnButtonReleaseAction();
        // auto end = std::chrono::high_resolution_clock::now();
        // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        // if (duration.count() > 10)
        //     HR_LOG_Info("OnButtonReleaseAction time is %d", duration.count());
    }
    else // 如果按下
    {
        // auto start = std::chrono::high_resolution_clock::now();
        OnButtonPressAction(endDI);
        // auto end = std::chrono::high_resolution_clock::now();
        // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        // HR_LOG_Info("OnButtonPressAction time is %d", duration.count());
    }
    return true;
}

void Handle::Start()
{

    if (m_handleEnable)
    {
        std::vector<int> endDIVec;
        if (RecevieEndDI(endDIVec))
        {
            // endDIVec={0,1,1,0};
            // HR_LOG_Info("EndDI: %d,%d,%d,%d",endDIVec[0],endDIVec[1],endDIVec[2],endDIVec[3]);
            // auto start = std::chrono::high_resolution_clock::now();
            if (!ExeHandleAction(endDIVec))
            {
                return;
            }
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
            // auto end = std::chrono::high_resolution_clock::now();
            // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            // if (duration.count() > 10)
            // {
            //     HR_LOG_Info("handle action time is %d", duration.count());
            // }
        }
        else
        {
            HR_LOG_Debug("read endDI fail.");
        }
    }
}

void Handle::GetButtonPressedIndexOf6ButtonHandle(std::vector<int> endDI)
{
    for (int i = 1; i < 7; i++)
    {
        if (endDI == m_buttonMap[i])
        {
            m_buttonIndex = i;
            // HR_LOG_Info("button index is %d", i);
            return;
        }
    }
    // HR_LOG_Debug("wrong button press.");
}

void Handle::SetEndDO()
{
    if(RobotModel::Elfin == m_robotModel)
    {
        return;
    }
    // m_endDO[7] = 1;
    HRIF_SetEndDO(0, 0, 2, 0); // 锁存线置低
    for (int i = 0; i < 8; i++)
    {
        HRIF_SetEndDO(0, 0, 1, m_endDO[i]); // 置数据位
        HRIF_SetEndDO(0, 0, 0, 1);          // 时钟线置高
        HRIF_SetEndDO(0, 0, 0, 0);          // 时钟线置低
    }
    HRIF_SetEndDO(0, 0, 2, 1); // 锁存线置高
    if (!m_lightFlag) //长按保持常亮
    {
        HRIF_SetEndDO(0, 0, 2, 0); // 锁存线置低
    }
}

void Handle::OnButtonReleaseAction()
{
    if (0 == m_buttonIndex)
    {
        m_weldFunction = 0;
        m_lightFlag = false;
        return;
    }
    if (m_buttonIndex > 0)
    {
        m_lightFlag = false;
        HR_LOG_Info("button %d release.", m_buttonIndex);
        for (int i = 0; i < 8; i++)
        {
            m_endDO[i] = 0;
        }
        thread setDO(&Handle::SetEndDO, this);
        setDO.detach();
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
    // auto start = std::chrono::high_resolution_clock::now();
    GetButtonPressedIndexOf6ButtonHandle(endDI);
    // auto end = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // HR_LOG_Info("GetButtonPressedIndexOf6ButtonHandleForPro time is %d", duration.count());

    if (m_buttonIndex > 0)
    {
        if (!m_lightFlag)
        {
            m_lightFlag = true;
            m_endDO[8 - m_buttonIndex] = 1;
            // HR_LOG_Info("EndDO: %d,%d,%d,%d,%d,%d,%d,%d",m_endDO[0],m_endDO[1],m_endDO[2],m_endDO[3],m_endDO[4],m_endDO[5],m_endDO[6],m_endDO[7]);
            thread setDO(&Handle::SetEndDO, this);
            setDO.detach();
            HR_LOG_Info("button %d press.", m_buttonIndex);
        }

        // auto end2 = std::chrono::high_resolution_clock::now();
        // auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - end);
        // HR_LOG_Info("SetEndDO time is %d", duration2.count());
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
            // std::vector<int> endDI;
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
    // auto start = std::chrono::high_resolution_clock::now();
    char buffer[4096]; // 缓冲区大小

    // 从套接字读取数据
    int bytesRead = read(m_sockfd, buffer, sizeof(buffer));
    if (bytesRead <= 0)
    {
        return false;
    }
    if (bytesRead < 700)
    {
        return false;
    }
    // 复制从第12个位置开始的数据到新的缓冲区
    int startPos = 12;                        // 起始位置
    int newDataLength = bytesRead - startPos; // 需要复制的数据长度

    std::string receivedData(buffer + startPos, newDataLength);
    GetEndDIFromString(endDI, receivedData);
    // auto end = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // if (duration.count() > 10)
    //     HR_LOG_Info("RecevieEndDI time is %d", duration.count());

    if (endDI.size() < 4)
    {
        return false;
    }

    return true;
}