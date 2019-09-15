#include "mgcdevice.h"

#include <QDebug>
mgcDeviceFile::mgcDeviceFile()
{
    m_fp = nullptr;
    m_data = nullptr;


}
mgcDeviceFile::~mgcDeviceFile()
{
    if(m_data!=nullptr)
        delete [] m_data;
    if(m_fp!=nullptr)
        fclose(m_fp);

}

 bool mgcDeviceFile:: open(const char * hostname, int port)
 {
     m_fp =  std::fopen(hostname,"rb");
     if(m_fp==nullptr)
     {
         return false;
     }
     m_info.nSigs = 1;
     m_info.nTrigs = 0;
     m_info.nSmpRate = 250;
     m_info.nBlockSize = 50 ;
     m_info.nGain = 200.0;
     m_data = new short[ m_info.nBlockSize];
     return true;
 }
 bool mgcDeviceFile:: init( )
{
     return true;
}
 bool mgcDeviceFile:: close()
 {
      return true;

 }


 void mgcDeviceFile::run()
 {
     forever {
         if(m_fp!=nullptr)
         {
             fread(m_data,sizeof(short),m_info.nBlockSize,m_fp);
             msleep(200);
             emit getMsg((char*)m_data,sizeof(int)*m_info.nBlockSize);
             qDebug()<< "hell" << endl;
         }
     }

 }

