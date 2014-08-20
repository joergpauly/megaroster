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

#include "cdutytypeedit.h"
#include "ui_cdutytypeedit.h"
#include "cmainwindow.h"

CDutyTypeEdit::CDutyTypeEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDutyTypeEdit)
{
    m_parent = parent;
    ui->setupUi(this);
    connect(qApp,SIGNAL(focusChanged(QWidget*,QWidget*)),this,SLOT(setSelected(QWidget*,QWidget*)));
    loadTable();
    fillDTypeTable();
    fillDBTcombo();
}

CDutyTypeEdit::~CDutyTypeEdit()
{
    disconnect(this,SLOT(setSelected(QWidget*,QWidget*)));
    delete ui;
}

void CDutyTypeEdit::setSubWnd(QMdiSubWindow *pSubWnd)
{
    m_SubWnd = pSubWnd;
}

void CDutyTypeEdit::loadTable()
{
    m_qry = new QSqlQuery();
    m_qry->prepare("SELECT * FROM tblDutyTypes ORDER BY Mark;");
    m_qry->exec();
}

void CDutyTypeEdit::fillDTypeTable()
{
    ui->tblDutytps->setRowCount(0);
    ui->tblDutytps->setColumnCount(7);;

    m_qry->first();
    int i = 0;

    while(m_qry->isValid())
    {
        ui->tblDutytps->setRowCount(ui->tblDutytps->rowCount()+1);
        QTableWidgetItem* litem = new QTableWidgetItem(m_qry->value(m_qry->record().indexOf("Mark")).toString());
        litem->setData(Qt::UserRole,m_qry->value(m_qry->record().indexOf("ID")).toInt());
        QColor lclr;
        lclr.setRed(m_qry->value(m_qry->record().indexOf("ColorR")).toInt());
        lclr.setGreen(m_qry->value(m_qry->record().indexOf("ColorG")).toInt());
        lclr.setBlue(m_qry->value(m_qry->record().indexOf("ColorB")).toInt());
        litem->setBackgroundColor(lclr);
        ui->tblDutytps->setItem(i,0,litem);
        litem = new QTableWidgetItem(m_qry->value(m_qry->record().indexOf("Decr")).toString());
        ui->tblDutytps->setItem(i,1,litem);
        //TODO: Basistyp
        litem = new QTableWidgetItem();
        QTime ltime = QTime::fromString(m_qry->value(m_qry->record().indexOf("TimeFrom")).toString(),"hh:mm:ss.zzz");
        litem->setText(ltime.toString("hh:mm"));
        ui->tblDutytps->setItem(i,2,litem);
        litem = new QTableWidgetItem();
        ltime = QTime::fromString(m_qry->value(m_qry->record().indexOf("TimeTo")).toString(),"hh:mm:ss.zzz");
        litem->setText(ltime.toString("hh:mm"));
        ui->tblDutytps->setItem(i,3,litem);
        litem = new QTableWidgetItem();
        ltime = QTime::fromString(m_qry->value(m_qry->record().indexOf("TimeFrom2")).toString(),"hh:mm:ss.zzz");
        litem->setText(ltime.toString("hh:mm"));
        ui->tblDutytps->setItem(i,4,litem);
        litem = new QTableWidgetItem();
        ltime = QTime::fromString(m_qry->value(m_qry->record().indexOf("TimeTo2")).toString(),"hh:mm:ss.zzz");
        litem->setText(ltime.toString("hh:mm"));
        ui->tblDutytps->setItem(i,5,litem);
        litem = new QTableWidgetItem();
        int ltyp = m_qry->value(m_qry->record().indexOf("BaseType")).toInt();
        CDtyBaseType ltp(ltyp);
        litem->setText(ltp.Desc());
        ui->tblDutytps->setItem(i,6,litem);
        i++;
        m_qry->next();
    }

    QTableWidgetItem* hdr = new QTableWidgetItem();
    hdr->setText("F/S/N");
    ui->tblDutytps->setHorizontalHeaderItem(0,hdr);
    hdr = new QTableWidgetItem();
    hdr->setText("Bezeichnung");
    ui->tblDutytps->setHorizontalHeaderItem(1,hdr);
    hdr = new QTableWidgetItem();
    hdr->setText("Dienst-Beginn");
    ui->tblDutytps->setHorizontalHeaderItem(2,hdr);
    hdr = new QTableWidgetItem();
    hdr->setText("Dienst-Ende");
    ui->tblDutytps->setHorizontalHeaderItem(3,hdr);
    hdr = new QTableWidgetItem();
    hdr->setText("2. Dienst-Beginn");
    ui->tblDutytps->setHorizontalHeaderItem(4,hdr);
    hdr = new QTableWidgetItem();
    hdr->setText("2. Dienst-Ende");
    ui->tblDutytps->setHorizontalHeaderItem(5,hdr);
    hdr = new QTableWidgetItem();
    hdr->setText("Basis-Typ");
    ui->tblDutytps->setHorizontalHeaderItem(6,hdr);
}

void CDutyTypeEdit::fillDBTcombo()
{
    CDatabaseManager *dbman = ((CMainWindow*)m_parent)->dataBase();
    QList<CDtyBaseType> dbtList(*dbman->dbaseList());
    for(int i = 0; i < dbtList.count(); i++)
    {
        ui->cmbBaseType->addItem(dbtList.at(i).CLetter(), dbtList.at(i).id());
    }
    delete dbman;
}

void CDutyTypeEdit::updateUI()
{    
    ui->txtMark->setText(m_qry->value(m_qry->record().indexOf("Mark")).toString());
    ui->txtDescr->setText(m_qry->value(m_qry->record().indexOf("Decr")).toString());
    QString lstr = m_qry->value(m_qry->record().indexOf("TimeFrom")).toString();
    QTime lTime = QTime::fromString(lstr,"hh:mm:ss.zzz");
    ui->timStart->setTime(lTime);
    lstr = m_qry->value(m_qry->record().indexOf("TimeTo")).toString();
    lTime = QTime::fromString(lstr,"hh:mm:ss.zzz");
    ui->timEnd->setTime(lTime);
    lstr = m_qry->value(m_qry->record().indexOf("TimeElapsed")).toString();
    lTime = QTime::fromString(lstr,"hh:mm:ss.zzz");
    ui->timDur->setTime(lTime);
    lstr = m_qry->value(m_qry->record().indexOf("TimeFrom2")).toString();
    lTime = QTime::fromString(lstr,"hh:mm:ss.zzz");
    ui->timStart2->setTime(lTime);
    lstr = m_qry->value(m_qry->record().indexOf("TimeTo2")).toString();
    lTime = QTime::fromString(lstr,"hh:mm:ss.zzz");
    ui->timEnd2->setTime(lTime);
    lstr = m_qry->value(m_qry->record().indexOf("TimeElapsed2")).toString();
    lTime = QTime::fromString(lstr,"hh:mm:ss.zzz");
    ui->timDur2->setTime(lTime);
    lstr = m_qry->value(m_qry->record().indexOf("MinOffBefore")).toString();
    lTime = QTime::fromString(lstr,"hh:mm:ss.zzz");
    ui->timBefore->setTime(lTime);
    lstr = m_qry->value(m_qry->record().indexOf("MinOffAfter")).toString();
    lTime = QTime::fromString(lstr,"hh:mm:ss.zzz");
    ui->timAfter->setTime(lTime);
    m_clr.setRed(m_qry->value(m_qry->record().indexOf("ColorR")).toInt());
    m_clr.setGreen(m_qry->value(m_qry->record().indexOf("ColorG")).toInt());
    m_clr.setBlue(m_qry->value(m_qry->record().indexOf("ColorB")).toInt());
    QPalette lpal;
    lpal.setColor(QPalette::Button,m_clr);
    ui->cmdColor->setPalette(lpal);
    CDtyBaseType ldbt(m_qry->value(m_qry->record().indexOf("BaseType")).toInt());
    for(int i = 0; i < ui->cmbBaseType->count(); i++)
    {
        ui->cmbBaseType->setCurrentIndex(i);
        if(ui->cmbBaseType->currentData().toInt() == ldbt.id())
        {
            break;
        }
    }
}

void CDutyTypeEdit::updateRecord(int pID)
{
    m_qry = new QSqlQuery();
    m_qry->prepare("UPDATE tblDutyTypes SET Mark = :Mark, Decr = :DECR, TimeFrom = :TF, TimeTo = :TT, TimeElapsed = :TE, TimeFrom2 = :TF2, TimeTo2 = :TT2, TimeElapsed2 = :TE2, MinOffBefore = :MB, MinOffAfter = :MA, ColorR = :CR, ColorG = :CG, ColorB = :CB, BaseType = :BT WHERE ID = :ID;");
    m_qry->bindValue(":Mark", ui->txtMark->text());
    m_qry->bindValue(":DECR", ui->txtDescr->text());
    m_qry->bindValue(":TF",ui->timStart->time());
    m_qry->bindValue(":TT",ui->timEnd->time());
    m_qry->bindValue(":TE",ui->timDur->time());
    m_qry->bindValue(":TF2",ui->timStart2->time());
    m_qry->bindValue(":TT2",ui->timEnd2->time());
    m_qry->bindValue(":TE2",ui->timDur2->time());
    m_qry->bindValue(":MB",ui->timBefore->time());
    m_qry->bindValue(":MA",ui->timAfter->time());
    m_qry->bindValue(":CR",m_clr.red());
    m_qry->bindValue(":CG",m_clr.green());
    m_qry->bindValue(":CB",m_clr.blue());
    m_qry->bindValue(":BT",ui->cmbBaseType->currentData().toInt());
    m_qry->bindValue(":ID", pID);
    m_qry->exec();
    QString err = m_qry->lastError().text();
    loadTable();
    fillDTypeTable();
}

void CDutyTypeEdit::getFromID(int pID)
{
    m_qry = new QSqlQuery();
    m_qry->prepare("SELECT * FROM tblDutyTypes WHERE ID = :ID;");
    m_qry->bindValue(":ID",pID);
    m_qry->exec();
    m_qry->first();
    m_ID = m_qry->value(m_qry->record().indexOf("ID")).toInt();
}


void CDutyTypeEdit::on_tblDutytps_cellClicked(int row, int column)
{
    //column auf 0 setzen, um die Warnung zu unterdrücken
    column = 0;
    //Record holen
    m_ID = ui->tblDutytps->item(row,column)->data(Qt::UserRole).toInt();
    getFromID(m_ID);
    updateUI();
    ui->txtMark->setFocus();
}

void CDutyTypeEdit::on_cmdColor_clicked()
{
    m_clr = QColorDialog::getColor(m_clr);
    QPalette lpal;
    lpal.setColor(QPalette::Button,m_clr);
    ui->cmdColor->setPalette(lpal);
    updateRecord(m_ID);
    updateUI();
}

void CDutyTypeEdit::on_cmdNew_clicked()
{
    m_qry = new QSqlQuery();
    m_qry->prepare("INSERT INTO tblDutyTypes (Mark, Decr, TimeFrom, TimeFrom2, TimeTo, TimeTo2, TimeElapsed, TimeElapsed2, MinOffBefore, MinOffAfter, ColorR, ColorG, ColorB, BaseType) VALUES ('-', '-', '00:00:00.000', '00:00:00.000', '00:00:00.000', '00:00:00.000','00:00:00.000', '00:00:00.000', '00:00:00.000', '00:00:00.000', 255, 255, 255, 0);");
    m_qry->exec();
    m_lastInserted = m_qry->lastInsertId().toInt();
    loadTable();
    fillDTypeTable();
    getFromID(m_lastInserted);
    updateUI();
    ui->txtMark->setFocus();
}

void CDutyTypeEdit::on_txtMark_editingFinished()
{
    updateRecord(m_ID);
}

void CDutyTypeEdit::on_txtDescr_editingFinished()
{
    updateRecord(m_ID);
}

void CDutyTypeEdit::on_timStart_editingFinished()
{
    updateRecord(m_ID);
}

void CDutyTypeEdit::on_timEnd_editingFinished()
{
    QTime ltime = QTime::fromString("00:00:00","hh:mm:ss");
    QTime lTS = ui->timStart->time();
    QTime lTE = ui->timEnd->time();
    int lsecs = lTS.secsTo(lTE);
    QTime ltime2 = ltime.addSecs(lsecs);
    ui->timDur->setTime(ltime2);
    updateRecord(m_ID);
}

void CDutyTypeEdit::on_timBefore_editingFinished()
{
    updateRecord(m_ID);
}

void CDutyTypeEdit::on_timAfter_editingFinished()
{
    updateRecord(m_ID);
}

void CDutyTypeEdit::on_timStart2_editingFinished()
{
    updateRecord(m_ID);
}

void CDutyTypeEdit::on_timEnd2_editingFinished()
{
    QTime ltime = QTime::fromString("00:00:00","hh:mm:ss");
    QTime lTS = ui->timStart2->time();
    QTime lTE = ui->timEnd2->time();
    int lsecs = lTS.secsTo(lTE);
    QTime ltime2 = ltime.addSecs(lsecs);
    ui->timDur2->setTime(ltime2);
    updateRecord(m_ID);
}

void CDutyTypeEdit::setSelected(QWidget *pold, QWidget *pnew)
{
    if(pnew)
    {
        if(pnew->objectName().left(3) == "txt")
        {
            ((QLineEdit*)pnew)->selectAll();
        }
    }

}

void CDutyTypeEdit::on_cmbBaseType_currentIndexChanged(int index)
{
    updateRecord(m_ID);
}
