#ifndef COMMON_H
#define COMMON_H

#include <QString>

class Common
{
public:
    Common();

    static QString formatTime(qint64 timeMilliSeconds);
};

#endif // COMMON_H
