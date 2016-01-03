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
        // von Ostern abhängige Feiertage
        Ostern-48   "Rosenmontag"
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

#include "choliday.h"

CHoliday::CHoliday(int pJahr)
{
    makeOsterSonntag(pJahr);
    makeHolidayList();
}

CHoliday::~CHoliday()
{
    delete m_holidayList;
}

bool CHoliday::checkForHoliday(QDate pDate)
{

    for(int i = 0; i < m_holidayList->count(); i++)
    {

        if(m_holidayList->at(i) == pDate)
        {
            return true;
        }

    }

    return false;
}

//TODO: Feiertagsliste aus Datenbank laden.
void CHoliday::makeHolidayList()
{    
    m_holidayList = new QList<QDate>();
<<<<<<< .mine
<<<<<<< .working
<<<<<<< .working
    QDate ldate(m_osterSonntag.year(),1,1);
    m_holidayList->append(ldate);
    ldate = QDate(m_osterSonntag.year(),5,1);
    m_holidayList->append(ldate);
    ldate = QDate(m_osterSonntag.year(),10,3);
    m_holidayList->append(ldate);
    ldate = QDate(m_osterSonntag.year(),11,1);
    m_holidayList->append(ldate);
    ldate = QDate(m_osterSonntag.year(),12,24);
    m_holidayList->append(ldate);
    ldate = QDate(m_osterSonntag.year(),12,25);
    m_holidayList->append(ldate);
    ldate = QDate(m_osterSonntag.year(),12,26);
    m_holidayList->append(ldate);
    ldate = QDate(m_osterSonntag.year(),12,31);
    m_holidayList->append(ldate);
    ldate = m_osterSonntag.addDays(-48);
    m_holidayList->append(ldate);
    ldate = m_osterSonntag.addDays(-2);
    m_holidayList->append(ldate);
    ldate = m_osterSonntag.addDays(1);
    m_holidayList->append(ldate);
    ldate = m_osterSonntag.addDays(39);
    m_holidayList->append(ldate);
    ldate = m_osterSonntag.addDays(50);
    m_holidayList->append(ldate);
    ldate = m_osterSonntag.addDays(60);
    m_holidayList->append(ldate);
=======
    CHolidayList *lLst = new CHolidayList();
    QDate *lDate;

    for(int i = 0; i < lLst->count(); i++)
    {
        if(!lLst->at(i).Movable())
        {
            lDate = new QDate(m_osterSonntag.year(), lLst->at(i).Month(), lLst->at(i).Day());
        }
        else
        {
            *lDate = m_osterSonntag.addDays(lLst->at(i).Day());
        }
        m_holidayList->append(*lDate);
    }
>>>>>>> .r156
=======
    CHolidayList *lLst = new CHolidayList();
    QDate *lDate;

    for(int i = 0; i < lLst->count(); i++)
    {
        if(!lLst->at(i).Movable())
        {
            lDate = new QDate(m_osterSonntag.year(), lLst->at(i).Month(), lLst->at(i).Day());
        }
        else
        {
            *lDate = m_osterSonntag.addDays(lLst->at(i).Day());
        }
        m_holidayList->append(*lDate);
    }
>>>>>>> .merge-right.r155
=======
    CHolidayList *lLst = new CHolidayList();
    QDate *lDate;

    for(int i = 0; i < lLst->count(); i++)
    {
        if(!lLst->at(i).Movable())
        {
            lDate = new QDate(m_osterSonntag.year(), lLst->at(i).Month(), lLst->at(i).Day());
        }
        else
        {
            *lDate = m_osterSonntag.addDays(lLst->at(i).Day());
        }
        m_holidayList->append(*lDate);
    }
>>>>>>> .merge-right.r155
}

void CHoliday::makeOsterSonntag(int pJahr)
{
    int a = pJahr % 19;
    int b = pJahr / 100;
    int c = pJahr % 100;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - (b/4) - g + 15) % 30;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * (c / 4) - h - k) % 7;
    int m = (a + 11 * h + 22 * l) / 451;
    int nMonth = (h + l - 7 * m + 114) / 31;
    int nDay = (h + l - 7 * m + 114) % 31 + 1;
    m_osterSonntag.setDate(pJahr,nMonth,nDay);
}
