/****************************************************************************************
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 13.04.2014 by joerg
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

#ifndef CPREALERT_H
#define CPREALERT_H

// System-Header
#include <QWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QList>
#include <QMdiSubWindow>
#include <QMenu>
#include <QAction>
#include <QTreeWidgetItem>

// Projekt-Header
#include "cpersonal.h"
#include "cdutytype.h"
#include "cdatabasemanager.h"

namespace Ui {
class CPrealert;
}

class CPrealert : public QWidget
{
    Q_OBJECT

public:
    explicit CPrealert(QWidget *parent = 0);
    ~CPrealert();
    void setSubWnd(QMdiSubWindow *pSubWnd);

private slots:
    void on_cmbPersonal_currentIndexChanged(int index);
    void on_dtMenu(QAction *pAction);

    void on_trvDutyTypes_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);


    void on_trvDutyTypes_itemClicked(QTreeWidgetItem *item, int column);

    void on_cmdNewDuty_clicked();

private:
    Ui::CPrealert *ui;
    QWidget *m_parent;
    QMdiSubWindow *m_subWnd;
    CDatabaseManager *m_db;
    QList<CPersonal> *m_PersList;
    QList<CDutyType> *m_DutyTypes;
    CPersonal *m_actPers;
    QMenu *m_dtMenu;

};

#endif // CPREALERT_H
