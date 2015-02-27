/****************************************************************************************
*
*   File: cbranchedit.cpp
*
*   This file is part of the MEGASeries Project.
*   Copyright (C) 2015 Joerg Pauly, MEGAMover.de
*   File created 27.02.2015 by joerg
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

#include "cbranchedit.h"
#include "ui_cbranchedit.h"

CBranchEdit::CBranchEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CBranchEdit)
{
    ui->setupUi(this);
    setupBranchList();

    if(ui->tbvBranches->rowCount() > 0)
    {
        m_actBranch = new CBranch(ui->tbvBranches->item(0,0)->data(Qt::UserRole).toInt());
    }
    else
    {
        m_actBranch = new CBranch();
    }

}

CBranchEdit::~CBranchEdit()
{
    delete ui;
}

void CBranchEdit::setSubWnd(QMdiSubWindow *pSubWnd)
{
    m_subWnd = pSubWnd;
}

void CBranchEdit::on_txtName1_editingFinished()
{ 
    saveToDB();
}

void CBranchEdit::on_txtName2_editingFinished()
{    
    saveToDB();
}

void CBranchEdit::on_txtName3_editingFinished()
{
    saveToDB();
}

void CBranchEdit::on_txtAdress1_editingFinished()
{
    saveToDB();
}

void CBranchEdit::on_txtAdress2_editingFinished()
{
    saveToDB();
}

void CBranchEdit::on_txtAdress3_editingFinished()
{
    saveToDB();
}

void CBranchEdit::on_txtAdress4_editingFinished()
{
    saveToDB();
}

void CBranchEdit::on_txtAdress5_editingFinished()
{
    saveToDB();
}

void CBranchEdit::on_txtHours_editingFinished()
{
    saveToDB();
}

void CBranchEdit::on_cmdNew_clicked()
{
    m_actBranch = new CBranch();
    QSqlQuery lqry;
    lqry.prepare("INSERT INTO tblBranches (Name1) VALUES ('');");
    lqry.exec();
    m_actBranch->setID(lqry.lastInsertId().toInt());
    setupUiFields();
}

void CBranchEdit::on_cmdDelete_clicked()
{

}

void CBranchEdit::on_cmdClose_clicked()
{
    close();
}

void CBranchEdit::saveToDB()
{    
    //m_actBranch->setID(ui->txtID->text().toInt());
    m_actBranch->setName1(ui->txtName1->text());
    m_actBranch->setName2(ui->txtName2->text());
    m_actBranch->setName3(ui->txtName3->text());
    m_actBranch->setAdress1(ui->txtAdress1->text());
    m_actBranch->setAdress2(ui->txtAdress2->text());
    m_actBranch->setAdress3(ui->txtAdress3->text());
    m_actBranch->setAdress4(ui->txtAdress4->text());
    m_actBranch->setAdress5(ui->txtAdress5->text());
    m_actBranch->setHours(ui->txtHours->text());
    if(!m_actBranch->saveToDB())
    {
        QMessageBox lmsg;
        lmsg.setWindowTitle("Fehler!");
        lmsg.setText("Fehler beim Speichern in der Datenbank!");
        lmsg.setIcon( QMessageBox::Critical);
        lmsg.setStandardButtons(QMessageBox::Ok);
        lmsg.exec();
    }
    setupBranchList();
}

void CBranchEdit::setupUiFields()
{
    if(m_actBranch->Valid())
    {
        ui->txtID->setText(QString(m_actBranch->ID()));
        ui->txtName1->setText(m_actBranch->Name1());
        ui->txtName2->setText(m_actBranch->Name2());
        ui->txtName3->setText(m_actBranch->Name3());
        ui->txtAdress1->setText(m_actBranch->Adress1());
        ui->txtAdress2->setText(m_actBranch->Adress2());
        ui->txtAdress3->setText(m_actBranch->Adress3());
        ui->txtAdress4->setText(m_actBranch->Adress4());
        ui->txtAdress5->setText(m_actBranch->Adress5());
        ui->txtHours->setText(m_actBranch->Hours());
    }

}

void CBranchEdit::setupBranchList()
{
    ui->tbvBranches->clear();
    ui->tbvBranches->setColumnCount(5);
    ui->tbvBranches->setRowCount(0);
    QSqlQuery lqry;
    lqry.prepare("SELECT * FROM tblBranches ORDER BY ID;");
    lqry.exec();
    lqry.first();

    while(lqry.isValid())
    {        
        ui->tbvBranches->setRowCount(ui->tbvBranches->rowCount() + 1);
        QTableWidgetItem *litem = new QTableWidgetItem(lqry.value(lqry.record().indexOf("ID")).toString());
        litem->setData(Qt::UserRole, lqry.value(lqry.record().indexOf("ID")).toInt());
        ui->tbvBranches->setItem((ui->tbvBranches->rowCount() - 1),0,litem);
        litem = new QTableWidgetItem(lqry.value(lqry.record().indexOf("Name1")).toString());
        ui->tbvBranches->setItem((ui->tbvBranches->rowCount() - 1), 1, litem);
        litem = new QTableWidgetItem(lqry.value(lqry.record().indexOf("Name2")).toString());
        ui->tbvBranches->setItem((ui->tbvBranches->rowCount() - 1), 2, litem);
        litem = new QTableWidgetItem(lqry.value(lqry.record().indexOf("Name3")).toString());
        ui->tbvBranches->setItem((ui->tbvBranches->rowCount() - 1), 3, litem);
        litem = new QTableWidgetItem(lqry.value(lqry.record().indexOf("Adress3")).toString());
        ui->tbvBranches->setItem((ui->tbvBranches->rowCount() - 1), 4, litem);
        lqry.next();
    }

}

void CBranchEdit::on_tbvBranches_cellClicked(int row, int column)
{
    saveToDB();
    QSqlQuery lqry;
    m_actBranch = new CBranch(ui->tbvBranches->item(row,0)->data(Qt::UserRole).toInt());
    setupUiFields();
}
