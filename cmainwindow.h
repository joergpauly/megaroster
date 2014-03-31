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

#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

// System-Header
#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMdiSubWindow>

// Projekt-Header
#include "crosterwindow.h"

namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

private slots:
    void on_actionProgramm_be_enden_triggered();

    void on_actionBe_arbeiten_triggered();

private:
    // Properties
    Ui::CMainWindow *ui;
    CRosterWindow* m_Roster;

    // Funktionen
    void closeEvent(QCloseEvent* e);
};

#endif // CMAINWINDOW_H
