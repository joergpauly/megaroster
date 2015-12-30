/****************************************************************************************
*
*   File: cholidaydata.h    Class: CHolidayData
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
#ifndef CHOLIDAYDATA_H
#define CHOLIDAYDATA_H

#include <QString>

class CHolidayData
{
public:
    CHolidayData();
    CHolidayData(int pDay, int pMonth, bool pMovable, QString pDescription);

    int Day() const;
    void setDay(int Day);

    int Month() const;
    void setMonth(int Month);

    bool Movable() const;
    void setMovable(bool Movable);

    QString Description() const;
    void setDescription(const QString &Description);

private:
    int      m_Day;
    int      m_Month;
    bool     m_Movable;
    QString  m_Description;

};

#endif // CHOLIDAYDATA_H
