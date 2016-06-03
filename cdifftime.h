/********************************************************************
*
*   File: cdifftime.h    Class: CDiffTime
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2016 Joerg Pauly
*   Created 02.06.2016 by joerg
*   All Rights reserved
*
*   Alle Programme der MEGA-Serie sind Freie Software:
*   Sie können sie unter den Bedingungen
*   der GNU Lesser General Public License, wie von der
*   Free Software Foundation, Version 3 der Lizenz oder
*   (nach Ihrer Option) jeder späteren veröffentlichten
*   Version, weiterverbreiten und/oder modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es nützlich
*   sein wird, aber OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt;
*   sogar ohne die implizite Gewährleistung der MARKTFÄHIGKEIT
*   oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU Lesser General Public License für weitere Details.
*
*   Sie sollten eine Kopie der GNU Lesser General Public License
*   zusammen mit diesem Programm erhalten haben.
*   Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*
********************************************************************/
#ifndef CDIFFTIME_H
#define CDIFFTIME_H

#include <QTime>
#include <QString>

class CDiffTime
{
private:
    int m_Hour;
    int m_Min;
    int m_totalMins;
    int m_totalSecs;

    void makeTotalTime();

public:
    CDiffTime();
    CDiffTime(QTime pTime);
    CDiffTime(float pTime);

    int Hour() const;
    void setHour(int Hour);
    int Min() const;
    void setMin(int Min);
    int totalMins() const;
    void setTotalMins(int totalMins);
    int totalSecs() const;
    void setTotalSecs(int totalSecs);

    QString toString();
    double toNumber();
};

#endif // CDIFFTIME_H
