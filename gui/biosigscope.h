#ifndef BIOSIGSCOPE_H
#define BIOSIGSCOPE_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>

#define MAX_NSEC_IN_ONE_SCREEN  10    // 一屏幕中最长的时间长度

#ifndef DELETE_ARRAY
#define DELETE_ARRAY(x) if (x != NULL) {delete[] x; x = NULL;}
#define DELETE_OBJECT(x) if (x != NULL) {delete   x; x = NULL;}
#endif

class BiosigScope : public QWidget
{

public:

    BiosigScope (QWidget* parent);
    ~BiosigScope();
    bool set(  unsigned int  nBlockSize, unsigned int m_nSigChan, unsigned int m_nTrgChan ,unsigned int nSamplingRate,unsigned int nSecInOneScreen);
    void showSignal(double *sig);


protected:
    void paintEvent(QPaintEvent *evt);

    void resizeEvent(QResizeEvent *event);


private:
    void         setChanShow(int * chanShow);  //设置显示的导联


    void drawSignal(int istart, int iend, bool clearall = false);
    void drawLabel();

    QPoint dataAxisToScreen(int i , int ch );
    int    chanPositionInScreen(int ch);

public:
    void         zoomOut();      // 放大
    void         zoomIn();      // 缩小
    void         zoomAuto();
    void         timeLineInc();   //时间轴增加
    void         timeLineDec();   // 时间轴减小
    void         setSavedPen(bool saved);   // 保存数据时，使用蓝色线条显示
    void         reset();

private:
    unsigned int                      m_nSigChan;
    unsigned int                      m_nTrgChan;
    unsigned int                      m_nChanNum;
    unsigned int                      m_nSamplingRate;  // 采样率
    unsigned int                      m_nBlockSize;	    // 数据块大小
    unsigned int                      m_nBlockNum;      // 最多的数据块个数
    unsigned int                      m_nSecInOneScreen;    // 一屏中总的时间长度
    double                            *m_buffer;


    unsigned long             m_curPos;


    double                    m_preEventValue;
    int                      *m_bChanShow;   //是否显示该导联。
    unsigned int              m_nSigShow;   //显示的导联个数
   // 缩放

    double                    m_fADUnit;

    long                      m_orignOffsetX;
    long                      m_bottomOffsetY;

    long                      m_nInputDataLength;

    bool          m_bInit;

        long         m_nCurTime;





    QPixmap *                  _canvas;
};

#endif // BIOSIGSCOPE_H
