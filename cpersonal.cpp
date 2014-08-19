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

#include "cpersonal.h"

CPersonal::CPersonal()
{
}

CPersonal::CPersonal(int pID)
{
    QSqlQuery* lqry = new QSqlQuery();
    lqry->prepare("SELECT * FROM tblPersonal WHERE ID = :ID;");
    lqry->bindValue(":ID", pID);
    lqry->exec();
    lqry->first();
    m_id = lqry->value(lqry->record().indexOf("ID")).toInt();
    m_Name = lqry->value(lqry->record().indexOf("Name")).toString();
    m_VName = lqry->value(lqry->record().indexOf("VName")).toString();
    m_PersNo = lqry->value(lqry->record().indexOf("PNr")).toString();
    m_GebDat = QDate::fromString(lqry->value(lqry->record().indexOf("GebDat")).toString(),"yyyy-MM-dd");
    m_Eintritt = QDate::fromString(lqry->value(lqry->record().indexOf("Eintritt")).toString(),"yyyy-MM-dd");
    m_Austritt = QDate::fromString(lqry->value(lqry->record().indexOf("Austritt")).toString(),"yyyy-MM-dd");
    m_SollTag = QTime::fromString(lqry->value(lqry->record().indexOf("SollTag")).toString(),"hh:mm:ss.zzz");
    m_Admin = lqry->value(lqry->record().indexOf("Admin")).toBool();
    m_Edit = lqry->value(lqry->record().indexOf("PlanEdit")).toBool();
    delete lqry;
}

QString CPersonal::Name() const
{
    return m_Name;
}

void CPersonal::setName(const QString &Name)
{
    m_Name = Name;
}

QString CPersonal::VName() const
{
    return m_VName;
}

void CPersonal::setVName(const QString &VName)
{
    m_VName = VName;
}

QString CPersonal::PersNo() const
{
    return m_PersNo;
}

void CPersonal::setPersNo(const QString &PersNo)
{
    m_PersNo = PersNo;
}

QTime CPersonal::SollTag() const
{
    return m_SollTag;
}

void CPersonal::setSollTag(const QTime &SollTag)
{
    m_SollTag = SollTag;
}

QDate CPersonal::GebDat() const
{
    return m_GebDat;
}

void CPersonal::setGebDat(const QDate &GebDat)
{
    m_GebDat = GebDat;
}

int CPersonal::id() const
{
    return m_id;
}

void CPersonal::setId(int id)
{
    m_id = id;
}

QDate CPersonal::Eintritt() const
{
    return m_Eintritt;
}

void CPersonal::setEintritt(const QDate &Eintritt)
{
    m_Eintritt = Eintritt;
}

QDate CPersonal::Austritt() const
{
    return m_Austritt;
}

void CPersonal::setAustritt(const QDate &Austritt)
{
    m_Austritt = Austritt;
}

bool CPersonal::Edit() const
{
    return m_Edit;
}

void CPersonal::setEdit(const bool pEd)
{
    m_Edit = pEd;
}

bool CPersonal::Admin() const
{
    return m_Admin;
}

void CPersonal::setAdmin(const bool pAd)
{
    m_Admin = pAd;
}








