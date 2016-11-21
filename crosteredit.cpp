/********************************************************************
*
*   File: crosteredit.cpp    Class: CRosterEdit
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2016 Joerg Pauly
*   Created 21.11.2016 by joerg
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
#include "crosteredit.h"
#include "ui_crosteredit.h"

CRosterEdit::CRosterEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CRosterEdit)
{
    ui->setupUi(this);
    buildRoster(new QDate(QDate::currentDate()));
}

CRosterEdit::CRosterEdit(QDate *pDate, QWidget *parent) :
    QWidget (parent),
    ui(new Ui::CRosterEdit)
{
    ui->setupUi(this);
    buildRoster(pDate);
}

CRosterEdit::~CRosterEdit()
{
    delete ui;
}

void CRosterEdit::on_tbwRoster_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{

}

void CRosterEdit::on_cmdPreviousMonth_clicked()
{

}

void CRosterEdit::on_cmdNextMonth_clicked()
{

}

void CRosterEdit::on_cmdCheckRoster_clicked()
{

}


/******************************************************************************
 * Aufbau des Roster beginnt hier
 *****************************************************************************/
void CRosterEdit::buildRoster(QDate *pDate)
{
    m_dateFrom.setDate(pDate->year(), pDate->month(), 1);
    m_dateTo.setDate(pDate->year(), pDate->month(), pDate->daysInMonth());
    m_Cols = pDate->daysInMonth() + 4;
    m_currentOfficers = getCurrentOfficers();
}

CCurrentOfficers *CRosterEdit::getCurrentOfficers()
{
    return new CCurrentOfficers(m_dateFrom, m_dateTo);
}


void CRosterEdit::on_dtedMonthChoice_dateChanged(const QDate &date)
{
    buildRoster(new QDate(date));
}
