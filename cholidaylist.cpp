/****************************************************************************************
*
*   File: cholidaylist.cpp    Class: CHolidayList
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2016 Joerg Pauly
*   Created 02.01.2016 by joerg
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
#include "cholidaylist.h"

CHolidayList::CHolidayList()
{
    loadListFromDb();
}

void CHolidayList::loadListFromDb()
{
    QSqlQuery lqry;
    lqry.prepare("SELECT * FROM tblHolidays ORDER BY mvbl, iMonth, iDay ASC;");
    lqry.exec();
    lqry.first();
    while(lqry.isValid())
    {
        CHolidayData lHd;
        lHd.setID(lqry.value(lqry.record().indexOf("ID")).toInt());
        lHd.setDay(lqry.value(lqry.record().indexOf("iDay")).toInt());
        lHd.setMonth(lqry.value(lqry.record().indexOf("iMonth")).toInt());
        lHd.setDescription(lqry.value(lqry.record().indexOf("Descr")).toString());
        lHd.setMovable(lqry.value(lqry.record().indexOf("mvbl")).toBool());
        this->append(lHd);
        lqry.next();
    }
}
