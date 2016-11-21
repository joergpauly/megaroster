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
#include "cmainwindow.h"
#include "ui_crosteredit.h"

CRosterEdit::CRosterEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CRosterEdit)
{
    m_parent = parent;
    ui->setupUi(this);

    if(!m_preSelected)
    {
        buildRoster(new QDate(QDate::currentDate()));
    }

}

CRosterEdit::CRosterEdit(QDate *pDate, QWidget *parent) :
    QWidget (parent),
    ui(new Ui::CRosterEdit)
{
    m_preSelected = true;
    CRosterEdit((QWidget*)this->parent());
    buildRoster(pDate);
}

CRosterEdit::~CRosterEdit()
{
    delete ui;
}

void CRosterEdit::setSubWnd(QWidget *pSubWnd)
{
    m_subWnd = pSubWnd;
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
    // Start- und Ende-Datum setzen
    m_dateFrom.setDate(pDate->year(), pDate->month(), 1);
    m_dateTo.setDate(pDate->year(), pDate->month(), pDate->daysInMonth());
    // Anzahl Spalten ermitteln
    m_cols = pDate->daysInMonth() + 4;
    // Liste der diensthabenden Kollegen holen
    m_currentOfficers = *((CMainWindow*)m_parent)->dataBase()->personalList(m_dateFrom, m_dateTo);
    // Anzahl Zeilen ermitteln
    m_rows = m_currentOfficers.count();
    // Tabellengröße festlegen
    ui->tbwRoster->setColumnCount(m_cols);
    ui->tbwRoster->setRowCount(m_rows);
    // Zeilen- und Spalten-Header setzen
    buildHorizontalHeader();
    buildVerticalHeader();
}

void CRosterEdit::buildHorizontalHeader()
{
    QDate lDate;
    QColor lSat(100,100,255);
    QColor lSun(255,0,0);
    QColor lHol(255,255,0);
    QColor lHolFg(255,0,0);
    int ldays = m_dateFrom.daysInMonth();
    int lwdays = ldays;

    for(int i = 0; i < m_dateFrom.daysInMonth(); i++)
    {
        lDate.setDate(m_dateFrom.year(),m_dateFrom.month(),i+1);
        QTableWidgetItem* litem = new QTableWidgetItem();
        QString dt = QDate::shortDayName(lDate.dayOfWeek());
        dt.append("\n");
        dt.append(QString::number(i+1));
        litem->setText(dt);

        if(lDate.dayOfWeek() == 6)
        {
            litem->setBackground(QBrush(lSat));
            lwdays--;
        }

        if(lDate.dayOfWeek() == 7)
        {
            litem->setBackground(QBrush(lSun));
            lwdays--;
        }

        if(m_Holidays->checkForHoliday(lDate) && lDate.dayOfWeek() < 6)
        {
            litem->setForeground(QBrush(lHolFg));
            litem->setBackground(QBrush(lHol));

            if(lDate.dayOfWeek()<6)
            {
                lwdays--;
            }

        }

        ui->tbwRoster->setHorizontalHeaderItem(i,litem);
        ui->tbwRoster->setColumnWidth(i,27);
    }

    QTableWidgetItem* litem = new QTableWidgetItem("Ist-h");
    ui->tbwRoster->setHorizontalHeaderItem(lDate.daysInMonth(), litem);
    ui->tbwRoster->setColumnWidth(lDate.daysInMonth(), 55);
    litem = new QTableWidgetItem("Soll-h");
    ui->tbwRoster->setHorizontalHeaderItem(lDate.daysInMonth()+1, litem);
    ui->tbwRoster->setColumnWidth(lDate.daysInMonth()+1, 55);
    litem = new QTableWidgetItem("Diff.");
    ui->tbwRoster->setHorizontalHeaderItem(lDate.daysInMonth()+2, litem);
    ui->tbwRoster->setColumnWidth(lDate.daysInMonth()+2, 55);
    litem = new QTableWidgetItem("Kum.Diff.");
    ui->tbwRoster->setHorizontalHeaderItem(lDate.daysInMonth()+3, litem);
    ui->tbwRoster->setColumnWidth(lDate.daysInMonth()+3, 55);
    makeSollH(lDate,lwdays,ldays+1);
}

void CRosterEdit::buildVerticalHeader()
{
    for(int i = 0; i < ui->tbwRoster->rowCount(); i++)
    {
        QString lfullname = m_currentOfficers.at(i).Name();
        lfullname.append(", ");
        lfullname.append(m_currentOfficers.at(i).VName());
        QTableWidgetItem* hdr = new QTableWidgetItem(lfullname);
        QColor white(255,255,255);
        hdr->setBackground(QBrush(white));
        hdr->setData(1,m_currentOfficers.at(i).id());
        ui->tbwRoster->setVerticalHeaderItem(i,hdr);
    }
}

void CRosterEdit::on_dtedMonthChoice_dateChanged(const QDate &date)
{
    buildRoster(new QDate(date));
}

void CRosterEdit::makeSollH(QDate pDate, int pwdays, int pcol)
{
    QDate lfirstDate;
    lfirstDate.setDate(pDate.year(),pDate.month(),1);
    QDate llastDate;
    llastDate.setDate(pDate.year(),pDate.month(),pDate.daysInMonth());

    for(int i = 0; i < m_currentOfficers.count(); i++)
    {
        int shr = m_currentOfficers.at(i).SollTag().toString("hh:mm").left(2).toInt();
        int smn = m_currentOfficers.at(i).SollTag().toString("hh:mm").right(2).toInt();
        smn += (shr * 60);
        smn = smn * pwdays;
        int sshr = smn / 60;
        int ssmn = smn - (sshr * 60);
        QString ltime = QString::number(sshr);
        ltime.append(":");

        if(ssmn < 10)
        {
            ltime.append("0");
        }

        ltime.append(QString::number(ssmn));
        QTableWidgetItem* litem = new QTableWidgetItem();
        litem->setText(ltime);
        litem->setTextAlignment(Qt::AlignRight);
        ui->tbwRoster->setItem(i, pcol, litem);
    }

}
