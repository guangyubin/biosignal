#ifndef MGCDEVICEUDP_H
#define MGCDEVICEUDP_H
#include "mgcdevice.h"
#include <QUdpSocket>
class mgcDeviceUDP:public mgcDevice
{
public:
    mgcDeviceUDP();
    virtual ~mgcDeviceUDP() override;
public:

    virtual bool open(const char * hostname, int port) override ;
    virtual bool init( ) override;
    virtual bool close() override;

protected:
    void run() override;

    void read_data();

private:

    QUdpSocket *mSocket;

};

#endif // MGCDEVICEUDP_H
