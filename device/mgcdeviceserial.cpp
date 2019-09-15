#include "mgcdeviceserial.h"

mgcdeviceSerial::mgcdeviceSerial()
{

}


 mgcdeviceSerial::~mgcdeviceSerial()
 {

 }
 bool mgcdeviceSerial:: open(const char * hostname, int port)
 {
      mSerialPort = new QSerialPort;
      mSerialPort->close();
      mSerialPort->setPortName(hostname);

      if (!mSerialPort->open(QIODevice::ReadWrite)) {

          return false;
         }


      return true;
 }

 bool mgcdeviceSerial::init( )
 {
    return false;
 }

 bool mgcdeviceSerial::close()
 {
return false;
 }

 void mgcdeviceSerial::run()
 {

 }
void mgcdeviceSerial::read_data()
{


}
