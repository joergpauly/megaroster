/****************************************************************************************
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 01.04.2014 by Joerg Pauly
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
#include "cduty.h"

CDuty::CDuty()
{
}

CDuty::CDuty(QDate pDate, CPersonal pKollege, CDutyType pTyp)
{
    m_Date = pDate;
    m_Kollege = pKollege;
    m_Typ = pTyp;
}

QDate CDuty::Date() const
{
    return m_Date;
}

void CDuty::setDate(const QDate &Date)
{
    m_Date = Date;
}

CPersonal CDuty::Kollege() const
{
    return m_Kollege;
}

void CDuty::setKollege(const CPersonal &Kollege)
{
    m_Kollege = Kollege;
}

CDutyType CDuty::Typ() const
{
    return m_Typ;
}

void CDuty::setTyp(const CDutyType &Typ)
{
    m_Typ = Typ;
}



