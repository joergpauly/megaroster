/********************************************************************
*
*   File: cdifftime.cpp    Class: CDiffTime
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
/*******************************************************************
 *
 *  CDiffTime dient zum Berechnen und Speichern vorzeichenbehafteter
 *  Zeitdifferenzen.
 *
 * ******************************************************************/

#include "cdifftime.h"

CDiffTime::CDiffTime()
{
    m_Hour = 0;
    m_Min = 0;
    m_totalMins = 0;
}

CDiffTime::CDiffTime(QTime pTime)
{
    m_Hour = pTime.hour();
    m_Min = pTime.minute();
    m_totalMins = (m_Hour * 60) + m_Min;   
}

CDiffTime::CDiffTime(float pTime)
{
    m_Hour = pTime;
    m_Min = (pTime - m_Hour) * 60;
    makeTotalTime();
}


int CDiffTime::Hour() const
{
    return m_Hour;
}

void CDiffTime::setHour(int Hour)
{
    m_Hour = Hour;
}

int CDiffTime::Min() const
{
    return m_Min;
}

void CDiffTime::setMin(int Min)
{
    m_Min = Min;
}

int CDiffTime::totalMins() const
{
    return m_totalMins;
}

void CDiffTime::setTotalMins(int totalMins)
{
    m_totalMins = totalMins;
    makeTotalTime();
}

void CDiffTime::setTime(QTime pTime)
{
    m_Hour = pTime.hour();
    m_Min = pTime.minute();
    m_totalMins = (m_Hour * 60) + m_Min;
}

QString CDiffTime::toString()
{
    //TODO: Stringformatierung optimieren!
    QString lStr;
    lStr = QString::number(m_Hour);
    lStr.append(':');
    QString lMin = QString::number(m_Min);

    if(lMin.length() < 2)
    {
        lMin.insert(0,'0');
    }

    lStr.append(lMin);
    return lStr;
}

double CDiffTime::toNumber()
{
    float lTime = m_Hour;
    float lMins = m_Min / 60;
    return (lTime + lMins);
}

void CDiffTime::makeTotalTime()
{
    m_Hour = m_totalMins / 60;
    m_Min = m_totalMins - (m_Hour * 60);
}

