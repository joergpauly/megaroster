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
    m_actUser = *new CPersonal(static_cast<CMainWindow*>(parent)->getUserID());

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
    ui->dtedMonthChoice->setDate(*pDate);
    ui->tbwRoster->clear();
    m_Holidays = new CHoliday(pDate->year());
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
    fillRoster(pDate);
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

void CRosterEdit::fillRoster(QDate *pDate)
{
    m_Roster = new CRoster(m_currentOfficers, pDate);
    m_list = m_Roster->roster();

    for(int i = 0; i < m_list.count(); i++)
    {
        QList<CDuty> lList = m_list.at(i);

        for(int j = 0; j < lList.count(); j++)
        {
            CDuty lDuty = lList.at(j);
            QTableWidgetItem *lItem = new QTableWidgetItem();
            lItem->setTextAlignment(Qt::AlignCenter);
            lItem->setText(lDuty.Typ()->Mark());
            lItem->setBackgroundColor(QColor(lDuty.Typ()->RosterColorR(), lDuty.Typ()->RosterColorG(), lDuty.Typ()->RosterColorB()));
            lItem->setData(Qt::UserRole, lDuty.id());

            if(lDuty.Request())
            {
                QFont lfnt = lItem->font();
                lfnt.setItalic(true);
                lItem->setFont(lfnt);
                QBrush brsh;
                QColor colr;
                colr.setRed(255);
                brsh.setColor(colr);
                lItem->setForeground(brsh);
            }

            ui->tbwRoster->setItem(i, j, lItem);
        }
    }
}

void CRosterEdit::ActiveCellChanged(int row, int column)
{
    m_actDuty = new CDuty(ui->tbwRoster->item(row, column)->data(Qt::UserRole).toInt());
    ui->txtDutyType->setText(m_actDuty->Typ()->Desc());
    QPalette pal = ui->txtDutyType->palette();
    QColor lclr(m_actDuty->Typ()->RosterColorR(),m_actDuty->Typ()->RosterColorG(),m_actDuty->Typ()->RosterColorB());
    pal.setColor(QPalette::Base,lclr);
    ui->txtDutyType->setPalette(pal);
    ui->chkReq->setChecked(m_actDuty->Request());
    ui->timFrom->setTime(m_actDuty->TimeFrom());
    ui->timTo->setTime(m_actDuty->TimeTo());
    ui->timDura->setTime(m_actDuty->Duration());
    ui->timFrom2->setTime(m_actDuty->TimeFrom2());
    ui->timTo2->setTime(m_actDuty->TimeTo2());
}

void CRosterEdit::saveSingleDuty(int row, int column)
{
    CDuty *lDuty = new CDuty(ui->tbwRoster->item(row, column)->data(Qt::UserRole).toInt());
    updateDetails(lDuty);
    lDuty->saVeDB();
}

void CRosterEdit::on_tbwRoster_cellActivated(int row, int column)
{
}

void CRosterEdit::on_tbwRoster_cellChanged(int row, int column)
{
}

void CRosterEdit::on_tbwRoster_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{

    ActiveCellChanged(currentRow, currentColumn);
}

void CRosterEdit::updateDetails(int prow, int pcol)
{
    // Anhand der Zelle CDuty-Objekt bilden und updaten
    if(prow < 0)
    {
        ui->timFrom->setEnabled(false);
        ui->timFrom2->setEnabled(false);
        ui->timTo->setEnabled(false);
        ui->timTo2->setEnabled(false);
        return;
    }

    if(pcol < 0)
    {
        ui->timFrom->setEnabled(false);
        ui->timFrom2->setEnabled(false);
        ui->timTo->setEnabled(false);
        ui->timTo2->setEnabled(false);
        return;
    }

    m_actDuty = new CDuty(ui->tbwRoster->item(prow, pcol)->data(Qt::UserRole).toInt());
    m_previousDuty = m_actDuty;
    updateDetails(m_actDuty);
}

void CRosterEdit::updateDetails(CDuty *pDuty)
{
    // Detailfelder berechnen und beschreiben
    m_updatingDetails = true;

    QString txt = pDuty->Typ()->Desc();
    ui->txtDutyType->setText(txt);
    QPalette pal = ui->txtDutyType->palette();
    QColor lclr(pDuty->Typ()->RosterColorR(),pDuty->Typ()->RosterColorG(),pDuty->Typ()->RosterColorB());
    pal.setColor(QPalette::Base,lclr);
    ui->txtDutyType->setPalette(pal);
    ui->chkReq->setChecked(pDuty->Request());
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
    ui->timFrom->setEnabled(true);
    ui->timFrom2->setEnabled(true);
    ui->timTo->setEnabled(true);
    ui->timTo2->setEnabled(true);
    //updatePrealerts(pDuty);

    /*
    if(ui->chkRTCheck->checkState() == Qt::Checked)
    {
        checkBaseTarget(pDuty);
    }
    */

    m_updatingDetails = false;

    if(!m_actUser.Edit())
    {

        if(pDuty->Date() >= QDate::currentDate())
        {

            if(!m_checkingRules)
            {
                ui->tbwRoster->setEnabled(false);
                QMessageBox lbox;
                lbox.setWindowTitle("Keine Berechtigung!");
                lbox.setText("Sie sind nicht berechtigt,\ngegenwärtige oder zukünftige\nDienstplan-Einträge zu ändern!");
                lbox.setStandardButtons(QMessageBox::Ok);
                lbox.setIcon(QMessageBox::Critical);
                lbox.exec();
                ui->dtedMonthChoice->setFocus();
                ui->tbwRoster->setEnabled(true);
            }

        }
        else
        {
            ui->tbwRoster->setEnabled(true);
        }

    }
}

void CRosterEdit::saveFromTable(int row, int col)
{
    QTableWidgetItem *item = ui->tbwRoster->item(row, col);
    saveFromTable(item);
}

void CRosterEdit::saveFromTable(QTableWidgetItem *pItem)
{
    if(m_init)
    {
        return;
    }

    if(pItem->data(Qt::UserRole).toInt() == 0)
    {
        return;
    }

    m_edit = true;
    CDuty *dty = new CDuty(pItem->data(Qt::UserRole).toInt());
    CLogManager logman;
    CLogManager::sctLogEntry entry;
    entry.affDuty = *dty;
    CDutyType *dtyp = new CDutyType(pItem->text().toUpper());
    entry.oldDuty = *m_previousDuty->Typ();
    entry.newDuty = *dtyp;
    entry.user = CPersonal(static_cast<CMainWindow*>(m_parent)->getUserID());
    entry.timeStamp = QDateTime::currentDateTime();
    logman.writeEntry(entry);
    pItem->setText(dtyp->Mark());
    dty->setTyp(*dtyp);
    dty->setTimeFrom(dtyp->TimeFrom());
    dty->setTimeTo(dtyp->TimeTo());
    dty->setDuration(dtyp->TimeElapsed());
    dty->setTimeFrom2(dtyp->TimeFrom2());
    dty->setTimeTo2(dtyp->TimeTo2());
    dty->setDuration2(dtyp->TimeElapsed2());
    QColor lclr(dtyp->RosterColorR(),dtyp->RosterColorG(),dtyp->RosterColorB());
    pItem->setBackground(QBrush(lclr));
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
    makeIstH(ui->tbwRoster->currentRow()); //TODO: makeIstH und checkRules in anderen Thread auslagern!!!
    //checkRules(dty->Date());
    m_previousDuty = dty;
    delete dty;
    delete dtyp;
    m_edit = false;
}

void CRosterEdit::makeIstH()
{
    CDuty dty(ui->tbwRoster->item(0,0)->data(Qt::UserRole).toInt());
    int mins;
    int hrs;
    QDate lDate = dty.Date();

    for(int row = 0; row < ui->tbwRoster->rowCount(); row++)
    {
        mins = 0;

        for(int col = 0; col < lDate.daysInMonth(); col++)
        {
            int lid = ui->tbwRoster->item(row,col)->data(Qt::UserRole).toInt();
            dty = CDuty(lid);
            mins += dty.Duration().minute() + (dty.Duration().hour() * 60);
            mins += dty.Duration2().minute() + (dty.Duration2().hour() * 60);
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
        ui->tbwRoster->setItem(row, dty.Date().daysInMonth(), litem);
        makeDiff(row);
        makeKumDiff(row);
    }

}

void CRosterEdit::makeIstH(int prow)
{
    if(prow < 0)
    {
        return;
    }

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
    makeDiff(prow);
    makeKumDiff(prow);
}

void CRosterEdit::makeDiff(int prow)
{
    int istCol = ui->tbwRoster->columnCount()-4;
    int solCol = ui->tbwRoster->columnCount()-3;
    int difCol = ui->tbwRoster->columnCount()-2;
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

void CRosterEdit::makeKumDiff(int prow)
{
    int lPid = ui->tbwRoster->verticalHeaderItem(prow)->data(1).toInt();
    CPersonal *lPer = new CPersonal(lPid);
    QDate lBreak = lPer->BreakDate();
    CDiffTime BDdiff(lPer->BDdiff());
    QSqlQuery lqry;
    lqry.prepare("SELECT * from tblDuty WHERE PersID = :PID AND DDate > "":BDate"" AND DDate <= "":DDT;""");
    lqry.bindValue(":PID", lPer->id());
    lqry.bindValue(":BDate", lBreak.toString("yyyy-MM-dd"));
    QDate x;
    x.setDate(m_Year, m_Month, 1);
    x.setDate(m_Year, m_Month, x.daysInMonth());
    lqry.bindValue(":DDT", x.toString("yyyy-MM-dd"));
    lqry.exec();
    QString lerr = lqry.lastError().text();
    lqry.first();
    QList<CDuty> *dutyList = new QList<CDuty>();

    while(lqry.isValid())
    {
        CDuty* lDuty = new CDuty(lqry.value(lqry.record().indexOf("ID")).toInt());
        dutyList->append(*lDuty);
        lqry.next();
    }

    CDiffTime lDiff;
    lDiff.setTotalMins(0);

    for(int i = 0; i < dutyList->count(); i++)
    {
        CDiffTime lDailyHrs;
        CDiffTime lDur1;
        CDiffTime lDur2;
        CDiffTime lDur;

        lDur1.setTime(dutyList->at(i).Duration());
        lDur2.setTime(dutyList->at(i).Duration2());
        lDur.setTotalMins(lDur1.totalMins() + lDur2.totalMins());

        if(m_Holidays->checkForHoliday(dutyList->at(i).Date()))
        {
            lDailyHrs.setTotalMins(0);
        }
        else
        {
            lDailyHrs.setTime(lPer->SollTag());
        }

        CDiffTime bDiff;
        bDiff.setTotalMins(lDur.totalMins() - lDailyHrs.totalMins());
        lDiff.setTotalMins(lDiff.totalMins() + bDiff.totalMins());
    }

    lDiff.setTotalMins(lDiff.totalMins() + BDdiff.totalMins());
    QTableWidgetItem* litem = new QTableWidgetItem(lDiff.toString());
    litem->setTextAlignment(Qt::AlignRight);
    ui->tbwRoster->setItem(prow, ui->tbwRoster->columnCount()-1, litem);
}
