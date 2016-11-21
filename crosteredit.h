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
#include "ccurrentofficers.h"

namespace Ui {
class CRosterEdit;
}

class CRosterEdit : public QWidget
{
    Q_OBJECT

private:
    QDate               m_dateFrom;
    QDate               m_dateTo;
    int                 m_Cols;
    CCurrentOfficers    *m_currentOfficers;

public:
    explicit CRosterEdit(QWidget *parent = 0);
    CRosterEdit(QDate *pDate, QWidget *parent = 0);
    ~CRosterEdit();

private slots:
    void on_tbwRoster_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);
    void on_cmdPreviousMonth_clicked();
    void on_cmdNextMonth_clicked();
    void on_cmdCheckRoster_clicked();
    void on_dtedMonthChoice_dateChanged(const QDate &date);

private:
    Ui::CRosterEdit *ui;

    void buildRoster(QDate *pDate);
    CCurrentOfficers* getCurrentOfficers();
};

#endif // CROSTEREDIT_H
