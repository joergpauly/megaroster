/****************************************************************************************
*
*   File: cholidayedit.h    Class: CHolidayEdit
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
#ifndef CHOLIDAYEDIT_H
#define CHOLIDAYEDIT_H

//System-Header
#include <QDialog>
#include <QMdiSubWindow>
#include <QMessageBox>

//Projekt-Header
#include "cholidaylist.h"


namespace Ui
{
    class CHolidayEdit;
}

class CHolidayEdit : public QDialog
{
    Q_OBJECT
private:
    QMdiSubWindow *m_SubWnd;
    CHolidayList *m_HolidayList;
    bool m_init;

public:
    explicit CHolidayEdit(QWidget *parent = 0);
    ~CHolidayEdit();

    void setSubWnd(QMdiSubWindow *pSubWnd);

private slots:
    void on_tblHolidays_cellClicked(int row, int column);
    void on_cmdNew_clicked();
    void on_tblHolidays_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_cmdKill_clicked();

private:
    Ui::CHolidayEdit *ui;
    void getFromList();
    void saveToDb(int previousRow);
};

#endif // CHOLIDAYEDIT_H
