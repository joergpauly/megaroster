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

#include "crosterwindow.h"
#include "ui_crosterwindow.h"
#include "cmainwindow.h"

CRosterWindow::CRosterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CRosterWindow)
{
    m_parent = parent;
    ui->setupUi(this);
    m_Prefix = "Soll";
    ui->dtedMonthChoice->setDate(QDate::currentDate());
    setTabTitle(m_Prefix, QDate::currentDate());
}

CRosterWindow::CRosterWindow(QWidget *parent, int pMonth, int pYear) :
    QWidget(parent),
    ui(new Ui::CRosterWindow)
{
    m_Month = pMonth;
    m_Year = pYear;
    ui->setupUi(this);
}

CRosterWindow::~CRosterWindow()
{
    delete ui;
}

void CRosterWindow::setSubWnd(QWidget *pSubWnd)
{
    m_subWnd = pSubWnd;
}

void CRosterWindow::setTabTitle(QString pPrefix, QDate pDate)
{
    QString ltitle = pPrefix;
    ltitle.append("-Dienstplan ");
    ltitle.append(QDate::longMonthName(pDate.month()));
    ltitle.append(" ");
    ltitle.append(QString::number(pDate.year()));
    this->setWindowTitle(ltitle);
}

void CRosterWindow::makeRows(QDate pDate)
{
    QDate lfirstDate;
    lfirstDate.setDate(pDate.year(),pDate.month(),1);
    QDate llastDate;
    llastDate.setDate(pDate.year(),pDate.month(),pDate.daysInMonth());
    QList<CPersonal>* lpersonalList = m_dbman->personalList(lfirstDate, llastDate);
    ui->tbwRoster->setRowCount(lpersonalList->count());
    for(int i = 0; i < ui->tbwRoster->rowCount(); i++)
    {
        QString lfullname = lpersonalList->at(i).Name();
        lfullname.append(", ");
        lfullname.append(lpersonalList->at(i).VName());
        QTableWidgetItem* hdr = new QTableWidgetItem(lfullname);
        ui->tbwRoster->setVerticalHeaderItem(i,hdr);
    }
}

void CRosterWindow::makeColumns(QDate pDate)
{
    QColor lSat(100,100,255);
    QColor lSun(255,0,0);
    QColor lHol(255,255,0);
    QColor lHolFg(255,0,0);
    int ldays = pDate.daysInMonth();
    int lwdays = ldays;
    ui->tbwRoster->setColumnCount(ldays+3);
    for(int i = 0; i < pDate.daysInMonth(); i++)
    {
        pDate.setDate(pDate.year(),pDate.month(),i+1);
        QTableWidgetItem* litem = new QTableWidgetItem(QString::number(i+1));

        if(pDate.dayOfWeek() == 6)
        {
            litem->setBackground(QBrush(lSat));
            lwdays--;
        }

        if(pDate.dayOfWeek() == 7)
        {
            litem->setBackground(QBrush(lSun));
            lwdays--;
        }

        if(m_Holidays->checkForHoliday(pDate))
        {
            litem->setForeground(QBrush(lHolFg));
            litem->setBackground(QBrush(lHol));
            if(pDate.dayOfWeek()<6)
            {
                lwdays--;
            }
        }

        ui->tbwRoster->setHorizontalHeaderItem(i,litem);
        ui->tbwRoster->setColumnWidth(i,25);
    }
    QTableWidgetItem* litem = new QTableWidgetItem("Ist-h");
    ui->tbwRoster->setHorizontalHeaderItem(pDate.daysInMonth(),litem);
    ui->tbwRoster->setColumnWidth(pDate.daysInMonth(),50);
    litem = new QTableWidgetItem("Soll-h");
    ui->tbwRoster->setHorizontalHeaderItem(pDate.daysInMonth()+1,litem);
    ui->tbwRoster->setColumnWidth(pDate.daysInMonth()+1,50);
    litem = new QTableWidgetItem("Diff.");
    ui->tbwRoster->setHorizontalHeaderItem(pDate.daysInMonth()+2,litem);
    ui->tbwRoster->setColumnWidth(pDate.daysInMonth()+2,50);
    makeSollH(pDate,lwdays,ldays+1);
}

void CRosterWindow::makeSollH(QDate pDate, int pwdays, int pcol)
{
    QDate lfirstDate;
    lfirstDate.setDate(pDate.year(),pDate.month(),1);
    QDate llastDate;
    llastDate.setDate(pDate.year(),pDate.month(),pDate.daysInMonth());
    QList<CPersonal>* lpersonalList = m_dbman->personalList(lfirstDate, llastDate);
    for(int i = 0; i < lpersonalList->count(); i++)
    {
        int shr = lpersonalList->at(i).SollTag().toString("hh:mm").left(2).toInt();
        int smn = lpersonalList->at(i).SollTag().toString("hh:mm").right(2).toInt();
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
        QTableWidgetItem* litem = new QTableWidgetItem(ltime);
        ui->tbwRoster->setItem(i, pcol, litem);
    }
}



void CRosterWindow::on_dtedMonthChoice_dateChanged(const QDate &date)
{
    m_Holidays = new CHoliday(date.year());
    m_dbman = ((CMainWindow*)m_parent)->dataBase();
    setTabTitle(m_Prefix, date);
    makeRows(date);
    makeColumns(date);
}
