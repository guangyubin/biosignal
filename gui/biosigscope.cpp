#include "biosigscope.h"
#include <QPainter>
#include <QRect>
#include <QDebug>

 BiosigScope::BiosigScope (QWidget* parent)
 {

     this->setAttribute(Qt::WA_StyledBackground,true);
     this->setStyleSheet("background-color: rgb(255,255, 255)");
     this->setMouseTracking(true);

     m_buffer = nullptr;
     m_bChanShow = nullptr;
     _canvas = new QPixmap(size());
     _canvas->fill(Qt::white);

     m_orignOffsetX = 45 ;
     m_bInit = false;

 }
BiosigScope::~BiosigScope()
{
    delete _canvas;
}

// nSecInOneScreen
bool BiosigScope::set(unsigned int  nBlockSize, unsigned int nSigChan, unsigned int nTrgChan ,unsigned int nSamplingRate,unsigned int nSecInOneScreen)
{


    m_nSamplingRate = nSamplingRate;
    m_nSecInOneScreen = nSecInOneScreen;
    m_nSigChan = nSigChan;
    m_nTrgChan = nTrgChan;
    m_nBlockSize = nBlockSize;
    m_nChanNum = m_nSigChan+m_nTrgChan;

    m_nBlockNum = m_nSecInOneScreen*m_nSamplingRate / m_nBlockSize;   // 所需保存的数据包的个数

    m_curPos = 0;
    DELETE_ARRAY(m_buffer)

    DELETE_ARRAY(m_bChanShow)
    m_buffer = new double [MAX_NSEC_IN_ONE_SCREEN*m_nSamplingRate*m_nChanNum] ;


    m_fADUnit = 1.0;
    m_orignOffsetX = 45 ;
    m_bottomOffsetY = 40;


    m_bChanShow = new int [m_nChanNum];
    for (unsigned int i = 0 ; i < m_nChanNum ; i++)
    {
        m_bChanShow[i] = 1;

    }
    m_nSigShow = m_nSigChan;
    m_nInputDataLength = 0;


    m_bInit = true;
    drawLabel();
    return 1;

}


void BiosigScope::showSignal(double *pData)
{
    m_nInputDataLength += m_nBlockSize;
    m_nInputDataLength %=  m_nBlockSize*m_nBlockNum;
    memcpy(m_buffer+(m_curPos)*m_nBlockSize*m_nChanNum, pData, sizeof(double)*m_nBlockSize*m_nChanNum);

    drawSignal(int(m_curPos*m_nBlockSize),int(m_curPos*m_nBlockSize+m_nBlockSize));

    m_curPos ++;
    if (m_curPos == m_nBlockNum)
    {
        m_curPos = 0 ;
    }
}


QPoint BiosigScope::dataAxisToScreen(int i , int ch)
{


    if(i < 0 ) i = 0 ;
    if(i >= int(m_nBlockNum*m_nBlockSize)) i = int(m_nBlockNum*m_nBlockSize -1) ;

   double stepX =   (this->rect().width() - m_orignOffsetX) / (1.0*m_nBlockNum*m_nBlockSize);

    double v = double( (m_buffer[(i*m_nChanNum+ch)] - m_buffer[ch])*m_fADUnit + chanPositionInScreen(ch));
    double x = m_orignOffsetX + i *stepX;

    return QPoint(int(x), int(v));
}

 int    BiosigScope::chanPositionInScreen(int ch)
 {
     QRect rect = this->rect();
     double setpY = (rect.height() - m_bottomOffsetY) / (1.0*(m_nSigShow));
      double y0 = setpY/2 + 5;
      double ybase = y0 + ch*setpY;
      return int(ybase);

 }
void BiosigScope:: drawLabel()
{
    if(!m_bInit) return;
      QPainter p(_canvas);
      for( int ch = 0 ; ch < int(m_nSigShow) ; ch++)
      {
        QString s ;
        s.sprintf("ch%d" , ch);
         p.drawText(0,chanPositionInScreen(ch),s);
      }
      this->repaint(QRect(0,0,m_orignOffsetX,this->rect().height()));
}
void   BiosigScope:: drawSignal(int istart, int iend , bool clearall)
{
    if(!m_bInit) return;
    QPainter p(_canvas);
    QPainterPath path;

    int x0 = dataAxisToScreen(istart-1,0).x();
    int x1 = dataAxisToScreen(iend-1,0).x();


    QRect rc;
    if(clearall)
        rc = this->rect();
    else
        rc = QRect(x0,0,x1-x0,this->rect().height() );

    p.eraseRect(rc);
    for (int ch = 0 ; ch < int(m_nSigChan) ; ch++)
    {
        if (m_bChanShow[ch] == 1)
        {

            path.moveTo(dataAxisToScreen(istart-1,ch));
            for(int i = istart ; i < iend ;i++ )
            {

                path.lineTo(dataAxisToScreen(i,ch));
            }

        }
    }

     QPainterPath path_axis;
     for(int i = istart ; i < iend ; i++)
     {
         int smallLine = m_nSamplingRate / 5;
         if (i % smallLine == 0 && i%m_nSamplingRate !=0)
         {
             int x0 = dataAxisToScreen(i,0).x();
             path_axis.moveTo( x0 , this->rect().top());
             path_axis.lineTo( x0 , this->rect().bottom()- m_bottomOffsetY);
         }
     }
     QPainterPath path_axis_1sec;
     for(int i = istart ; i < iend ; i++)
     {

         if (i % m_nSamplingRate == 0 && i !=0)
         {
             int x0 = dataAxisToScreen(i,0).x();
             path_axis_1sec.moveTo( x0 , this->rect().top());
             path_axis_1sec.lineTo( x0 , this->rect().bottom()- m_bottomOffsetY);
         }
     }

    p.drawPath(path);

    QPen pen(QColor::fromRgb(255, 153, 71), 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    p.setPen(pen);
    p.drawPath(path_axis);


    QPen pen1(QColor::fromRgb(255, 153, 71), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    p.setPen(pen1);
    p.drawPath(path_axis_1sec);
    qDebug() <<istart <<  iend << endl;

    this->repaint(rc);
}

void BiosigScope::zoomIn()
{

    m_fADUnit/=2.0;
    drawSignal(0, m_curPos*m_nBlockSize,true);
}
void BiosigScope::zoomOut()
{

     m_fADUnit*=2.0;
         drawSignal(0, m_curPos*m_nBlockSize,true);
}

void  BiosigScope::zoomAuto()
{

    m_fADUnit = 1.0;
      drawSignal(0, m_curPos*m_nBlockSize,true);
}
void BiosigScope::timeLineDec()
{

    m_nSecInOneScreen--;
    if(m_nSecInOneScreen == 0 )
    {
        m_nSecInOneScreen = 1;
        return;
    }
    m_nBlockNum = m_nSecInOneScreen*m_nSamplingRate / m_nBlockSize;   // 所需保存的数据包的个数
      m_curPos = 0;
       drawSignal(0, m_curPos*m_nBlockSize,true);


    //Reset();

}
void BiosigScope::timeLineInc()
{

    m_nSecInOneScreen++;
    if(m_nSecInOneScreen > 10 )
    {
        m_nSecInOneScreen = 10;
        return;
    }
    m_nBlockNum = m_nSecInOneScreen*m_nSamplingRate / m_nBlockSize;   // 所需保存的数据包的个数

    m_curPos = 0;
    drawSignal(0, m_curPos*m_nBlockSize,true);


    //Reset();

}
void BiosigScope::setChanShow(int * chanShow)
{

    int m = 0 ;
    for (int i= 0 ; i< m_nSigShow; i++)
    {
        m_bChanShow[i] = chanShow[i];
        if (m_bChanShow[i] == 1)
        {
            m++;
        }
    }

    m_nSigShow = m ;
    drawSignal(0, m_curPos*m_nBlockSize,true);

}

void BiosigScope::paintEvent(QPaintEvent *evt)
{


    QPainter painter(this);
    painter.drawPixmap(evt->rect(), *_canvas ,evt->rect());


}

void BiosigScope::resizeEvent(QResizeEvent *event)
{

    _canvas = new QPixmap(event->size());
    _canvas->fill(Qt::white);
  drawLabel();
    drawSignal(0, m_curPos*m_nBlockSize,true);

//    qDebug() <<    _canvas->size();


}
