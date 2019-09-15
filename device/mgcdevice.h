#ifndef MGCDEVICE_H
#define MGCDEVICE_H
#include <QThread>
#include <stdio.h>
#include <string>

struct device_info
{
    int nSigs;
    int nTrigs;
    int nBlockSize;
    int nSmpRate;
    double nGain;  // gain to mV

};

class mgcDevice:public QThread
{
     Q_OBJECT
public:

    virtual bool open(const char * hostname, int port) = 0 ;
    virtual bool init( ) = 0 ;
    virtual bool close() = 0 ;
   // virtual int  read(char * data , int len) = 0 ;
    //virtual int  write(char *data, int len) = 0 ;
    device_info m_info;
signals:  
    void getMsg(char *msg , int len);

public slots:


};

class mgcDeviceFile:public mgcDevice
{
public:

    explicit mgcDeviceFile() ;
    virtual ~mgcDeviceFile() override;

    virtual bool open(const char * hostname, int port = 0) override ;
    virtual bool init( ) override;
    virtual bool close() override;

protected:
    void run() override;

private:
    short * m_data;
    FILE  *m_fp;
};


#endif // MGCDEVICE_H
