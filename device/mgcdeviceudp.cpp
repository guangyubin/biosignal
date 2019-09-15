#include "mgcdeviceudp.h"

mgcDeviceUDP::mgcDeviceUDP()
{
    mSocket = nullptr;
}

 mgcDeviceUDP::~mgcDeviceUDP()
 {

 }
 bool mgcDeviceUDP:: open(const char * hostname, int port)
 {
      mSocket = new QUdpSocket;
      mSocket->bind(QHostAddress(hostname),quint16(port));
      connect(mSocket,SIGNAL(readyRead()),this,SLOT(read_data()));
      return true;
 }

 bool mgcDeviceUDP::init( )
 {
    return false;
 }

 bool mgcDeviceUDP::close()
 {
return false;
 }

 void mgcDeviceUDP::run()
 {

 }
void mgcDeviceUDP::read_data()
{
    while(mSocket->hasPendingDatagrams()) //拥有等待的数据报
     {
         QByteArray datagram; //拥于存放接收的数据报
         datagram.resize(mSocket->pendingDatagramSize());
         mSocket->readDatagram(datagram.data(),datagram.size());
         unsigned short size = datagram.size();
         unsigned char msg[10] = {0};
         memcpy(msg, datagram.data(), size);
         unsigned short arr = msg[0];
         arr = (arr<<8)+msg[1];
         qDebug()<<msg[0]<<msg[1]<<msg[2]<<msg[3];
     }

}
