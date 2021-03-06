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

#include "cmainwindow.h"
#include "ui_cmainwindow.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    QSettings *set = new QSettings("MEGA-Serie", "MEGARoster");
    ui->setupUi(this);
    m_Path = new QDir(set->value("FILEDIR", QVariant(".")).toString());

    m_dbman = new CDatabaseManager(this);    
    m_Username = qgetenv("USER");

    if(m_Username.isEmpty())
    {
        m_Username = qgetenv("USERNAME");
    }

    checkLogon();
    QLabel *txtUser = new QLabel();
    txtUser->setText("Anwender: " + CPersonal(m_actualUser).Name() + ", " + CPersonal(m_actualUser).VName());
    ui->statusBar->addPermanentWidget(txtUser);
    delete set;
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

CDatabaseManager *CMainWindow::dataBase()
{
    return m_dbman;
}

void CMainWindow::setStatusText(QString pText)
{
    ui->statusBar->showMessage(pText);
}

void CMainWindow::setUserID(int pID)
{
    m_actualUser = pID;
}

int CMainWindow::getUserID()
{
    return m_actualUser;
}

QDir *CMainWindow::path()
{
    return m_Path;
}

void CMainWindow::openMonth(int pMonth, int pYear, bool pLeft, CRosterWindow *pCalling)
{
    m_Roster = new CRosterWindow(this, pMonth, pYear);
    m_Roster->setSubWnd(ui->mdiArea->addSubWindow(m_Roster));

    if(pLeft)
    {
        ui->mdiArea->setTabOrder(m_Roster, pCalling);
    }

    m_Roster->show();
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

void CMainWindow::openEditableRoster()
{
    // Alte Version
    /*m_Roster = new CRosterWindow(this);
    m_Roster->setSubWnd(ui->mdiArea->addSubWindow(m_Roster));
    m_Roster->show();*/
    // Neue Version
    m_RosterEdit = new CRosterEdit(this);
    m_RosterEdit->setSubWnd(ui->mdiArea->addSubWindow(m_RosterEdit));
    m_RosterEdit->show();
}

void CMainWindow::openPersonalEdit()
{
    m_PersEdit = new CPersonalEdit(this);
    m_PersEdit->setSubWnd(ui->mdiArea->addSubWindow(m_PersEdit));
    m_PersEdit->show();
}

void CMainWindow::openDutyTypeEdit()
{
    m_DTEdit = new CDutyTypeEdit(this);
    m_DTEdit->setSubWnd(ui->mdiArea->addSubWindow(m_DTEdit));
    m_DTEdit->show();
}

void CMainWindow::openBranchEdit()
{
    m_BranchEdit = new CBranchEdit(this);
    m_BranchEdit->setSubWnd(ui->mdiArea->addSubWindow(m_BranchEdit));
    m_BranchEdit->show();
}

void CMainWindow::openHolidayEdit()
{
    m_HolidayEdit = new CHolidayEdit(this);
    m_HolidayEdit->setSubWnd(ui->mdiArea->addSubWindow(m_HolidayEdit));
    m_HolidayEdit->show();
}

void CMainWindow::checkLogon()
{
    QSqlQuery lqry;
    lqry.prepare("SELECT * FROM tblLogon WHERE LogonName = :NAME;");
    lqry.bindValue(":NAME", m_Username);
    lqry.exec();
    lqry.first();

    if(lqry.isValid())
    {
        m_actualUser = lqry.value(lqry.record().indexOf("PID")).toInt();
    }
    else
    {
        CLogonAssign ldlg(m_Username, this);
        ldlg.exec();
    }

}


void CMainWindow::on_actionBe_arbeiten_triggered()
{    
    openEditableRoster();
}

void CMainWindow::on_cmdEditRoster_clicked()
{
    openEditableRoster();
}

void CMainWindow::on_action_Personal_triggered()
{
    openPersonalEdit();
}

void CMainWindow::on_action_Dienst_Arten_triggered()
{
    openDutyTypeEdit();
}

void CMainWindow::on_cmdPersEdit_clicked()
{
    openPersonalEdit();
}

void CMainWindow::on_cmdDType_clicked()
{
    openDutyTypeEdit();
}

void CMainWindow::on_actionDruckvorlage_bearbeiten_triggered()
{    
}

void CMainWindow::on_cmdPreAlerts_clicked()
{
    CPrealertEdit *pAlert = new CPrealertEdit(this);
    pAlert->setSubWnd(ui->mdiArea->addSubWindow(pAlert));
    pAlert->show();
}

void CMainWindow::on_actionDaten_Ordner_festlegen_triggered()
{
    QFileDialog dlg;
    QSettings *set = new QSettings("MEGA-Serie", "MEGARoster");

    QDir dir;
    dir.setPath(set->value("FILEDIR", QVariant(".")).toString());
    dlg.setFileMode(QFileDialog::DirectoryOnly);
    dlg.setDirectory(dir);
    dlg.setWindowTitle("Daten-Ordner festlegen");

    if(dlg.exec() == QDialog::Accepted)
    {
        dir = dlg.directory();
        set->setValue("FILEDIR", (QVariant)dir.path());
    }

    delete set;
}

void CMainWindow::on_cmdChangeLog_clicked()
{
    CLogbookView *pLogView = new CLogbookView(this);
    pLogView->setSubWnd(ui->mdiArea->addSubWindow(pLogView));
    pLogView->show();
}

void CMainWindow::on_actionDienst_stellen_bearbeiten_triggered()
{
    openBranchEdit();
}

void CMainWindow::on_cmdBranches_clicked()
{
    openBranchEdit();
}

void CMainWindow::on_cmdHolidayEdit_clicked()
{
    openHolidayEdit();
}

void CMainWindow::on_action_Feiertagsliste_bearbeiten_triggered()
{
    openHolidayEdit();
}
