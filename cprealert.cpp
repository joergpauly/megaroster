/****************************************************************************************
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 14.04.2014 by joerg
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

#include "cprealert.h"

CPrealert::CPrealert()
{
}

CPrealert::CPrealert(int pPID, QDate pDate)
{
    // Alert aus DB holen
    QSqlQuery *lqry = new QSqlQuery();
    lqry->prepare("SELECT * FROM tblPrealert WHERE PersID = :PID AND DDate = :DAT;");
    lqry->bindValue(":PID", pPID);
    lqry->bindValue(":DAT", pDate.toString("yyyy-MM-dd"));
    lqry->exec();
    lqry->first();
    m_Pers = new CPersonal(lqry->value(lqry->record().indexOf("PersID")).toInt());
    m_paTypes = getTypes(lqry->value(lqry->record().indexOf("ID")).toInt());
}

CPrealert::CPrealert(int pID)
{
    // Alert aus DB holen
    QSqlQuery *lqry = new QSqlQuery();
    lqry->prepare("SELECT * FROM tblPrealert WHERE ID = :ID;");
    lqry->bindValue(":ID", pID);
    lqry->exec();
    lqry->first();
    m_id = lqry->value(lqry->record().indexOf("ID")).toInt();
    m_Date = lqry->value(lqry->record().indexOf("DDate")).toDate();
    m_Pers = new CPersonal(lqry->value(lqry->record().indexOf("PersID")).toInt());
    m_paTypes = getTypes(pID);
}

CPersonal *CPrealert::Pers() const
{
    return m_Pers;
}

void CPrealert::setPers(CPersonal *Pers)
{
    m_Pers = Pers;
}

QList<CPrealertType> *CPrealert::paTypes() const
{
    return m_paTypes;
}

void CPrealert::setPaTypes(QList<CPrealertType> *paTypes)
{
    m_paTypes = paTypes;
}

QDate CPrealert::Date() const
{
    return m_Date;
}

void CPrealert::setDate(const QDate &Date)
{
    m_Date = Date;
}

int CPrealert::id() const
{
    return m_id;
}

void CPrealert::setId(int id)
{
    m_id = id;
}

QList<CPrealertType> *CPrealert::getTypes(int id)
{
    QSqlQuery *lqry = new QSqlQuery();
    lqry->prepare("SELECT * FROM tblPATypes WHERE PAID = :ID;");
    lqry->bindValue(":ID", id);
    lqry->exec();
    lqry->first();
    QList<CPrealertType> *lLst = new QList<CPrealertType>();
    while(lqry->isValid())
    {
        CPrealertType type;
        // Daten einsetzen
        type.setId(lqry->value(lqry->record().indexOf("ID")).toInt());
        type.setPid(lqry->value(lqry->record().indexOf("PAID")).toInt());
        CDutyType* pdt = new CDutyType(lqry->value(lqry->record().indexOf("TypeID")).toInt());
        type.setType(pdt);
        lLst->append(type);
        lqry->next();
    }
    delete lqry;
    return lLst;
}




