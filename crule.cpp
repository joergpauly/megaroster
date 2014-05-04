#include "crule.h"

CRule::CRule(int pID)
{
    QSqlQuery lqry;
    lqry.prepare("SELECT * FROM tblDailyRule WHERE ID = :PID;");
    lqry.bindValue(":PID", pID);
    lqry.exec();
    lqry.first();
    m_ID = lqry.value(lqry.record().indexOf("ID")).toInt();
    m_Name = lqry.value(lqry.record().indexOf("Desc")).toString();
    lqry.prepare("SELECT * FROM tblDrDty WHERE DRID = :DRID;");
    lqry.bindValue(":DRID",m_ID);
    lqry.exec();
    lqry.first();
    m_tList = new QList<CDutyType>();
    while(lqry.isValid())
    {
        CDutyType ltyp(lqry.value(lqry.record().indexOf("DTID")).toInt());
        m_tList->append(ltyp);
        lqry.next();
    }
}

QList<CDutyType> *CRule::tList() const
{
    return m_tList;
}

void CRule::setTList(QList<CDutyType> *tList)
{
    m_tList = tList;
}

int CRule::ID() const
{
    return m_ID;
}

void CRule::setID(int ID)
{
    m_ID = ID;
}

QString CRule::Name() const
{
    return m_Name;
}

void CRule::setName(const QString &Name)
{
    m_Name = Name;
}



