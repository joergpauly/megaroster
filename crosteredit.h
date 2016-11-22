/********************************************************************
*
*   File: crosteredit.h    Class: CRosterEdit
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
#ifndef CROSTEREDIT_H
#define CROSTEREDIT_H

// System-Header
#include <QWidget>
#include <QTableWidgetItem>

// Project-Header
#include "cdatabasemanager.h"
#include "cpersonal.h"
#include "cdutytype.h"
#include "cduty.h"
#include "cdtybasetype.h"
#include "choliday.h"
#include "cprealert.h"
#include "cprealerttype.h"
#include "crule.h"
#include "cprinttable.h"
#include "cdbuploader.h"
#include "cdifftime.h"
#include "choliday.h"
#include "cholidaydata.h"
#include "cholidaylist.h"
#include "croster.h"


namespace Ui {
class CRosterEdit;
}

class CRosterEdit : public QWidget
{
    Q_OBJECT

private:
    QWidget*            m_subWnd;
    QObject             *m_parent;
    CDatabaseManager    *m_db;
    QDate               m_dateFrom;
    QDate               m_dateTo;
    int                 m_cols;
    int                 m_rows;
    QList<CPersonal>    m_currentOfficers;
    bool                m_preSelected;
    CHoliday*           m_Holidays;
    CRoster*            m_Roster;
    QList<QList<CDuty>> m_list;
    CDuty*              m_actDuty;
    CDuty*              m_previousDuty;
    bool                m_updatingDetails;
    CPersonal           m_actUser;
    bool                m_checkingRules;
    bool                m_edit;
    bool                m_init;
    int                 m_Year;
    int                 m_Month;

public:
    explicit CRosterEdit(QWidget *parent = 0);
    CRosterEdit(QDate *pDate, QWidget *parent = 0);
    ~CRosterEdit();


    void setSubWnd(QWidget *pSubWnd);

private slots:
    void on_tbwRoster_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);
    void on_cmdPreviousMonth_clicked();
    void on_cmdNextMonth_clicked();
    void on_cmdCheckRoster_clicked();
    void on_dtedMonthChoice_dateChanged(const QDate &date);

    void on_tbwRoster_cellActivated(int row, int column);

    void on_tbwRoster_cellChanged(int row, int column);

    void on_tbwRoster_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::CRosterEdit *ui;

    void buildRoster(QDate *pDate);
    void buildHorizontalHeader();
    void buildVerticalHeader();
    void makeSollH(QDate pDate, int pwdays, int pcol);
    void fillRoster(QDate *pDate);
    void ActiveCellChanged(int row, int column);
    void saveSingleDuty(int row, int column);
    void updateDetails(int prow, int pcol);
    void updateDetails(CDuty* pDuty);
    void saveFromTable(int row, int col);
    void saveFromTable(QTableWidgetItem *pItem);
    void makeKumDiff(int prow);
    void makeDiff(int prow);
    void makeIstH(int prow);
    void makeIstH();

};

#endif // CROSTEREDIT_H
