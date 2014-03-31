/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 31.03.2014 by joerg
*   All Rights reserved
*
*   ChartButler ist Freie Software: Sie können es unter den Bedingungen
*   der GNU Lesser General Public License, wie von der Free Software Foundation,
*   Version 3 der Lizenz oder (nach Ihrer Option) jeder späteren
*   veröffentlichten Version, weiterverbreiten und/oder modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
*   OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
*   Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU Lesser General Public License für weitere Details.
*
*   Sie sollten eine Kopie der GNU Lesser General Public License zusammen mit diesem
*   Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*
*****************************************************************************************/

#include "cdutytype.h"

CDutyType::CDutyType()
{
}

CDutyType::CDutyType(QString pMark, QString pDesc, QTime pTimeFrom, QTime pTimeTo, QTime pTimeElapsed, QTime pMinOffBefore, QTime pMinOffAfter, QColor pRosterColor)
{
    m_Mark = pMark;
    m_Desc = pDesc;
    m_TimeFrom = pTimeFrom;
    m_TimeTo = pTimeTo;
    m_TimeElapsed = pTimeElapsed;
    m_MinOffBefore = pMinOffBefore;
    m_MinOffAfter = pMinOffAfter;
}

QString CDutyType::Mark() const
{
    return m_Mark;
}

void CDutyType::setMark(const QString &Mark)
{
    m_Mark = Mark;
}

QString CDutyType::Desc() const
{
    return m_Desc;
}

void CDutyType::setDesc(const QString &Desc)
{
    m_Desc = Desc;
}

QTime CDutyType::TimeFrom() const
{
    return m_TimeFrom;
}

void CDutyType::setTimeFrom(const QTime &TimeFrom)
{
    m_TimeFrom = TimeFrom;
}

QTime CDutyType::TimeTo() const
{
    return m_TimeTo;
}

void CDutyType::setTimeTo(const QTime &TimeTo)
{
    m_TimeTo = TimeTo;
}

QTime CDutyType::TimeElapsed() const
{
    return m_TimeElapsed;
}

void CDutyType::setTimeElapsed(const QTime &TimeElapsed)
{
    m_TimeElapsed = TimeElapsed;
}

QTime CDutyType::MinOffBefore() const
{
    return m_MinOffBefore;
}

void CDutyType::setMinOffBefore(const QTime &MinOffBefore)
{
    m_MinOffBefore = MinOffBefore;
}

QTime CDutyType::MinOffAfter() const
{
    return m_MinOffAfter;
}

void CDutyType::setMinOffAfter(const QTime &MinOffAfter)
{
    m_MinOffAfter = MinOffAfter;
}

QColor CDutyType::RosterColor() const
{
    return m_RosterColor;
}

void CDutyType::setRosterColor(const QColor &RosterColor)
{
    m_RosterColor = RosterColor;
}








