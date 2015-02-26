/****************************************************************************************
*
*   This file is part of the MEGASeries Project.
*   Copyright (C) 2014 joerg
*   All Rights reserved
*
*   Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
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

#include "clogbookview.h"
#include "ui_clogbookview.h"

CLogbookView::CLogbookView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CLogbookView)
{
    ui->setupUi(this);
    ui->datFrom->setDate(QDate(QDate::currentDate().year(), QDate::currentDate().month(), 1));
    ui->datTo->setDateTime(QDateTime::currentDateTime());
    loadLog();
}

CLogbookView::~CLogbookView()
{
    delete ui;
}

void CLogbookView::setSubWnd(QMdiSubWindow *pSubWnd)
{
    m_SubWnd = pSubWnd;
}

void CLogbookView::on_datFrom_editingFinished()
{
    loadLog();
}

void CLogbookView::on_datTo_editingFinished()
{
    loadLog();
}

void CLogbookView::loadLog()
{
    QSqlQuery lqry;
    lqry.prepare("SELECT * FROM tblLogbook WHERE DDateTime >= :FROM AND DDateTime <= :TO;");
    QString lFrom = ui->datFrom->dateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString lTo = ui->datTo->dateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    lqry.bindValue(":FROM", lFrom);
    lqry.bindValue(":TO", lTo);
    lqry.exec();
    QString db = lqry.lastError().text();
    lqry.first();
    ui->tbwLogbook->clear();
    ui->tbwLogbook->setColumnCount(6);
    ui->tbwLogbook->setRowCount(0);
    QTableWidgetItem *litem;
    litem = new QTableWidgetItem("Datum / Zeit");
    ui->tbwLogbook->setHorizontalHeaderItem(0, litem);
    ui->tbwLogbook->setColumnWidth(0,150);
    litem = new QTableWidgetItem("Bearbeiter");
    ui->tbwLogbook->setHorizontalHeaderItem(1, litem);
     ui->tbwLogbook->setColumnWidth(1,150);
    litem = new QTableWidgetItem("Geändert für");
    ui->tbwLogbook->setHorizontalHeaderItem(2, litem);
     ui->tbwLogbook->setColumnWidth(2,150);
    litem = new QTableWidgetItem("Dienst am");
    ui->tbwLogbook->setHorizontalHeaderItem(3, litem);
     ui->tbwLogbook->setColumnWidth(3,150);
    litem = new QTableWidgetItem("Alt");
    ui->tbwLogbook->setHorizontalHeaderItem(4, litem);
    litem = new QTableWidgetItem("Neu");
    ui->tbwLogbook->setHorizontalHeaderItem(5, litem);

    while(lqry.isValid())
    {
        ui->tbwLogbook->setRowCount(ui->tbwLogbook->rowCount() + 1);
        litem = new QTableWidgetItem(lqry.value(lqry.record().indexOf("DDateTime")).toDateTime().toString("dd.MM.yyyy hh:mm"));
        ui->tbwLogbook->setItem(ui->tbwLogbook->rowCount() - 1, 0, litem);
        CPersonal lPers(lqry.value(lqry.record().indexOf("PID")).toInt());
        litem = new QTableWidgetItem(lPers.Name() + ", " + lPers.VName());
        ui->tbwLogbook->setItem(ui->tbwLogbook->rowCount() - 1, 1, litem);
        CDuty lDuty(lqry.value(lqry.record().indexOf("DtID")).toInt());
        litem = new QTableWidgetItem(lDuty.Kollege()->Name() + ", " + lDuty.Kollege()->VName());
        ui->tbwLogbook->setItem(ui->tbwLogbook->rowCount() - 1, 2, litem);
        litem = new QTableWidgetItem(lDuty.Date().toString("ddd, dd.MM.yyyy"));
        ui->tbwLogbook->setItem(ui->tbwLogbook->rowCount() - 1, 3, litem);
        CDutyType lOld(lqry.value(lqry.record().indexOf("OldDTID")).toInt());
        litem = new QTableWidgetItem(lOld.Desc());
        ui->tbwLogbook->setItem(ui->tbwLogbook->rowCount() - 1, 4, litem);
        CDutyType lNew(lqry.value(lqry.record().indexOf("NewDTID")).toInt());
        litem = new QTableWidgetItem(lNew.Desc());
        ui->tbwLogbook->setItem(ui->tbwLogbook->rowCount() - 1, 5, litem);
        lqry.next();
    }

}
