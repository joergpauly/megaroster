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

#include "cdutytype.h"

CDutyType::CDutyType()
{
}

CDutyType::CDutyType(QString pMark)
{
    QSqlQuery *lqry = new QSqlQuery();
    lqry->prepare("SELECT * FROM tblDutyTypes WHERE Mark = :Mark;");
    lqry->bindValue(":Mark", QVariant::fromValue(pMark));
    lqry->exec();
    lqry->first();
    readDB(lqry);
}

CDutyType::CDutyType(int pID)
{
    QSqlQuery *lqry = new QSqlQuery();
    lqry->prepare("SELECT * FROM tblDutyTypes WHERE ID = :ID;");
    lqry->bindValue(":ID", pID);
    lqry->exec();
    lqry->first();
    readDB(lqry);
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

QTime CDutyType::TimeFrom2() const
{
    return m_TimeFrom2;
}

void CDutyType::setTimeFrom2(const QTime &TimeFrom2)
{
    m_TimeFrom2 = TimeFrom2;
}

QTime CDutyType::TimeTo2() const
{
    return m_TimeTo2;
}

void CDutyType::setTimeTo2(const QTime &TimeTo2)
{
    m_TimeTo2 = TimeTo2;
}

QTime CDutyType::TimeElapsed2() const
{
    return m_TimeElapsed2;
}

void CDutyType::setTimeElapsed2(const QTime &TimeElapsed2)
{
    m_TimeElapsed2 = TimeElapsed2;
}

int CDutyType::RosterColorR() const
{
    return m_RosterColorR;
}

void CDutyType::setRosterColorR(int RosterColorR)
{
    m_RosterColorR = RosterColorR;
}

int CDutyType::RosterColorG() const
{
    return m_RosterColorG;
}

void CDutyType::setRosterColorG(int RosterColorG)
{
    m_RosterColorG = RosterColorG;
}

int CDutyType::RosterColorB() const
{
    return m_RosterColorB;
}

void CDutyType::setRosterColorB(int RosterColorB)
{
    m_RosterColorB = RosterColorB;
}

int CDutyType::id() const
{
    return m_id;
}

void CDutyType::setId(int id)
{
    m_id = id;
}

void CDutyType::readDB(QSqlQuery* pqry)
{
    m_id = pqry->value(pqry->record().indexOf("ID")).toInt();
    m_Mark = pqry->value(pqry->record().indexOf("Mark")).toString();
    m_Desc = pqry->value(pqry->record().indexOf("Decr")).toString();
    m_TimeFrom = QTime::fromString(pqry->value(pqry->record().indexOf("TimeFrom")).toString(),"hh:mm:ss.zzz");
    m_TimeTo = QTime::fromString(pqry->value(pqry->record().indexOf("TimeTo")).toString(),"hh:mm:ss.zzz");
    m_TimeElapsed = QTime::fromString(pqry->value(pqry->record().indexOf("TimeElapsed")).toString(),"hh:mm:ss.zzz");
    m_TimeFrom2 = QTime::fromString(pqry->value(pqry->record().indexOf("TimeFrom2")).toString(),"hh:mm:ss.zzz");
    m_TimeTo2 = QTime::fromString(pqry->value(pqry->record().indexOf("TimeTo2")).toString(),"hh:mm:ss.zzz");
    m_TimeElapsed2 = QTime::fromString(pqry->value(pqry->record().indexOf("TimeElapsed2")).toString(),"hh:mm:ss.zzz");
    m_RosterColorR = pqry->value(pqry->record().indexOf("ColorR")).toInt();
    m_RosterColorG = pqry->value(pqry->record().indexOf("ColorG")).toInt();
    m_RosterColorB = pqry->value(pqry->record().indexOf("ColorB")).toInt();
}

