/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 31.03.2014 by joerg
*   All Rights reserved
*
*   ChartButler ist Freie Software: Sie können es unter den Bedingungen
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

#include "cpersonaledit.h"
#include "ui_cpersonaledit.h"

CPersonalEdit::CPersonalEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPersonalEdit)
{
    ui->setupUi(this);
    loadTable();
    fillPersTable();
}

CPersonalEdit::~CPersonalEdit()
{
    delete ui;
}

void CPersonalEdit::setSubWnd(QMdiSubWindow *pSubWnd)
{
    m_SubWnd = pSubWnd;
}

void CPersonalEdit::loadTable()
{
    m_qry = new QSqlQuery();
    m_qry->prepare("SELECT * FROM tblPersonal order by Name;");
    m_qry->exec();
}

void CPersonalEdit::fillPersTable()
{
    //ui->tblPersonal->clear();
    ui->tblPersonal->setRowCount(0);
    ui->tblPersonal->setColumnCount(7);

    m_qry->first();
    int i = 0;
    while(m_qry->isValid())
    {
        ui->tblPersonal->setRowCount(ui->tblPersonal->rowCount()+1);
        QTableWidgetItem *lName = new QTableWidgetItem(m_qry->value(m_qry->record().indexOf("Name")).toString());
        lName->setData(1,m_qry->value(m_qry->record().indexOf("ID")).toInt());
        QTableWidgetItem *lVName = new QTableWidgetItem(m_qry->value(m_qry->record().indexOf("VName")).toString());
        QTableWidgetItem *lPersNo = new QTableWidgetItem(m_qry->value(m_qry->record().indexOf("PNr")).toString());
        QDate GBdat = QDate::fromString(m_qry->value(m_qry->record().indexOf("GebDat")).toString(),"yyyy-MM-dd");
        QTableWidgetItem *lGebDat = new QTableWidgetItem(GBdat.toString("dd.MM.yyyy"));
        QTime STd = QTime::fromString(m_qry->value(m_qry->record().indexOf("SollTag")).toString(),"hh:mm:ss.zzz");
        QTableWidgetItem *lSollH = new QTableWidgetItem(STd.toString("hh:mm"));
        QDate ETdat = QDate::fromString(m_qry->value(m_qry->record().indexOf("Eintritt")).toString(),"yyyy-MM-dd");
        QTableWidgetItem *lETDat = new QTableWidgetItem(ETdat.toString("dd.MM.yyyy"));
        QDate ATdat = QDate::fromString(m_qry->value(m_qry->record().indexOf("Austritt")).toString(),"yyyy-MM-dd");
        QTableWidgetItem *lATDat = new QTableWidgetItem(ATdat.toString("dd.MM.yyyy"));


        ui->tblPersonal->setItem(i,0,lName);
        ui->tblPersonal->setItem(i,1,lVName);
        ui->tblPersonal->setItem(i,2,lPersNo);
        ui->tblPersonal->setItem(i,3,lGebDat);
        ui->tblPersonal->setItem(i,4,lSollH);
        ui->tblPersonal->setItem(i,5,lETDat);
        ui->tblPersonal->setItem(i,6,lATDat);
        i++;
        m_qry->next();
    }    

    QTableWidgetItem* hdr = new QTableWidgetItem();
    hdr->setText("Name");
    ui->tblPersonal->setHorizontalHeaderItem(0,hdr);
    hdr = new QTableWidgetItem();
    hdr->setText("Vorname");
    ui->tblPersonal->setHorizontalHeaderItem(1,hdr);
    hdr = new QTableWidgetItem();
    hdr->setText("Pers.-Nr.");
    ui->tblPersonal->setHorizontalHeaderItem(2,hdr);
    hdr = new QTableWidgetItem();
    hdr->setText("Geburtsdatum");
    ui->tblPersonal->setHorizontalHeaderItem(3,hdr);
    hdr = new QTableWidgetItem();
    hdr->setText("Soll-Std./Tag");
    ui->tblPersonal->setHorizontalHeaderItem(4,hdr);
    hdr = new QTableWidgetItem();
    hdr->setText("Eintritt");
    ui->tblPersonal->setHorizontalHeaderItem(5,hdr);
    hdr = new QTableWidgetItem();
    hdr->setText("Austritt");
    ui->tblPersonal->setHorizontalHeaderItem(6,hdr);
}

void CPersonalEdit::updateUI()
{
    //Daten in Edit-Felder schreiben
    QString Name = m_qry->value(m_qry->record().indexOf("Name")).toString();
    ui->txtName->setText(Name);
    QString VName = m_qry->value(m_qry->record().indexOf("VName")).toString();
    ui->txtVName->setText(VName);
    QString PNr = m_qry->value(m_qry->record().indexOf("PNr")).toString();
    ui->txtPersNo->setText(PNr);
    QString GDat = m_qry->value(m_qry->record().indexOf("GebDat")).toString();
    QDate GDate = QDate::fromString(GDat,"yyyy-MM-dd");
    ui->datGebDat->setDate(GDate);
    QString SollTag = m_qry->value(m_qry->record().indexOf("SollTag")).toString();
    QTime STg = QTime::fromString(SollTag,"hh:mm:ss.zzz");
    ui->timSollTag->setTime(STg);
    QString ETat = m_qry->value(m_qry->record().indexOf("Eintritt")).toString();
    QDate ETDate = QDate::fromString(ETat,"yyyy-MM-dd");
    ui->datEintritt->setDate(ETDate);
    QString ATDat = m_qry->value(m_qry->record().indexOf("Austritt")).toString();
    QDate ATDate = QDate::fromString(ATDat,"yyyy-MM-dd");
    ui->datAustritt->setDate(ATDate);
}

void CPersonalEdit::getFromID(int pID)
{
    m_qry = new QSqlQuery();
    m_qry->prepare("SELECT * FROM tblPersonal WHERE ID = :ID;");
    m_qry->bindValue(":ID",pID);
    m_qry->exec();
    m_qry->first();
    m_id = m_qry->value(m_qry->record().indexOf("ID")).toInt();
}

void CPersonalEdit::updateRecord(int pID)
{
    m_qry = new QSqlQuery();
    m_qry->prepare("UPDATE tblPersonal SET Name = :Name, VName = :VName, PNr = :PNr, GebDat = :GBD, SollTag = :Soll, Eintritt = :ED, Austritt = :AD WHERE ID = :ID");
    m_qry->bindValue(":Name",ui->txtName->text());
    m_qry->bindValue(":VName",ui->txtVName->text());
    m_qry->bindValue(":PNr",ui->txtPersNo->text());
    m_qry->bindValue(":GBD",ui->datGebDat->date());
    m_qry->bindValue(":Soll",ui->timSollTag->time());
    m_qry->bindValue(":ED",ui->datEintritt->date());
    m_qry->bindValue(":AD",ui->datAustritt->date());
    m_qry->bindValue(":ID",pID);
    m_qry->exec();
    loadTable();
    fillPersTable();
}


void CPersonalEdit::on_tblPersonal_cellClicked(int row, int column)
{
    //column auf 0 setzen, um die Warnung zu unterdrücken
    column = 0;
    //Record holen
    m_id = ui->tblPersonal->item(row,column)->data(1).toInt();
    getFromID(m_id);
    updateUI();
}

void CPersonalEdit::on_cmdNew_clicked()
{
    m_qry = new QSqlQuery();
    m_qry->prepare("INSERT INTO tblPersonal (Name, VName, PNr, GebDat, SollTag, Eintritt, Austritt) VALUES (' ', ' ', ' ', '01.01.1970', '00:00:00', '01.01.1970','01.01.2070');");
    m_qry->exec();
    m_lastInserted = m_qry->lastInsertId().toInt();
    loadTable();
    fillPersTable();
    getFromID(m_lastInserted);
    updateUI();
    ui->txtName->setFocus();
}

void CPersonalEdit::on_txtName_editingFinished()
{
    updateRecord(m_id);
}

void CPersonalEdit::on_txtVName_editingFinished()
{
    updateRecord(m_id);
}

void CPersonalEdit::on_datGebDat_editingFinished()
{
    updateRecord(m_id);
}

void CPersonalEdit::on_txtPersNo_editingFinished()
{
    updateRecord(m_id);
}

void CPersonalEdit::on_timSollTag_editingFinished()
{
    updateRecord(m_id);
}

void CPersonalEdit::on_cmdSave_clicked()
{
    updateRecord(m_id);
}

void CPersonalEdit::on_cmdKill_clicked()
{
    QMessageBox *ldlg = new QMessageBox();
    ldlg->setWindowTitle("Personal-Satz Löschen");
    ldlg->setText("Wollen Sie diesen Personal-Datensatz wirklich löschen?");
    ldlg->setInformativeText("Dadurch werden auch alle Dienstplan-\nEinträge unwiderruflich gelöscht!\nSiehe auch unter 'Details'.");
    ldlg->setDetailedText("Bei Ausscheiden aus dem Dienst ist lediglich\ndas Datum des Ausscheidens einzutragen!");
    ldlg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    ldlg->setDefaultButton(QMessageBox::No);
    ldlg->setIcon(QMessageBox::Critical);
    if(ldlg->exec() == QMessageBox::Yes)
    {
        m_qry = new QSqlQuery();
        m_qry->prepare("DELETE FROM tblPersonal WHERE ID = :ID;");
        m_qry->bindValue(":ID",m_id);
        m_qry->exec();
        m_qry = new QSqlQuery();
        m_qry->prepare("DELETE FROM tblDuty WHERE PersID = :ID;");
        m_qry->bindValue(":ID",m_id);
        m_qry->exec();
    }
    loadTable();
    fillPersTable();
}

void CPersonalEdit::on_datEintritt_editingFinished()
{
    updateRecord(m_id);
}

void CPersonalEdit::on_datAustritt_editingFinished()
{
    updateRecord(m_id);
}
