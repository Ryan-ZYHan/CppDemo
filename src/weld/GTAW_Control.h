#ifndef __SP__CONTROL__H_
#define __SP__CONTROL__H_

#include "EIPScanner-master/src/EipCommonInterface.h"
#include "licensing/license-manager.h"
#include "HRSDK/AlgorithmExport.h"
#include "HRSDK/HR_RobotStruct.h"
#include "GTAW_DataCollection.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/calib3d.hpp"
#include "HRSDK/HR_AutoLock.h"
#include "IntelligentLaser.h"
#include "sqlite_interface.h"
#include "GTAW_Algorithms.h"
#include "HRSDK/hansType.h"
#include "GTAW_Constant.h"
#include "GTAW_DataRecv.h"
#include "HRSDK/HR_Pro.h"
#include "SerialPort/SerialPort.h"
#include "modbus.h"
#include "serial.h"
#include "cJSON.h"
#include "elog.h"
#include <opencv2/core.hpp>
#include <sys/resource.h>
#include <semaphore.h>
#include <sys/time.h>
#include <algorithm> 
#include <assert.h>
#include <iostream>
#include <fstream>
#include <numeric>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>
#include <cmath>
#include <ratio>
#include <mutex>
#include <regex>

using namespace std::chrono;
using namespace eipScanner;
using namespace std;
using namespace cv;

class GTAW_Control
{
    public:
        GTAW_Control();                                                                 
        ~GTAW_Control();

        //焊接机
        int Show_GTAW_State(vector<string> &result);
        int GTAW_License_Manager(const vector<string> &param, vector<string> &result);
        double GTAW_Set_Ec(const vector<string> &param,vector<string> &result);
        double GTAW_Set_Voltage(const vector<string> &param,vector<string> &result);

        int GTAW_init();                                         //插件初始化        
        void GTAWDataRecv();
        void ResolveJson();

        //新增
        int ArcOnSet(const vector<string> &param);
        int ArcOn();
        void ArcOffSet(cJSON *arcOffJson);
        //device manage set current and voltage
        void ArcSet(const vector<string> param); 
        //device manage distribute current and voltage
        int WeldSet(); 
        int ArcOff();
        int Materials(const vector<string> &param);
        int StartPushWire();
        int StopPushWire();
        int StartPullWire();
        int StopPullWire();
        int StartFlow();
        int StopFlow();
  
        int Get_CollectionData(vector<string> &result);
        int Get_CollectionStatus(vector<string> &result);
        int Get_CollectionFileNames(const vector<string> &param, vector<string> &result);
        int Get_CollectionHistoryData(const vector<string> &param, vector<string> &result);

        void ExecuteTask();
        void deviceStateCheckTask();
        void StatusMsg_Task();
        int StartTask(const vector<string> &param, vector<string> &result);
        int PauseTask(vector<string> &result);
        int ContinueTask(vector<string> &result);
        int ControlCmd(cJSON *);
        int ControlConditionCmd(cJSON *logic);

        int OpenDevice(const vector<string> &param, vector<string> &result);
        int CloseDevice(const vector<string> &param, vector<string> &result);
        static void getEIPData(const vector<uint8_t>& data);
        // return tast staus, false: no running; true: running
        int GetTaskStatus();
        void SetReservationStatus(const vector<string> &param);
        int StopTask(const vector<string> &param, vector<string> &result);

        void ProcessEvent(int EventNo); // callback function, register at datarecv module. add by yangquanli 20220922

		void HyperthermSet(const vector<string> &param); // 海宝参数设置
	    void HyperthermArcOn(); // 海宝起弧
	    void HyperthermArcOff(); // 海宝收弧
	    int HyperthermOpen(const vector<string> &param); // 海宝开启
	    void HyperthermClose(); // 海宝关机
	    void HyperthermRead(); // 海宝状态读取
        void HyperthermFault(); // 海宝错误码读取
    public:
        atomic<int> m_TaskStatus;
        atomic<int> m_WelderStatus;
        atomic_bool m_reservationStatus;
        atomic_bool m_RF10006;
        mutex RTInfoMutex;   
        GTAW_DataRecv DR;
        ST_RTInfo m_curRTInfo;
        // 正在执行的动作ID
        mutex TaskDataMtx;
        string m_actionID = "";
        atomic_int taskType;
        //判断是否有起弧动作
        atomic_bool isArcOn;
        atomic_bool isArcOnSet;
        //判断是否起弧成功
        atomic_bool isArcOnSuccess; 
        GTAW_common::GTAW_arcOnData arcOnParams;
        GTAW_common::GTAW_arcOnData weldParams;
        GTAW_common::GTAW_acrOffData arcOffParams;
    private:
        int TaskParamReset();
        int GetAllStatus(vector<string>& result);

        int G2R_CI_signal(int bit,int &state);
        int G2R_DI_signal(int bit,int &state);
        int R2G_AO_signal(int bit,int mode,double value);
        int G2R_AI_signal(int bit,double coefficient,double &value);       
        int execInsertOrUpdateSql(map<string, string> &result, bool isUpdate = true);

        bool ArcOnPoll();
        int WeldMaterials(int diameter, int extensions);
        void DeviceParamSet(const vector<string> &param);
        void DeviceParamReset();

        void resetEipData(int pos=1);
        int setParamValue(const GTAW_common::GTAW_arcOnData& data);
        int setFlamaParamValue(const GTAW_common::GTAW_arcOnData &data, int vPos, int cPos);
        void setWeldTECData(const GTAW_common::GTAW_arcOnData &data);
        int setFroniusParamValue(const GTAW_common::GTAW_arcOnData &data);
        int setLorchParamValue(const GTAW_common::GTAW_arcOnData &data);
        int setLorchModbusParamValue(const GTAW_common::GTAW_arcOnData &data);
        int setMillerParamValue(const GTAW_common::GTAW_arcOnData &data);
		int setFlamaRS485ParamValue(const GTAW_common::GTAW_arcOnData &data, int vPos, int cPos);
    	int setHyperthermRS485ParamValue(const GTAW_common::GTAW_arcOnData &data);
        int verifyLicense(const string& licenseFile, vector<string> &result);
        void getLicense(string & licenseInfo);
        void initLicense();

		void CalculateCRC(const char data[], size_t size, unsigned char result[2]);         // CRC-16 Modbus算法 将CRC结果拆分为低八位和高八位，存储在int数组中,先低后高
	    void SetCurrentVoltage(const int &voltage, const int &current, int vPos, int cPos); // 设置RS485协议的下发电流电压报文
	    unsigned char Char2Hex(char c); //将0-f的字符转换成16进制
	    unsigned char Chars2Hex(const char* chars);// 将两个字符转换为一个十六进制数
	    std::vector<unsigned char> Chars2Hexs(const char chars[],int chars_size); // 将一个字符数组每两位转成一个16进制数，返回一个16进制数组
	    unsigned int CalculateLRC(const std::vector<unsigned char>& data); //计算LRC码
        std::string findTTYUSB();//获取系统中usb接口，无则返回""
    private:
        bool ifCondition = false;
        sqlite_interface m_oSqlite;
        static string laserName;
        static string sDeviceName;
        string boxIO;
        GTAW_devicename::deviceParam deviceParams;
        // mutex m_oMutex;
        atomic_bool m_statusMsgTask;
        atomic_bool m_dataSendTask;
        atomic<int> m_ConnectionStatus;
                
        string m_taskID = "";// 正在执行的任务ID
        atomic<int> m_actionRes;
        atomic<int> taskIndex;
        string m_series; // Panasonic series:G/FT
        GTAW_Algorithm GA;
        
        vector<uint8_t> EipData = vector<uint8_t>(37,0);
        vector<uint8_t> Temp_EIPData = vector<uint8_t>(37,0);
        atomic_uint16_t ModbusData[10];
        atomic_uint16_t Temp_ModbusData[10];
        atomic_uint16_t LorchModbusData[8];
        atomic_uint16_t Temp_LorchModbusData[8];
        atomic_uint16_t FlamaModbusData[25];
        atomic_uint16_t Temp_FlamaModbusData[25];
        atomic_uint16_t FroniusModbusData[20];
        atomic_uint16_t Temp_FroniusModbusData[20];
        atomic_uint16_t WeldTECModbusData[6];
        atomic_uint16_t Temp_WeldTECModbusData[6];
        atomic_uint16_t KemppiModbusData[5];
        atomic_uint16_t Temp_KemppiModbusData[5];
		char FlamaRS485Data[59];
	    char Temp_FlamaRS485Data[59];
        atomic_int HyperthermRS485DataSize;
	    char HyperthermRS485Data[31];
	    char Temp_HyperthermRS485Data[31];
        
        int IO_State = -1;
        
        // Trackparams
        mutex TrackMtx;
        mutex dataMtx; //用于通讯数据修改时加锁
        
        //Findparams
        LicenseManager licenseManager;
        string m_sLicenseInfo;

        // cJSON *m_pJsonRoot;
        string m_sJsonParams;

        //通信协议
        eipCommonInterface _pEIP;
        modbus *_pModbus;
		SerialPort _serialPort;
};

#endif // !__SP__CONTROL_H_