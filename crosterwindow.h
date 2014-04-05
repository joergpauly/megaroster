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
#ifndef CROSTERWINDOW_H
#define CROSTERWINDOW_H

// System-Header
#include <QWidget>
#include <QMdiSubWindow>
#include <QList>

// Projekt-Header
#include "cdatabasemanager.h"
#include "cpersonal.h"
#include "cdutytype.h"
#include "cduty.h"
#include "choliday.h"

namespace Ui {
class CRosterWindow;
}

class CRosterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CRosterWindow(QWidget *parent = 0);
    explicit CRosterWindow(QWidget *parent, int pMonth, int pYear);
    ~CRosterWindow();
    void setSubWnd(QWidget* pSubWnd);

private slots:
    void on_dtedMonthChoice_dateChanged(const QDate &date);

private:
    // Properties
    Ui::CRosterWindow *ui;
    QWidget* m_subWnd;
    QString m_Prefix;
    int m_Month;
    int m_Year;
    QWidget* m_parent;
    CDatabaseManager* m_dbman;
    CHoliday* m_Holidays;
    QList<CDuty>* m_duty;

    // Funktionen
    void setTabTitle(QString pPrefix, QDate pDate);
    void makeRows(QDate pDate);
    void makeColumns(QDate pDate);
    void makeSollH(QDate pDate, int pwdays, int pcol);
    void makeRoster(QDate pDate);

};

#endif // CROSTERWINDOW_H
