#ifndef DEVICEMSGREC_H
#define DEVICEMSGREC_H
#include <QThread>

class deviceMsgRec:QThread
{
public:
    deviceMsgRec();

private:
    void run() override;

};

#endif // DEVICEMSGREC_H
