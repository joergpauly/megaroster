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

CPersonal::CPersonal(int pID, QString pName, QString pVName, QString pPersNo, QDate pGebDat, QTime pSollTag)
{
    m_id = pID;
    m_Name = pName;
    m_VName = pVName;
    m_PersNo = pPersNo;
    m_GebDat = pGebDat;
    m_SollTag = pSollTag;
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






