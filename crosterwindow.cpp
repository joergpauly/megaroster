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
    m_Prefix = "";
    ui->dtedMonthChoice->setDate(QDate::currentDate());
    setTabTitle(m_Prefix, QDate::currentDate());
    QSqlQuery* lqry = new QSqlQuery("SELECT * FROM tblDutyTypes ORDER BY Mark;");
    lqry->exec();
    lqry->first();
    ui->cmbDutyType->clear();
    while(lqry->isValid())
    {
        ui->cmbDutyType->addItem(lqry->value(lqry->record().indexOf("Mark")).toString(),QVariant(lqry->value(lqry->record().indexOf("ID")).toInt()));
        lqry->next();
    }
    delete lqry;
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
    ltitle.append("Dienstplan ");
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
        QColor white(255,255,255);
        hdr->setBackground(QBrush(white));
        hdr->setData(1,lpersonalList->at(i).id());
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
        QTableWidgetItem* litem = new QTableWidgetItem();
        QString dt = QDate::shortDayName(pDate.dayOfWeek());
        dt.append("\n");
        dt.append(QString::number(i+1));
        litem->setText(dt);

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
        QTableWidgetItem* litem = new QTableWidgetItem();
        litem->setText(ltime);
        litem->setTextAlignment(Qt::AlignRight);
        ui->tbwRoster->setItem(i, pcol, litem);
    }
}

void CRosterWindow::makeIstH()
{
    CDuty *dty = new CDuty(ui->tbwRoster->item(0,0)->data(Qt::UserRole).toInt());
    int mins;
    int hrs;
    QDate lDate = dty->Date();
    for(int row = 0; row < ui->tbwRoster->rowCount(); row++)
    {
        mins = 0;
        for(int col = 0; col < lDate.daysInMonth(); col++)
        {
            int lid = ui->tbwRoster->item(row,col)->data(Qt::UserRole).toInt();
            dty = new CDuty(lid);
            mins += dty->Duration().minute() + (dty->Duration().hour() * 60);
            mins += dty->Duration2().minute() + (dty->Duration2().hour() * 60);
        }
        hrs = mins / 60;
        mins = mins-(hrs*60);
        QString ltime = QString::number(hrs);
        ltime.append(":");
        if(mins < 10)
        {
            ltime.append("0");
        }
        ltime.append(QString::number(mins));
        QTableWidgetItem* litem = new QTableWidgetItem();
        litem->setText(ltime);
        litem->setTextAlignment(Qt::AlignRight);
        litem->setData(Qt::UserRole,"IST");
        ui->tbwRoster->setItem(row, dty->Date().daysInMonth(), litem);
        makeDiff(row);
    }
    delete dty;
}

void CRosterWindow::makeIstH(int prow)
{
    CDuty *dty = new CDuty(ui->tbwRoster->item(0,0)->data(Qt::UserRole).toInt());
    int mins;
    int hrs;
    QDate lDate = dty->Date();
    mins = 0;
    for(int col = 0; col < lDate.daysInMonth(); col++)
    {
        int lid = ui->tbwRoster->item(prow,col)->data(Qt::UserRole).toInt();
        dty = new CDuty(lid);
        mins += dty->Duration().minute() + (dty->Duration().hour() * 60);
        mins += dty->Duration2().minute() + (dty->Duration2().hour() * 60);
    }
    hrs = mins / 60;
    mins = mins-(hrs*60);
    QString ltime = QString::number(hrs);
    ltime.append(":");
    if(mins < 10)
    {
        ltime.append("0");
    }
    ltime.append(QString::number(mins));
    QTableWidgetItem* litem = new QTableWidgetItem();
    litem->setText(ltime);
    litem->setTextAlignment(Qt::AlignRight);
    litem->setData(Qt::UserRole,"IST");
    ui->tbwRoster->setItem(prow, dty->Date().daysInMonth(), litem);
    delete dty;
    makeDiff(prow);
}

void CRosterWindow::makeDiff(int prow)
{
    int istCol = ui->tbwRoster->columnCount()-3;
    int solCol = ui->tbwRoster->columnCount()-2;
    int difCol = ui->tbwRoster->columnCount()-1;
    QString istT = ui->tbwRoster->item(prow,istCol)->text();
    int istMins = istT.right(2).toInt();
    istMins += (istT.left(istT.length()-3).toInt() * 60);
    QString solT = ui->tbwRoster->item(prow,solCol)->text();
    int solMins = solT.right(2).toInt();
    solMins += (solT.left(solT.length()-3).toInt() * 60);
    int difMins = istMins - solMins;
    int difHrs = difMins / 60;
    QString difT = QString::number(difHrs);
    difT.append(":");
    difMins = difMins - (difHrs * 60);
    if(difMins < 0)
    {
        difMins = difMins - (difMins * 2);
    }
    if(difMins < 10)
    {
        difT.append("0");
    }
    difT.append(QString::number(difMins));
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(difT);
    item->setTextAlignment(Qt::AlignRight);
    ui->tbwRoster->setItem(prow,difCol,item);
}

void CRosterWindow::makeRoster(QDate pDate)
{
    QSqlQuery *lqry = new QSqlQuery();
    QDate lfirstDate;
    lfirstDate.setDate(pDate.year(),pDate.month(),1);
    QDate llastDate;
    llastDate.setDate(pDate.year(),pDate.month(),pDate.daysInMonth());
    bool newPlan = false;
    for(int row = 0; row < ui->tbwRoster->rowCount(); row++)
    {
        int PerID = ui->tbwRoster->verticalHeaderItem(row)->data(1).toInt();
        for(int col = 1; col <= pDate.daysInMonth(); col++)
        {
            QDate ldate(pDate.year(),pDate.month(),col);
            lqry->prepare("SELECT * FROM tblDuty WHERE PersID = :PID AND DDate = :DATE;");
            lqry->bindValue(":PID", PerID);
            lqry->bindValue(":DATE", ldate.toString("yyyy-MM-dd"));
            lqry->exec();
            lqry->first();

            if(!lqry->isValid())
            {
                newPlan = true;
                CDutyType *dtyp = new CDutyType("--");
                lqry->prepare("INSERT INTO tblDuty (PersID, DDate, TypeID, Status, TimeFrom, TimeTo, TimeFrom2, TimeTo2, Dura, Dura2) VALUES (:PID, :DATE, 6, 0, '00:00:00.000', '00:00:00.000', '00:00:00.000', '00:00:00.000', '00:00:00.000', '00:00:00.000');");
                lqry->bindValue(":PID", PerID);
                lqry->bindValue(":DATE", ldate.toString("yyyy-MM-dd"));
                lqry->exec();
                QTableWidgetItem *item = new QTableWidgetItem();
                QColor lclr(dtyp->RosterColorR(),dtyp->RosterColorG(),dtyp->RosterColorB());
                item->setBackground(QBrush(lclr));
                item->setData(Qt::UserRole,lqry->lastInsertId().toInt());
                ui->tbwRoster->setItem(row, col-1, item);
                delete dtyp;
            }

            CDuty* ditem = new CDuty(lqry->value(lqry->record().indexOf("ID")).toInt());
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(ditem->Typ()->Mark());
            item->setTextAlignment(Qt::AlignCenter);

            if(ui->cbShowAlerts->isChecked())
            {
                item->font().setBold(true);
            }
            else
            {
                item->font().setBold(false);
            }

            QColor lcol(ditem->Typ()->RosterColorR(),ditem->Typ()->RosterColorG(),ditem->Typ()->RosterColorB());
            item->setBackground(QBrush(lcol));
            item->setData(Qt::UserRole,ditem->id());
            ui->tbwRoster->setItem(row, col-1, item);            
        }        
    }
    if(newPlan)
    {
        makeRoster(pDate);
    }
    delete lqry;
}

void CRosterWindow::updateDetails(int prow, int pcol)
{
    CDuty *dty = new CDuty(ui->tbwRoster->item(prow, pcol)->data(Qt::UserRole).toInt());
    updateDetails(dty);
    delete dty;
}

void CRosterWindow::updateDetails(CDuty *pDuty)
{
    QString txt = pDuty->Typ()->Desc();
    ui->txtDutyType->setText(txt);
    QPalette pal = ui->txtDutyType->palette();
    QColor lclr(pDuty->Typ()->RosterColorR(),pDuty->Typ()->RosterColorG(),pDuty->Typ()->RosterColorB());
    pal.setColor(QPalette::Base,lclr);
    ui->txtDutyType->setPalette(pal);
    ui->timFrom->setTime(pDuty->TimeFrom());
    ui->timTo->setTime(pDuty->TimeTo());
    ui->timFrom2->setTime(pDuty->TimeFrom2());
    ui->timTo2->setTime(pDuty->TimeTo2());
    int hrs = pDuty->Duration().hour() + pDuty->Duration2().hour();
    int mins = pDuty->Duration().minute() + pDuty->Duration2().minute();
    if(mins > 59)
    {
        hrs +=1;
        mins-=60;
    }
    QTime ltim(hrs,mins);
    ui->timDura->setTime(ltim);
    updatePrealerts(pDuty);
}

void CRosterWindow::updatePrealerts(CDuty *pDuty)
{
    if(ui->tbwRoster->selectedItems().count() > 1)
    {
        return;
    }
    ui->tblPrealerts->clear();
    ui->tblPrealerts->setColumnCount(1);
    CPrealert lpa(pDuty->Kollege()->id(), pDuty->Date());
    ui->tblPrealerts->setRowCount(lpa.paTypes()->count());
    QTableWidgetItem *lhdr = new QTableWidgetItem(pDuty->Date().toString("dd.MM.yy"));
    ui->tblPrealerts->setHorizontalHeaderItem(0,lhdr);
    for(int i = 0; i < lpa.paTypes()->count(); i++)
    {
        QTableWidgetItem *litem = new QTableWidgetItem(lpa.paTypes()->at(i).type()->Mark());
        litem->setData(Qt::UserRole,QVariant(lpa.paTypes()->at(i).type()->id()));
        QColor lclr(lpa.paTypes()->at(i).type()->RosterColorR(),
                    lpa.paTypes()->at(i).type()->RosterColorG(),
                    lpa.paTypes()->at(i).type()->RosterColorB());
        litem->setBackground(QBrush(lclr));
        ui->tblPrealerts->setItem(i,0,litem);
    }

}

void CRosterWindow::on_dtedMonthChoice_dateChanged(const QDate &date)
{
    m_init = true;
    qApp->setOverrideCursor(QCursor(Qt::WaitCursor));
    m_Holidays = new CHoliday(date.year());
    m_dbman = ((CMainWindow*)m_parent)->dataBase();
    setTabTitle(m_Prefix, date);
    makeRows(date);
    makeColumns(date);    
    makeRoster(date);
    makeIstH();
    qApp->restoreOverrideCursor();
    m_init = false;
}


void CRosterWindow::on_tbwRoster_itemChanged(QTableWidgetItem *item)
{
    if(m_init)
    {        
        return;
    }
    if(item->data(Qt::UserRole).toInt() == 0)
    {
        return;
    }
    CDuty *dty = new CDuty(item->data(Qt::UserRole).toInt());
    CDutyType *dtyp = new CDutyType(item->text().toUpper());
    item->setText(dtyp->Mark());
    dty->setTyp(*dtyp);
    dty->setTimeFrom(dtyp->TimeFrom());
    dty->setTimeTo(dtyp->TimeTo());
    dty->setDuration(dtyp->TimeElapsed());
    dty->setTimeFrom2(dtyp->TimeFrom2());
    dty->setTimeTo2(dtyp->TimeTo2());
    dty->setDuration2(dtyp->TimeElapsed2());
    QColor lclr(dtyp->RosterColorR(),dtyp->RosterColorG(),dtyp->RosterColorB());
    item->setBackground(QBrush(lclr));
    QSqlQuery qry;
    qry.prepare("UPDATE tblDuty SET TypeID = :TID, TimeFrom = :TF, TimeTo = :TT, Dura = :Dura, TimeFrom2 = :TFF, TimeTo2 = :TTT, Dura2 = :Dura2 WHERE ID = :ID;");
    int tid = dtyp->id();
    qry.bindValue(":TID", tid);
    QString tf = dty->TimeFrom().toString("hh:mm:ss.zzz");
    qry.bindValue(":TF", tf);
    QString tt = dty->TimeTo().toString("hh:mm:ss.zzz");
    qry.bindValue(":TT", tt);
    QString dur = dty->Duration().toString("hh:mm:ss.zzz");
    qry.bindValue(":Dura", dur);
    QString tf2 = dty->TimeFrom2().toString("hh:mm:ss.zzz");
    qry.bindValue(":TFF", tf2);
    QString tt2 = dty->TimeTo2().toString("hh:mm:ss.zzz");
    qry.bindValue(":TTT", tt2);
    QString dur2 = dty->Duration2().toString("hh:mm:ss.zzz");
    qry.bindValue(":Dura2", dur2);
    int did = dty->id();
    qry.bindValue(":ID", did);
    qry.exec();
    updateDetails(dty);
    makeIstH(ui->tbwRoster->currentRow());
    delete dty;
    delete dtyp;
}

void CRosterWindow::on_tbwRoster_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    updateDetails(currentRow, currentColumn);
}

void CRosterWindow::on_cmbDutyType_currentIndexChanged(const QString &arg1)
{
    m_DType = new CDutyType(arg1);
    QPalette pal = ui->cmbDutyType->palette();
    QColor lclr(m_DType->RosterColorR(),m_DType->RosterColorG(),m_DType->RosterColorB());
    pal.setColor(QPalette::Button,lclr);
    ui->cmbDutyType->setPalette(pal);
    ui->cmdBlocks->setPalette(pal);
}

void CRosterWindow::on_tbwRoster_itemClicked(QTableWidgetItem *item)
{
    if(ui->cmdBlocks->isChecked())
    {
        item->setText(ui->cmbDutyType->currentText());
    }
}

void CRosterWindow::on_tbwRoster_itemSelectionChanged()
{
    if(ui->cmdBlocks->isChecked())
    {
        QList<QTableWidgetItem *> *llist = new QList<QTableWidgetItem *>(ui->tbwRoster->selectedItems());
        if(llist->count() == 1)
        {
            return;
        }
        for(int i = 0; i < llist->count(); i++)
        {
            llist->at(i)->setText(ui->cmbDutyType->currentText());
        }
    }

    ui->tblPrealerts->clear();
    QList<QTableWidgetItem*> llist = ui->tbwRoster->selectedItems();
    ui->tblPrealerts->setColumnCount(llist.count());
    for(int j = 0; j < llist.count(); j++)
    {
        CDuty *dty = new CDuty(llist.at(j)->data(Qt::UserRole).toInt());
        QTableWidgetItem *lhdr = new QTableWidgetItem(dty->Date().toString("dd.MM.yy"));
        ui->tblPrealerts->setHorizontalHeaderItem(j,lhdr);
        CPrealert lpa(dty->Kollege()->id(),dty->Date());
        if(ui->tblPrealerts->rowCount() < lpa.paTypes()->count())
        {
            ui->tblPrealerts->setRowCount(lpa.paTypes()->count());
        }
        for(int k = 0; k < lpa.paTypes()->count(); k++)
        {
            QTableWidgetItem *litem = new QTableWidgetItem(lpa.paTypes()->at(k).type()->Mark());
            litem->setData(Qt::UserRole,QVariant(lpa.paTypes()->at(k).type()->id()));
            QColor lclr(lpa.paTypes()->at(k).type()->RosterColorR(),
                        lpa.paTypes()->at(k).type()->RosterColorG(),
                        lpa.paTypes()->at(k).type()->RosterColorB());
            litem->setBackground(QBrush(lclr));
            ui->tblPrealerts->setItem(k,j,litem);
        }
    }
}

void CRosterWindow::on_cmdPrint_clicked()
{
    QPrinter* prt = new QPrinter();
    prt->setOrientation(QPrinter::Landscape);
    QPrintDialog* dlg = new QPrintDialog(prt, this);
    dlg->exec();
    QTableWidget *table = new QTableWidget(ui->tbwRoster);
    table->setParent(this);
    table->setGeometry(0,0,(table->horizontalHeader()->width() + (table->columnCount() * table->verticalHeader()->width())),table->horizontalHeader()->height() * (table->rowCount()+1));
    QPainter painter;
    painter.begin(prt);    
    double xscale = prt->pageRect().width()/double(ui->tbwRoster->width());
    double yscale = prt->pageRect().height()/double(ui->tbwRoster->height());
    double scale = qMin(xscale, yscale);
    painter.translate(prt->paperRect().x() + prt->pageRect().width()/2,
                       prt->paperRect().y() + prt->pageRect().height()/2);
    painter.scale(scale, scale);
    painter.translate(-width()/2, -height()/2);

    ui->tbwRoster->render(&painter);
    painter.end();
}

void CRosterWindow::on_tblPrealerts_itemDoubleClicked(QTableWidgetItem *item)
{
    CDutyType ltyp(item->data(Qt::UserRole).toInt());
    ui->tbwRoster->currentItem()->setText(ltyp.Mark());
}

void CRosterWindow::on_cbShowAlerts_clicked(bool checked)
{
    makeRoster(QDate(m_Year,m_Month,1));
}
