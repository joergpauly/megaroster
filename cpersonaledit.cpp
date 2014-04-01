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
    ui->tblPersonal->clear();
    ui->tblPersonal->setColumnCount(5);

    m_qry->first();
    int i = 0;
    while(m_qry->isValid())
    {
        ui->tblPersonal->setRowCount(ui->tblPersonal->rowCount()+1);
        QTableWidgetItem *lName = new QTableWidgetItem(m_qry->value(m_qry->record().indexOf("Name")).toString());
        QTableWidgetItem *lVName = new QTableWidgetItem(m_qry->value(m_qry->record().indexOf("VName")).toString());
        QTableWidgetItem *lPersNo = new QTableWidgetItem(m_qry->value(m_qry->record().indexOf("PNr")).toString());
        QTableWidgetItem *lGebDat = new QTableWidgetItem(m_qry->value(m_qry->record().indexOf("GebDat")).toString());
        QTableWidgetItem *lSollH = new QTableWidgetItem(m_qry->value(m_qry->record().indexOf("SollTag")).toString());


        ui->tblPersonal->setItem(i,0,lName);
        ui->tblPersonal->setItem(i,1,lVName);
        ui->tblPersonal->setItem(i,2,lPersNo);
        ui->tblPersonal->setItem(i,3,lGebDat);
        ui->tblPersonal->setItem(i,4,lSollH);
        i++;
        m_qry->next();
    }    
}


void CPersonalEdit::on_tblPersonal_cellClicked(int row, int column)
{

}
