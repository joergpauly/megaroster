/****************************************************************************************
*
*   File: cholidaydata.cpp    Class: CHolidayData
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 30.12.2015 by joerg
*   All Rights reserved
*
*   Alle Programme der MEGA-Serie sind Freie Software: Sie können sie unter den Bedingungen
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
#include "cholidaydata.h"

CHolidayData::CHolidayData()
{

}

CHolidayData::CHolidayData(int pDay, int pMonth, bool pMovable, QString pDescription)
{
    m_Day = pDay;
    m_Month = pMonth;
    m_Movable = pMovable;
    m_Description = pDescription;
}

/*
 * Getter-/Setter-Funktionen
 */

int CHolidayData::Day() const
{
    return m_Day;
}

void CHolidayData::setDay(int Day)
{
    m_Day = Day;
}

int CHolidayData::Month() const
{
    return m_Month;
}

void CHolidayData::setMonth(int Month)
{
    m_Month = Month;
}

bool CHolidayData::Movable() const
{
    return m_Movable;
}

void CHolidayData::setMovable(bool Movable)
{
    m_Movable = Movable;
}

QString CHolidayData::Description() const
{
    return m_Description;
}

void CHolidayData::setDescription(const QString &Description)
{
    m_Description = Description;
}
