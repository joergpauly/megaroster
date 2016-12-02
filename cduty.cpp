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
    m_Request = lqry->value(lqry->record().indexOf("Status")).toBool();
    m_Date = QDate::fromString(lqry->value(lqry->record().indexOf("DDate")).toString(),"yyyy-MM-dd");
    m_TimeFrom = QTime::fromString(lqry->value(lqry->record().indexOf("TimeFrom")).toString(),"hh:mm:ss.zzz");
    m_TimeTo = QTime::fromString(lqry->value(lqry->record().indexOf("TimeTo")).toString(),"hh:mm:ss.zzz");
    m_Duration = QTime::fromString(lqry->value(lqry->record().indexOf("Dura")).toString(),"hh:mm:ss.zzz");
    m_TimeFrom2 = QTime::fromString(lqry->value(lqry->record().indexOf("TimeFrom2")).toString(),"hh:mm:ss.zzz");
    m_TimeTo2 = QTime::fromString(lqry->value(lqry->record().indexOf("TimeTo2")).toString(),"hh:mm:ss.zzz");
    m_Duration2 = QTime::fromString(lqry->value(lqry->record().indexOf("Dura2")).toString(),"hh:mm:ss.zzz");
    m_Typ = new CDutyType(lqry->value(lqry->record().indexOf("TypeID")).toInt());
    m_Kollege = new CPersonal(lqry->value(lqry->record().indexOf("PersID")).toInt());
    delete lqry;
}

CDuty::CDuty(int pPid, QDate pDate)
{
    // Query holen
    QSqlQuery lqry;
    lqry.prepare("SELECT ID FROM tblDuty WHERE PersID = :PID AND DDate = :FDT;");
    lqry.bindValue(":PID", pPid);
    lqry.bindValue(":FDT", pDate.toString("yyyy-MM-dd"));
    // Ausführen und auf erstes Element setzen
    lqry.exec();
    QString err = lqry.lastError().text();
    lqry.first();
    m_id = lqry.value(lqry.record().indexOf("ID")).toInt();
    m_Request = lqry.value(lqry.record().indexOf("Status")).toBool();
    m_Date = QDate::fromString(lqry.value(lqry.record().indexOf("DDate")).toString(),"yyyy-MM-dd");
    m_TimeFrom = QTime::fromString(lqry.value(lqry.record().indexOf("TimeFrom")).toString(),"hh:mm:ss.zzz");
    m_TimeTo = QTime::fromString(lqry.value(lqry.record().indexOf("TimeTo")).toString(),"hh:mm:ss.zzz");
    m_Duration = QTime::fromString(lqry.value(lqry.record().indexOf("Dura")).toString(),"hh:mm:ss.zzz");
    m_TimeFrom2 = QTime::fromString(lqry.value(lqry.record().indexOf("TimeFrom2")).toString(),"hh:mm:ss.zzz");
    m_TimeTo2 = QTime::fromString(lqry.value(lqry.record().indexOf("TimeTo2")).toString(),"hh:mm:ss.zzz");
    m_Duration2 = QTime::fromString(lqry.value(lqry.record().indexOf("Dura2")).toString(),"hh:mm:ss.zzz");
    m_Typ = new CDutyType(lqry.value(lqry.record().indexOf("TypeID")).toInt());
    m_Kollege = new CPersonal(lqry.value(lqry.record().indexOf("PersID")).toInt());
}

CDuty::~CDuty()
{

}

void CDuty::update2Db(QSqlQuery lqry)
{
    lqry.prepare("UPDATE tblDuty SET PersID = :PID, TypeID = :TID, DDate = :DDt, Status = :RQ, TimeFrom = :TF, TimeTo = :TT, Dura = :Dura, TimeFrom2 = :TFF, TimeTo2 = :TTT, Dura2 = :Dura2 WHERE ID = :ID;");
    lqry.bindValue(":PID", m_Kollege->id());
    int tid = m_Typ->id();
    lqry.bindValue(":TID", tid);
    lqry.bindValue(":DDt", m_Date.toString("yyy-MM-dd"));
    lqry.bindValue(":RQ", m_Request);
    QString tf = m_TimeFrom.toString("hh:mm:ss.zzz");
    lqry.bindValue(":TF", tf);
    QString tt = m_TimeTo.toString("hh:mm:ss.zzz");
    lqry.bindValue(":TT", tt);
    QString dur = m_Duration.toString("hh:mm:ss.zzz");
    lqry.bindValue(":Dura", dur);
    QString tf2 = m_TimeFrom2.toString("hh:mm:ss.zzz");
    lqry.bindValue(":TFF", tf2);
    QString tt2 = m_TimeTo2.toString("hh:mm:ss.zzz");
    lqry.bindValue(":TTT", tt2);
    QString dur2 = m_Duration2.toString("hh:mm:ss.zzz");
    lqry.bindValue(":Dura2", dur2);
    lqry.bindValue(":ID", m_id);
    lqry.exec();
}

void CDuty::insert2Db(QSqlQuery lqry)
{
    lqry.prepare("INSERT INTO tblDuty (PersID, DDate, TypeID, Status, TimeFrom, TimeTo, TimeFrom2, TimeTo2, Dura, Dura2) VALUES (:PID, :DATE, :TID, :RQ, :TF, :TT, :TF2, :TT2, :DUR, :DUR2);");
    lqry.bindValue(":PID", m_Kollege->id());
    lqry.bindValue(":DATE", m_Date.toString("yyy-MM-dd"));
    lqry.bindValue(":TID", m_Typ->id());
    lqry.bindValue(":RQ", m_Request);
    lqry.bindValue(":TF", m_TimeFrom.toString("hh:mm:ss.zzz"));
    lqry.bindValue(":TT", m_TimeTo.toString("hh:mm:ss.zzz"));
    lqry.bindValue(":TF2", m_TimeFrom2.toString("hh:mm:ss.zzz"));
    lqry.bindValue(":TT2", m_TimeTo2.toString("hh:mm:ss.zzz"));
    lqry.bindValue(":DUR", m_Duration.toString("hh:mm:ss.zzz"));
    lqry.bindValue(":DUR2", m_Duration2.toString("hh:mm:ss.zzz"));
    lqry.exec();
    m_id = lqry.lastInsertId().toInt();
}

int CDuty::saVeDB()
{
    //Check if there's a record with that ID
    QSqlQuery lqry;
    lqry.prepare("SELECT * FORM tblDuty WHERE ID = :ID;");
    lqry.bindValue(":ID", m_id);
    lqry.exec();
    lqry.first();

    if(lqry.isValid())
    {
        //Record is there; update it.
        update2Db(lqry);
    }
    else
    {
        //New Record
        insert2Db(lqry);
    }

    return m_id;
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

void CDuty::setTyp(QString typ)
{
    m_Typ = new CDutyType(typ);
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

bool CDuty::Request() const
{
    return m_Request;
}

void CDuty::setRequest(bool Request)
{
    m_Request = Request;
}











