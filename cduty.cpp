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

CDuty::CDuty(int pid)
{
    QSqlQuery* lqry = new QSqlQuery();
    lqry->prepare("SELECT * FROM tblDuty WHERE ID = :ID;");
    lqry->bindValue(":ID", QVariant(pid));
    lqry->exec();
    lqry->first();    
    m_id = lqry->value(lqry->record().indexOf("ID")).toInt();
    m_Date = QDate::fromString(lqry->value(lqry->record().indexOf("DDate")).toString(),"yyyy-MM-dd");
    m_TimeFrom = QTime::fromString(lqry->value(lqry->record().indexOf("TimeFrom")).toString(),"hh:mm:ss.zzz");
    m_TimeTo = QTime::fromString(lqry->value(lqry->record().indexOf("TimeTo")).toString(),"hh:mm:ss.zzz");
    m_Duration = QTime::fromString(lqry->value(lqry->record().indexOf("Dura")).toString(),"hh:mm:ss.zzz");
    m_TimeFrom2 = QTime::fromString(lqry->value(lqry->record().indexOf("TimeFrom2")).toString(),"hh:mm:ss.zzz");
    m_TimeTo2 = QTime::fromString(lqry->value(lqry->record().indexOf("TimeTo2")).toString(),"hh:mm:ss.zzz");
    m_Duration2 = QTime::fromString(lqry->value(lqry->record().indexOf("Dura2")).toString(),"hh:mm:ss.zzz");
    m_Typ = new CDutyType(lqry->value(lqry->record().indexOf("TypeID")).toInt());
    m_Kollege = new CPersonal(lqry->value(lqry->record().indexOf("PersID")).toInt());
}

QDate CDuty::Date() const
{
    return m_Date;
}

void CDuty::setDate(const QDate &Date)
{
    m_Date = Date;
}

CPersonal *CDuty::Kollege() const
{
    return m_Kollege;
}

void CDuty::setKollege(const CPersonal &Kollege)
{
    m_Kollege = new CPersonal();
    *m_Kollege = Kollege;
}

CDutyType *CDuty::Typ() const
{
    return m_Typ;
}

void CDuty::setTyp(const CDutyType &Typ)
{
    m_Typ = new CDutyType();
    *m_Typ = Typ;
}

int CDuty::id() const
{
    return m_id;
}

void CDuty::setId(int id)
{
    m_id = id;
}

QTime CDuty::TimeFrom() const
{
    return m_TimeFrom;
}

void CDuty::setTimeFrom(const QTime &TimeFrom)
{
    m_TimeFrom = TimeFrom;
}

QTime CDuty::TimeTo() const
{
    return m_TimeTo;
}

void CDuty::setTimeTo(const QTime &TimeTo)
{
    m_TimeTo = TimeTo;
}

QTime CDuty::TimeFrom2() const
{
    return m_TimeFrom2;
}

void CDuty::setTimeFrom2(const QTime &TimeFrom2)
{
    m_TimeFrom2 = TimeFrom2;
}

QTime CDuty::TimeTo2() const
{
    return m_TimeTo2;
}

void CDuty::setTimeTo2(const QTime &TimeTo2)
{
    m_TimeTo2 = TimeTo2;
}

QTime CDuty::Duration() const
{
    return m_Duration;
}

void CDuty::setDuration(const QTime &Duration)
{
    m_Duration = Duration;
}

QTime CDuty::Duration2() const
{
    return m_Duration2;
}

void CDuty::setDuration2(const QTime &Duration2)
{
    m_Duration2 = Duration2;
}










