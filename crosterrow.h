/********************************************************************
*
*   File: crosterrow.h    Class: CRosterRow
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
#ifndef CROSTERROW_H
#define CROSTERROW_H

// System-Header
#include <QList>
#include <QTime>
#include <QSqlQuery>

// Project-Header
#include <cduty.h>
#include <choliday.h>

class CRosterRow
{
private:
    QList<CDuty>        m_duties;
    QTime               m_sollH;
    QTime               m_istH;
    QTime               m_monDiff;
    QTime               m_totalDiff;
    QDate               m_Date;
    int                 m_workDays;
    CHoliday*           m_Holiday;

public:
    // Constructors
    CRosterRow();
    CRosterRow(int pPersID, QDate pDate);

    // Getter / Setter
    QList<CDuty> duties() const;
    void setDuties(const QList<CDuty> &duties);
    QTime sollH() const;
    QTime istH() const;
    QTime monDiff() const;
    QTime totalDiff() const;

private:
    void makeSollH();
    void makeIstH();
    void makeMonDiff();
    void makeTotalDiff();
    void makeWorkDays();
};

#endif // CROSTERROW_H
