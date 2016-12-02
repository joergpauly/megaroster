/********************************************************************
*
*   File: crosterrow.cpp    Class: CRosterRow
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2016 Joerg Pauly
*   Created 02.12.2016 by joerg
*   All Rights reserved
*
*   Alle Programme der MEGA-Serie sind Freie Software:
*   Sie können sie unter den Bedingungen
*   der GNU Lesser General Public License, wie von der
*   Free Software Foundation, Version 3 der Lizenz oder
*   (nach Ihrer Option) jeder späteren veröffentlichten
*   Version, weiterverbreiten und/oder modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es nützlich
*   sein wird, aber OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt;
*   sogar ohne die implizite Gewährleistung der MARKTFÄHIGKEIT
*   oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU Lesser General Public License für weitere Details.
*
*   Sie sollten eine Kopie der GNU Lesser General Public License
*   zusammen mit diesem Programm erhalten haben.
*   Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*
********************************************************************/
#include "crosterrow.h"

CRosterRow::CRosterRow()
{

}

CRosterRow::CRosterRow(int pPersID, QDate pDate)
{
    m_duties.clear();
    m_Holiday = new CHoliday(pDate.year());
    makeWorkDays();
    m_Personal = new CPersonal(pPersID);
    QDate lFrom;
    lFrom.setDate(pDate.year(), pDate.month(), 1);
    QDate lTo;
    lTo.setDate(pDate.year(), pDate.month(), pDate.daysInMonth());

    for(QDate lIterDate = lFrom; lIterDate <= lTo; lIterDate = lIterDate.addDays(1))
    {
        CDuty lDuty(pPersID, pDate);
        m_duties.append(lDuty);
    }

    makeSollH();
    makeIstH();
    makeMonDiff();
    makeTotalDiff();
}

QList<CDuty> CRosterRow::duties() const
{
    return m_duties;
}

void CRosterRow::setDuties(const QList<CDuty> &duties)
{
    m_duties = duties;
}

QTime CRosterRow::sollH() const
{
    return m_sollH;
}

QTime CRosterRow::istH() const
{
    return m_istH;
}

QTime CRosterRow::monDiff() const
{
    return m_monDiff;
}

QTime CRosterRow::totalDiff() const
{
    return m_totalDiff;
}

void CRosterRow::makeSollH()
{
    int shr = m_Personal->SollTag().hour();
    int smn = m_Personal->SollTag().minute();
    smn += (shr * 60);
    smn = smn * m_workDays;
    int sshr = smn / 60;
    int ssmn = smn - (sshr * 60);
    QString ltime = QString::number(sshr);
    ltime.append(":");

    if(ssmn < 10)
    {
        ltime.append("0");
    }

    ltime.append(QString::number(ssmn));
    m_sollH = QTime::fromString(ltime, "hh:mm");
}

void CRosterRow::makeIstH()
{
    int lhr = 0;
    int lmn = 0;

    for(int i = 0; i < m_duties.count(); i++)
    {
        lmn = m_duties.at(i).Duration().hour() * 60;
        lmn += m_duties.at(i).Duration().minute();
        lmn += m_duties.at(i).Duration2().hour() * 60;
        lmn += m_duties.at(i).Duration2().minute();
    }

    lhr = lmn / 60;
    lmn = lmn - (lhr * 60);
    QString lTime = QString::number(lhr);
    lTime.append(":");

    if(lmn < 10)
    {
        lTime.append("0");
    }

    lTime.append(QString::number(lmn));
    m_istH.fromString(lTime, "hh:mm");
}

void CRosterRow::makeMonDiff()
{
    m_monDiff = (QTime::fromString("00:00", "hh:mm")).addSecs(m_sollH.secsTo(m_istH));
}

void CRosterRow::makeTotalDiff()
{

}

void CRosterRow::makeWorkDays()
{
    m_workDays = m_Date.daysInMonth();
    QDate lDate;

    for(int i = 0; i < m_Date.daysInMonth(); i++)
    {
        lDate.setDate(m_Date.year(),m_Date.month(),i+1);

        if(lDate.dayOfWeek() == 6)
        {
            m_workDays--;
        }

        if(lDate.dayOfWeek() == 7)
        {
            m_workDays--;
        }

        if(m_Holiday->checkForHoliday(lDate) && lDate.dayOfWeek() < 6)
        {

            if(lDate.dayOfWeek()<6)
            {
                m_workDays--;
            }

        }
    }
}


