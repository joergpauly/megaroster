/****************************************************************************************
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 04.04.2014 by joerg
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

/* Liste aller Feiertage
        1,1,jahr,   "Neujahr"
        15,8,jahr,  "Mariä Himmelfahrt"
        1,11,jahr,  "Allerheiligen"
        8,12,jahr,  "Maria Empfängnis"
        24,12,jahr, "Heilig Abend"
        25,12,jahr, "1.Weihnachtsfeiertag"
        26,12,jahr, "2.Weihnachtsfeiertag"
        31.12.jahr, "Sylvester"
        // von Ostern abhängige Feiertage
        Ostern-7,   "Palmsonntag"
        Ostern-2,   "Karfreitag"
        Ostern-1,   "Karsamstag"
        Ostern,     "Ostersonntag"
        Ostern+1,   "Ostermontag"
        Ostern+39,  "Christi Himmelfahrt"
        Ostern+49,  "Pfingstsonntag"
        Ostern+50,  "Pfingstmontag"
        Ostern+60,  "Fronleichnam"
*/


#ifndef CHOLIDAY_H
#define CHOLIDAY_H

#include <QDate>
#include <QList>

class CHoliday
{
public:
    CHoliday(int pJahr);
    ~CHoliday();
    bool checkForHoliday(QDate pDate);

private:
    QDate m_osterSonntag;
    QList<QDate>* m_holidayList;
    void makeHolidayList();
    void makeOsterSonntag(int pJahr);

};

#endif // CHOLIDAY_H
