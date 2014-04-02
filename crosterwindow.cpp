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

CRosterWindow::CRosterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CRosterWindow)
{
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



void CRosterWindow::on_dtedMonthChoice_dateChanged(const QDate &date)
{
    setTabTitle(m_Prefix, date);
}
