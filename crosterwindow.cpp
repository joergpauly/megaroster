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
    m_edit = false;
    m_currentDuty = NULL;    
    m_parent = parent;
    m_actUser = new CPersonal(static_cast<CMainWindow*>(parent)->getUserID());
    ui->setupUi(this);
    m_Prefix = "";
    ui->cbShowAlerts->setChecked(true);
    ui->dtedMonthChoice->setDate(QDate::currentDate());
    m_Year = QDate::currentDate().year();
    m_Month = QDate::currentDate().month();
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
    m_checkingRules = false;
    loadRules();
}

CRosterWindow::CRosterWindow(QWidget *parent, int pMonth, int pYear) :
    QWidget(parent),
    ui(new Ui::CRosterWindow)
{
    QDate lDate(pYear, pMonth, 1);
    m_Month = pMonth;
    m_Year = pYear;
    m_edit = false;
    m_currentDuty = NULL;
    m_parent = parent;
    m_actUser = new CPersonal(static_cast<CMainWindow*>(parent)->getUserID());
    ui->setupUi(this);
    m_Prefix = "";
    ui->cbShowAlerts->setChecked(true);
    ui->dtedMonthChoice->setDate(lDate);
    setTabTitle(m_Prefix, lDate);
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
    m_checkingRules = false;
    loadRules();
}

CRosterWindow::~CRosterWindow()
{
    delete ui;
    delete m_Holidays;
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
    ui->tbwRoster->setColumnCount(ldays+4);

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

        if(m_Holidays->checkForHoliday(pDate) && pDate.dayOfWeek() < 6)
        {
            litem->setForeground(QBrush(lHolFg));
            litem->setBackground(QBrush(lHol));

            if(pDate.dayOfWeek()<6)
            {
                lwdays--;
            }

        }

        ui->tbwRoster->setHorizontalHeaderItem(i,litem);
        ui->tbwRoster->setColumnWidth(i,27);
    }

    QTableWidgetItem* litem = new QTableWidgetItem("Ist-h");
    ui->tbwRoster->setHorizontalHeaderItem(pDate.daysInMonth(), litem);
    ui->tbwRoster->setColumnWidth(pDate.daysInMonth(), 55);
    litem = new QTableWidgetItem("Soll-h");
    ui->tbwRoster->setHorizontalHeaderItem(pDate.daysInMonth()+1, litem);
    ui->tbwRoster->setColumnWidth(pDate.daysInMonth()+1, 55);
    litem = new QTableWidgetItem("Diff.");
    ui->tbwRoster->setHorizontalHeaderItem(pDate.daysInMonth()+2, litem);
    ui->tbwRoster->setColumnWidth(pDate.daysInMonth()+2, 55);
    litem = new QTableWidgetItem("Kum.Diff.");
    ui->tbwRoster->setHorizontalHeaderItem(pDate.daysInMonth()+3, litem);
    ui->tbwRoster->setColumnWidth(pDate.daysInMonth()+3, 55);
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

void CRosterWindow::makeIstH(int prow)
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

void CRosterWindow::makeDiff(int prow)
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

void CRosterWindow::makeKumDiff(int prow)
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
                lqry->prepare("INSERT INTO tblDuty (PersID, DDate, TypeID, Status, TimeFrom, TimeTo, TimeFrom2, TimeTo2, Dura, Dura2) VALUES (:PID, :DATE, :TID, 0, '00:00:00.000', '00:00:00.000', '00:00:00.000', '00:00:00.000', '00:00:00.000', '00:00:00.000');");
                lqry->bindValue(":PID", PerID);
                lqry->bindValue(":TID", CDutyType("--").id());
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
                QString lstr = "Suche Vormerkungen: ";
                CPersonal pers(PerID);
                lstr.append(pers.Name());
                lstr.append(", ");
                lstr.append(pers.VName());
                lstr.append("; ");
                lstr.append(ldate.toString("dd.MM.yyyy"));
                static_cast<CMainWindow*>(m_parent)->setStatusText(lstr);
                QSqlQuery lvqry;
                lvqry.prepare("SELECT * FROM tblPrealert WHERE DDate = :DAT AND PersID = :PID;");
                lvqry.bindValue(":DAT",ldate.toString("yyyy-MM-dd"));
                lvqry.bindValue(":PID", PerID);
                lvqry.exec();
                lvqry.first();

                if(lvqry.isValid())
                {
                    QFont fnt = item->font();
                    fnt.setBold(true);
                    fnt.setItalic(true);
                    fnt.setUnderline(true);
                    fnt.setPointSize(fnt.pointSize() + 2);
                    item->setFont(fnt);
                }

            }

            QColor lcol(ditem->Typ()->RosterColorR(),ditem->Typ()->RosterColorG(),ditem->Typ()->RosterColorB());
            item->setBackground(QBrush(lcol));                                                 
            item->setData(Qt::UserRole,ditem->id());
            ui->tbwRoster->setItem(row, col-1, item);
            delete ditem;
        }
    }

    if(newPlan)
    {
        makeRoster(pDate);
    }

    static_cast<CMainWindow*>(m_parent)->setStatusText("Bereit...");
    qApp->restoreOverrideCursor();
    delete lqry;   
}

void CRosterWindow::updateDetails(int prow, int pcol)
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

    m_currentDuty = new CDuty(ui->tbwRoster->item(prow, pcol)->data(Qt::UserRole).toInt());
    m_previousDuty = *m_currentDuty;
    updateDetails(m_currentDuty);
}

void CRosterWindow::updateDetails(CDuty *pDuty)
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
    updatePrealerts(pDuty);

    m_updatingDetails = false;

    if(!m_actUser->Edit())
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

void CRosterWindow::updatePrealerts(CDuty *pDuty)
{    
    if(ui->tbwRoster->selectedItems().count() > 1)
    {
        return;
    }

    ui->tblPrealerts->clear();
    ui->tblPrealerts->setColumnCount(1);
    CPrealert lpa(pDuty->Kollege()->id(), pDuty->Date());

    if(!lpa.paTypes() | (lpa.id() <= 0))
    {
        return;
    }

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
        litem->setTextAlignment(Qt::AlignCenter);
        ui->tblPrealerts->setItem(i,0,litem);
    }

}

void CRosterWindow::loadRules()
{
    QSqlQuery lqry;
    lqry.exec("SELECT * FROM tblDailyRule;");
    lqry.first();
    m_ruleList = new QList<CRule>();

    while(lqry.isValid())
    {
        CRule lrule(lqry.value(lqry.record().indexOf("ID")).toInt());
        m_ruleList->append(lrule);
        lqry.next();
    }
}

bool CRosterWindow::checkRules(QDate pdate)
{
    //TODO: Mindesfreizeit und Blocklängen prüfen!
    qApp->setOverrideCursor(QCursor(Qt::WaitCursor));    
    loadRules();
    int acCol = ui->tbwRoster->currentColumn();
    int acRow = ui->tbwRoster->currentRow();
    int lCol = pdate.day() - 1;
    bool lRulesFullfilled = false;

    for(int lrule = 0; lrule < m_ruleList->count(); lrule++)
    {

        for(int lrow = 0; lrow < ui->tbwRoster->rowCount(); lrow++)
        {
            ui->tbwRoster->setCurrentCell(lrow,lCol);
            CDutyType ltyp(ui->tbwRoster->currentItem()->text());           

            for(int lrt = 0; lrt < m_ruleList->at(lrule).tList()->count(); lrt++)
            {
                CDutyType ldtyp = m_ruleList->at(lrule).tList()->at(lrt);
                if(ltyp.id() == m_ruleList->at(lrule).tList()->at(lrt).id())
                {                    
                    ldtyp.setChecked(true);                    
                }                                
                m_ruleList->at(lrule).tList()->replace(lrt, ldtyp);
            }

        }

    }

    for(int lrule = 0; lrule < m_ruleList->count(); lrule++)
    {
        lRulesFullfilled = true;

        for(int rchecked = 0; rchecked < m_ruleList->at(lrule).tList()->count(); rchecked++)
        {

            if(!m_ruleList->at(lrule).tList()->at(rchecked).Checked())
            {
                lRulesFullfilled = false;
                break;
            }

        }

        if(lRulesFullfilled == true)
        {
            break;
        }

    }

    for(int lrule = 0; lrule < m_ruleList->count(); lrule++)
    {

        for(int rchecked = 0; rchecked < m_ruleList->at(lrule).tList()->count(); rchecked++)
        {
            CDutyType ldtyp = m_ruleList->at(lrule).tList()->at(rchecked);
            ldtyp.setChecked(false);
            m_ruleList->at(lrule).tList()->replace(rchecked, ldtyp);
        }

    }

    if(!lRulesFullfilled)
    {
        QTableWidgetItem *lhdr = ui->tbwRoster->horizontalHeaderItem(ui->tbwRoster->currentColumn());
        QFont fnt = lhdr->font();
        fnt.setPointSize(14);
        lhdr->setFont(fnt);
        ui->tbwRoster->setHorizontalHeaderItem(ui->tbwRoster->currentColumn(), lhdr);
    }
    else
    {
        QTableWidgetItem *lhdr = ui->tbwRoster->horizontalHeaderItem(ui->tbwRoster->currentColumn());
        QFont fnt = lhdr->font();
        fnt.setPointSize(9);
        lhdr->setFont(fnt);
        ui->tbwRoster->setHorizontalHeaderItem(ui->tbwRoster->currentColumn(), lhdr);
    }

    ui->tbwRoster->setCurrentCell(acRow,acCol);
    qApp->restoreOverrideCursor();    
    return lRulesFullfilled;
}

bool CRosterWindow::checkRuleSet(QList<CDutyType> pList)
{
    int lShall = pList.count();
    int lIs = 0;

    for(int i = 0; i < lShall; i++)
    {
        if(pList.at(i).Checked())
        {
            lIs++;
        }
    }

    if(lIs == lShall)
    {
        return true;
    }
    else
    {
        return false;
    }

}

void CRosterWindow::updateDutyDB()
{
    QSqlQuery qry;
    QTime ltime = QTime::fromString("00:00:00","hh:mm:ss");
    int secs1 = ui->timFrom->time().secsTo(ui->timTo->time());
    ltime = ltime.addSecs(secs1);
    m_currentDuty->setDuration(ltime);
    ltime = QTime::fromString("00:00:00","hh:mm:ss");
    int secs2 = ui->timFrom2->time().secsTo(ui->timTo2->time());
    ltime = ltime.addSecs(secs2);
    m_currentDuty->setDuration2(ltime);
    ltime = QTime::fromString("00:00:00","hh:mm:ss");
    ltime.addSecs(secs1 + secs2);
    ui->timDura->setTime(ltime);
    qry.prepare("UPDATE tblDuty SET TypeID = :TID, Status = :RQ, TimeFrom = :TF, TimeTo = :TT, Dura = :Dura, TimeFrom2 = :TFF, TimeTo2 = :TTT, Dura2 = :Dura2 WHERE ID = :ID;");
    int tid = m_currentDuty->Typ()->id();
    qry.bindValue(":TID", tid);
    qry.bindValue(":RQ", m_currentDuty->Request());
    QString tf = m_currentDuty->TimeFrom().toString("hh:mm:ss.zzz");
    qry.bindValue(":TF", tf);
    QString tt = m_currentDuty->TimeTo().toString("hh:mm:ss.zzz");
    qry.bindValue(":TT", tt);
    QString dur = m_currentDuty->Duration().toString("hh:mm:ss.zzz");
    qry.bindValue(":Dura", dur);
    QString tf2 = m_currentDuty->TimeFrom2().toString("hh:mm:ss.zzz");
    qry.bindValue(":TFF", tf2);
    QString tt2 = m_currentDuty->TimeTo2().toString("hh:mm:ss.zzz");
    qry.bindValue(":TTT", tt2);
    QString dur2 = m_currentDuty->Duration2().toString("hh:mm:ss.zzz");
    qry.bindValue(":Dura2", dur2);
    int did = m_currentDuty->id();
    qry.bindValue(":ID", did);
    qry.exec();
    updateDetails(m_currentDuty);
    makeIstH(ui->tbwRoster->currentRow());
    checkRules(m_currentDuty->Date());
}

void CRosterWindow::saveFromTable(int row, int col)
{
    QTableWidgetItem *item = ui->tbwRoster->item(row, col);
    saveFromTable(item);
}

void CRosterWindow::saveFromTable(QTableWidgetItem *pItem)
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
    entry.oldDuty = *m_previousDuty.Typ();
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
    m_previousDuty = *dty;
    delete dty;
    delete dtyp;
    m_edit = false;
}

void CRosterWindow::on_dtedMonthChoice_dateChanged(const QDate &date)
{
    m_init = true;
    qApp->setOverrideCursor(QCursor(Qt::WaitCursor));
    m_Month = date.month();
    m_Year = date.year();
    m_Holidays = new CHoliday(date.year());
    m_dbman = static_cast<CMainWindow*>(m_parent)->dataBase();
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

    if((item->column() <= ui->tbwRoster->columnCount() -3)
            & (item->data(Qt::UserRole).toInt() != 0)
            & !m_edit)
    {
        saveFromTable(item);
    }
}

void CRosterWindow::on_tbwRoster_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if(currentColumn >= ui->tbwRoster->columnCount() -3)
    {
        return;
    }
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
    delete m_DType;
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

        if(!lpa.valid())
        {
            return;
        }

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
    QPainter* localPainter = new QPainter();
    localPainter->begin(prt);

    QPoint lpos(50,50);
    QImage *logo = new QImage(":/gfx/ico/logo.jpg");
    localPainter->drawImage(lpos,*logo);

    lpos.setX(50 + logo->width() + 80);
    lpos.setY(80);
    QFont fnt;
    fnt.setPointSize(24);
    QFont oldfnt = localPainter->font();
    localPainter->setFont(fnt);
    localPainter->drawText(lpos, "Dienstplan " + QDate::longMonthName(ui->dtedMonthChoice->date().month()) + " " + QString::number(ui->dtedMonthChoice->date().year()));
    localPainter->setFont(oldfnt);

    lpos.setX(50 + ui->tbwRoster->verticalHeader()->width());
    lpos.setY(130);

    for(int i = 0; i < ui->tbwRoster->columnCount() - 2; i++)
    {        
        CPrintTableCell *cell = new CPrintTableCell(lpos, ui->tbwRoster->columnWidth(i)-5, ui->tbwRoster->horizontalHeader()->height(), ui->tbwRoster->horizontalHeaderItem(i)->text());
        QBrush brush = ui->tbwRoster->horizontalHeaderItem(i)->background();
        cell->setBrush(brush);
        cell->setAlign(Qt::AlignCenter);
        cell->draw(localPainter);
        lpos.setX(lpos.x() + cell->Rect().width());
    }

    lpos.setY(lpos.y()+ui->tbwRoster->horizontalHeader()->height());

    for(int row = 0; row < ui->tbwRoster->rowCount(); row++)
    {
        lpos.setX(50);
        int lhig;
        CPrintTableCell *cell = new CPrintTableCell(lpos,ui->tbwRoster->verticalHeader()->width(),ui->tbwRoster->rowHeight(row),ui->tbwRoster->verticalHeaderItem(row)->text());
        cell->setAlign(Qt::AlignLeft|Qt::AlignVCenter);
        cell->draw(localPainter);
        lpos.setX(50+ui->tbwRoster->verticalHeader()->width());

        for(int col = 0; col < ui->tbwRoster->columnCount() - 1; col++)
        {
            ui->tbwRoster->setCurrentCell(row,col);
            CPrintTableCell *cell = new CPrintTableCell(lpos,ui->tbwRoster->columnWidth(col)-5,ui->tbwRoster->rowHeight(row),ui->tbwRoster->currentItem()->text());
            cell->setBrush(ui->tbwRoster->currentItem()->background());

            if(ui->tbwRoster->columnCount() - col <= 3)
            {
                cell->setAlign(Qt::AlignRight|Qt::AlignVCenter);
            }
            else
            {
                cell->setAlign(Qt::AlignCenter);
            }

            cell->draw(localPainter);
            lpos.setX(lpos.x() + cell->Rect().width());
            lhig = cell->Rect().height();
        }

        lpos.setY(lpos.y() + lhig);
    }

    localPainter->end();
}

void CRosterWindow::on_tblPrealerts_itemDoubleClicked(QTableWidgetItem *item)
{
    CDutyType ltyp(item->data(Qt::UserRole).toInt());
    ui->tbwRoster->currentItem()->setText(ltyp.Mark());
    on_chkReq_clicked(true);
}

void CRosterWindow::on_cbShowAlerts_clicked(bool checked)
{
    qApp->setOverrideCursor(Qt::WaitCursor);
    makeRoster(ui->dtedMonthChoice->date());
}

void CRosterWindow::on_cmdCheckRoster_clicked()
{
    ((CMainWindow*)m_parent)->setStatusText("Prüfe Mindest-Besetzungsregeln...");    
    m_checkingRules = true;
    for(int day = 1; day <= QDate(m_Year, m_Month, 1).daysInMonth(); day++)
    {
        ui->tbwRoster->setCurrentCell(0,day-1);
        checkRules(QDate(m_Year,m_Month,day));
    }
    ((CMainWindow*)m_parent)->setStatusText("");
    m_checkingRules = false;
}

void CRosterWindow::on_timFrom_timeChanged(const QTime &time)
{
    if(!m_updatingDetails)
    {
        m_currentDuty->setTimeFrom(time);
        updateDutyDB();
    }
}

void CRosterWindow::on_timTo_timeChanged(const QTime &time)
{
    if(!m_updatingDetails)
    {
        m_currentDuty->setTimeTo(time);
        updateDutyDB();
    }
}

void CRosterWindow::on_timFrom2_timeChanged(const QTime &time)
{
    if(!m_updatingDetails)
    {
        m_currentDuty->setTimeFrom2(time);
        updateDutyDB();
    }
}

void CRosterWindow::on_timTo2_timeChanged(const QTime &time)
{
    if(!m_updatingDetails)
    {
        m_currentDuty->setTimeTo2(time);
        updateDutyDB();
    }
}

void CRosterWindow::on_cmdNextMonth_clicked()
{
    int lYear = ui->dtedMonthChoice->date().year();
    int lMonth = ui->dtedMonthChoice->date().month();
    if(lMonth == 12)
    {
        lYear++;
        lMonth = 1;
    }
    else
    {
        lMonth++;
    }
    ((CMainWindow*)m_parent)->openMonth(lMonth, lYear, false, this);
}

void CRosterWindow::on_cmdPreviousMonth_clicked()
{
    int lYear = ui->dtedMonthChoice->date().year();
    int lMonth = ui->dtedMonthChoice->date().month();
    if(lMonth == 1)
    {
        lYear--;
        lMonth = 12;
    }
    else
    {
        lMonth--;
    }
    ((CMainWindow*)m_parent)->openMonth(lMonth, lYear, true, this);
}

void CRosterWindow::on_chkReq_clicked(bool checked)
{
    m_currentDuty->setRequest(checked);
    updateDutyDB();
}

void CRosterWindow::on_cmdPublish_clicked()
{
    m_upLoader = new CDbUploader((CMainWindow*)m_parent);
    m_upLoader->doUpload();
}
