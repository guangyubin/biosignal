#ifndef MGCDEVICESERIAL_H
#define MGCDEVICESERIAL_H

#include <QSerialPort>
#include "mgcdevice.h"
class mgcdeviceSerial:public mgcDevice
{
public:
    mgcdeviceSerial();
    virtual ~mgcdeviceSerial() override;
public:

    virtual bool open(const char * hostname, int port) override ;
    virtual bool init( ) override;
    virtual bool close() override;

protected:
    void run() override;

    void read_data();

private:

    QSerialPort *mSerialPort;
};

#endif // MGCDEVICESERIAL_H
