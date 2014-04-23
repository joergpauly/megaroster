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

#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

// System-Header
#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMdiSubWindow>

// Projekt-Header
#include "cdatabasemanager.h"
#include "crosterwindow.h"
#include "cpersonaledit.h"
#include "cdutytypeedit.h"
#include "choliday.h"
#include "cprintform.h"
#include "cprealertedit.h"

namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();
    CDatabaseManager* dataBase();
    void setStatusText(QString pText);

private slots:
    void on_actionProgramm_be_enden_triggered();
    void on_actionBe_arbeiten_triggered();
    void on_cmdEditRoster_clicked();

    void on_action_Personal_triggered();

    void on_action_Dienst_Arten_triggered();

    void on_cmdPersEdit_clicked();

    void on_cmdDType_clicked();

    void on_actionDruckvorlage_bearbeiten_triggered();

    void on_cmdPreAlerts_clicked();

private:
    // Properties
    Ui::CMainWindow *ui;
    CDatabaseManager* m_dbman;
    CRosterWindow* m_Roster;
    CPersonalEdit* m_PersEdit;
    CDutyTypeEdit* m_DTEdit;
    QString m_Username;

    // Funktionen
    void closeEvent(QCloseEvent* e);
    void openEditableRoster();
    void openPersonalEdit();
    void openDutyTypeEdit();
};

#endif // CMAINWINDOW_H
