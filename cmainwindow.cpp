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

#include "cmainwindow.h"
#include "ui_cmainwindow.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::on_actionProgramm_be_enden_triggered()
{
    this->close();
}

void CMainWindow::closeEvent(QCloseEvent *e)
{
    QMessageBox lQuitDlg;
    lQuitDlg.setWindowTitle("Programmende");
    lQuitDlg.setText("Möchten Sie MEGARoster beenden?");
    lQuitDlg.setInformativeText("Die Daten werden gespeichert und das Programm wird beendet.");
    lQuitDlg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    lQuitDlg.setDefaultButton(QMessageBox::No);
    lQuitDlg.setButtonText(QMessageBox::Yes,"Be&enden");
    lQuitDlg.setButtonText(QMessageBox::No, "&Nicht beenden");
    lQuitDlg.setIcon(QMessageBox::Question);
    if(lQuitDlg.exec() == QMessageBox::Yes)
    {
        e->accept();
    }
    else
    {
        e->ignore();
    }
}


void CMainWindow::on_actionBe_arbeiten_triggered()
{    
    m_Roster = new CRosterWindow();
    m_Roster->setSubWnd(ui->mdiArea->addSubWindow(m_Roster));
    m_Roster->show();
}
