#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <libserialport.h>
// #include "elog.h"


class SerialPort 
{
public:
    SerialPort(const char *port_name);
    ~SerialPort();

    /**
     * @brief Open the specified serial port.
     * 
     * @return true 
     * @return false 
     */
    bool open();

    /**
     * @brief close the specified serial port.
     * 
     */
    void close();

    /**
     * @brief configure serialport param
     * 
     * @param baudrate Set the baud rate for the specified serial port.
     * @param data_bits Set the data bits for the specified serial port
     * @param stop_bits Set the stop bits for the specified serial port
     * @param parity Set the parity setting for the specified serial port
     * @return true 
     * @return false 
     */
    bool configure(int baudrate, int data_bits, int stop_bits, sp_parity parity);

    /**
     * @brief Read bytes from the specified serial port, blocking until complete
     * 
     * @param buffer Buffer in which to store the bytes read. Must not be NULL.
     * @param size Requested number of bytes to read.
     * @return int 0:success, <0 fail
     */
    int read(void *buffer, size_t size);

    /**
     * @brief Write bytes to the specified serial port, blocking until complete.
     * 
     * @param buffer Buffer containing the bytes to write. Must not be NULL
     * @param size Requested number of bytes to write.
     * @return int 0:success, <0 fail
     */
    int write(const void *buffer, size_t size);

    /**
     * @brief Set the Timeout object
     * 
     * @param timeout_ms Timeout in milliseconds, or zero to wait indefinitely
     */
    void setTimeout(int timeout_ms);

    /**
     * @brief Get the Error object
     * 
     * @return const char* 
     */
    const char* getError();

private:
    struct sp_port *m_SerialPort;
    const char *m_cPortName;
    int  m_nTimeout = 1000;
};