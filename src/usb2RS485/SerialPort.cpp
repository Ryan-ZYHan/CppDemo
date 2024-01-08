#include "SerialPort.h"
#include <chrono>

SerialPort::SerialPort(const char *port_name)
{
    this->m_cPortName = port_name;
    m_SerialPort = nullptr;
}

SerialPort::~SerialPort() 
{
    close();
}

bool SerialPort::open() 
{
    // HR_LOG_Info("enter SerialPort::open");
    int result = sp_get_port_by_name(m_cPortName, &m_SerialPort);
    if (result != SP_OK) 
    {
        // HR_LOG_Error("Unable to get port information");
        return false;
    }

    result = sp_open(m_SerialPort, SP_MODE_READ_WRITE);
    if (result != SP_OK) 
    {
        // HR_LOG_Error("Unable to open the serial port");
        sp_free_port(m_SerialPort);
        return false;
    }
    // HR_LOG_Info("leave SerialPort::open");
    return true;
}

void SerialPort::close() 
{
    // HR_LOG_Info("enter SerialPort::close");
    if (m_SerialPort) 
    {
        sp_close(m_SerialPort);
        sp_free_port(m_SerialPort);
        m_SerialPort = nullptr;
    }
}

bool SerialPort::configure(int baudrate, int data_bits, int stop_bits, sp_parity parity) 
{
    // HR_LOG_Info("enter SerialPort::configure");
    int result = sp_set_baudrate(m_SerialPort, baudrate);
    if (result != SP_OK) 
    {
        // HR_LOG_Error("Unable to set baud rate");
        return false;
    }

    result = sp_set_bits(m_SerialPort, data_bits);
    if (result != SP_OK) 
    {
        // HR_LOG_Error("Unable to set data bits");
        return false;
    }

    result = sp_set_stopbits(m_SerialPort, stop_bits);
    if (result != SP_OK) 
    {
        // HR_LOG_Error("Unable to set stop bits");
        return false;
    }

    result = sp_set_parity(m_SerialPort, parity);
    if (result != SP_OK) 
    {
        // HR_LOG_Error("Unable to set parity");
        return false;
    }
    // HR_LOG_Info("leave SerialPort::configure");
    return true;
}

int SerialPort::read(void *buffer, size_t size) 
{
    // HR_LOG_Info("enter SerialPort::read");

    int result = sp_blocking_read(m_SerialPort, buffer, size, m_nTimeout);
    if (result < 0) 
    {
        // HR_LOG_Info("Failed to read from the serial port");
        return -1;
    }
  
    // printf("%d从串口读取到数据：%.*s\n", result, result, buffer);
    // HR_LOG_Info("enter SerialPort::leave");
    return result;
}

int SerialPort::write(const void *buffer, size_t size) 
{
    // HR_LOG_Info("enter SerialPort::write");
    int result = sp_blocking_write(m_SerialPort, buffer, size, m_nTimeout);
    if (result < 0) 
    {
        // HR_LOG_Error("Failed to write to the serial port");
        return -1;
    }
    // sp_output_waiting(m_SerialPort);
    // HR_LOG_Info("leave SerialPort::write");
    return result;
}

void SerialPort::setTimeout(int timeout_ms) 
{
     m_nTimeout = timeout_ms;
}

const char* SerialPort::getError() 
{
    // HR_LOG_Info("enter SerialPort::getError");
    return sp_last_error_message();
}