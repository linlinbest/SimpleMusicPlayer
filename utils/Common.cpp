#include "Common.h"

Common::Common()
{

}

/**
 * @brief convert milliseconds to time in minites and seconds
 * @param timeMilliSeconds
 * @return formatted string of time in mm:ss
 */
QString Common::formatTime(qint64 timeMilliSeconds) {
    qint64 seconds = timeMilliSeconds / 1000;
    const qint64 minutes = seconds / 60;
    seconds -= minutes * 60;
    return QStringLiteral("%1:%2")
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}
