/****************************************************************************************
*
*   File: cholidayedit.cpp    Class: CHolidayEdit
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2015 Joerg Pauly
*   Created 30.12.2015 by joerg
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
#include "cholidayedit.h"
#include "ui_cholidayedit.h"

CHolidayEdit::CHolidayEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CHolidayEdit)
{
    m_init = true;
    ui->setupUi(this);
    getFromList();
    m_init = false;
}

CHolidayEdit::~CHolidayEdit()
{
    delete ui;
}

void CHolidayEdit::setSubWnd(QMdiSubWindow *pSubWnd)
{
    m_SubWnd = pSubWnd;
}

void CHolidayEdit::getFromList()
{
    m_HolidayList = new CHolidayList();
    ui->tblHolidays->setRowCount(0);

    for(int i = 0; i < m_HolidayList->count();i++)
    {
        ui->tblHolidays->setRowCount(i + 1);
        QTableWidgetItem *lItem = new QTableWidgetItem(m_HolidayList->at(i).Description());
        lItem->setData(Qt::UserRole,QVariant(m_HolidayList->at(i).ID()));
        ui->tblHolidays->setItem(i, 0, lItem);
        lItem = new QTableWidgetItem(QString::number(m_HolidayList->at(i).Day()));
        lItem->setTextAlignment(Qt::AlignRight);
        ui->tblHolidays->setItem(i, 1, lItem);
        lItem = new QTableWidgetItem(QString::number(m_HolidayList->at(i).Month()));
        lItem->setTextAlignment(Qt::AlignRight);
        ui->tblHolidays->setItem(i, 2, lItem);
        lItem = new QTableWidgetItem();
        lItem->setFlags(Qt::ItemIsUserCheckable);

        if(m_HolidayList->at(i).Movable())
        {
            lItem->setCheckState(Qt::Checked);
        }
        else
        {
            lItem->setCheckState(Qt::Unchecked);
        }

        ui->tblHolidays->setItem(i, 3, lItem);
    }
}

void CHolidayEdit::on_tblHolidays_cellClicked(int row, int column)
{
    if(column == 3)
    {
        if(ui->tblHolidays->item(row, column)->checkState() == Qt::Checked)
        {
            ui->tblHolidays->item(row, column)->setCheckState(Qt::Unchecked);
        }
        else
        {
            ui->tblHolidays->item(row, column)->setCheckState(Qt::Checked);
        }
    }
}

void CHolidayEdit::on_cmdNew_clicked()
{
    m_init = true;
    QSqlQuery lqry;
    lqry.exec("INSERT INTO tblHolidays (iDay) VALUES (0);");
    QTableWidgetItem *lItem = new QTableWidgetItem();
    lItem->setData(Qt::UserRole,lqry.lastInsertId());
    ui->tblHolidays->setRowCount(ui->tblHolidays->rowCount() + 1);
    ui->tblHolidays->setItem(ui->tblHolidays->rowCount() - 1, 0, lItem);
    lItem = new QTableWidgetItem(QString::number(0));
    lItem->setTextAlignment(Qt::AlignRight);
    ui->tblHolidays->setItem(ui->tblHolidays->rowCount() - 1, 1, lItem);
    lItem = new QTableWidgetItem(QString::number(0));
    lItem->setTextAlignment(Qt::AlignRight);
    ui->tblHolidays->setItem(ui->tblHolidays->rowCount() - 1, 2, lItem);
    lItem = new QTableWidgetItem();
    lItem->setFlags(Qt::ItemIsUserCheckable);
    lItem->setCheckState(Qt::Unchecked);
    ui->tblHolidays->setItem(ui->tblHolidays->rowCount() - 1, 3, lItem);
    ui->tblHolidays->selectRow(ui->tblHolidays->rowCount()-1);
    ui->tblHolidays->selectColumn(0);
    m_init = false;
}

void CHolidayEdit::saveToDb(int previousRow)
{
    QSqlQuery lqry;
    lqry.prepare("UPDATE tblHolidays SET Descr = :Desc, iDay = :day, iMonth = :Month, mvbl = :Mv WHERE ID = :ID;");
    lqry.bindValue(":ID", ui->tblHolidays->item(previousRow, 0)->data(Qt::UserRole).toInt());
    lqry.bindValue(":Desc", ui->tblHolidays->item(previousRow, 0)->text());
    lqry.bindValue(":day", ui->tblHolidays->item(previousRow, 1)->text().toInt());
    lqry.bindValue(":Month", ui->tblHolidays->item(previousRow, 2)->text().toInt());

    if(ui->tblHolidays->item(previousRow, 3)->checkState() == Qt::Checked)
    {
        lqry.bindValue(":Mv", 1);
    }
    else
    {
        lqry.bindValue(":Mv", 0);
    }

    lqry.exec();
}

void CHolidayEdit::on_tblHolidays_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if(m_init)
    {
        return;
    }
    if(previousRow < 0)
    {
        return;
    }
    saveToDb(previousRow);
}
