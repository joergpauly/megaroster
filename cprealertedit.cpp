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

#include "cprealertedit.h"
#include "ui_cprealertedit.h"
#include "cmainwindow.h"

CPrealertEdit::CPrealertEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CPrealertEdit)
{
    ui->setupUi(this);
    m_parent = parent;
    m_db = ((CMainWindow*)m_parent)->dataBase();
    m_DutyTypes = m_db->dutyTypeList();
    m_PersList = m_db->personalList(QDate::currentDate(),QDate::currentDate());
    for(int i = 0; i < m_PersList->count(); i++)
    {
        QString lFullName = m_PersList->at(i).Name() + ", " + m_PersList->at(i).VName();
        ui->cmbPersonal->addItem(lFullName, QVariant(m_PersList->at(i).id()));
    }
    ui->datFromDate->setDate(QDate::currentDate());
    ui->datBisDate->setDate(QDate::currentDate());
    m_dtMenu = new QMenu("Dienstart auswählen", ui->trvDutyTypes);
    QList<QAction*> *lActions = new QList<QAction*>();
    for(int dt = 0; dt < m_DutyTypes->count(); dt++)
    {
        QAction *lact = new QAction(m_DutyTypes->at(dt).Desc(), m_dtMenu);
        lact->setData(QVariant(m_DutyTypes->at(dt).id()));
        lActions->append(lact);
    }
    m_dtMenu->addActions(*lActions);
    connect(m_dtMenu, SIGNAL(triggered(QAction*)),SLOT(on_dtMenu(QAction*)));
}

CPrealertEdit::~CPrealertEdit()
{
    delete ui;
}

void CPrealertEdit::setSubWnd(QMdiSubWindow *pSubWnd)
{
    m_subWnd = pSubWnd;
}

void CPrealertEdit::on_cmbPersonal_currentIndexChanged(int index)
{
    m_actPers = new CPersonal(ui->cmbPersonal->currentData().toInt());
}

void CPrealertEdit::on_dtMenu(QAction *pAction)
{
    int lDtID = pAction->data().toInt();
}

void CPrealertEdit::on_trvDutyTypes_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if(current)
    {
        QAction* lsep = m_dtMenu->addSeparator();
        QAction *lAction = new QAction("Löschen", m_dtMenu);
        m_dtMenu->insertAction(lsep,lAction);
    }
    m_dtMenu->exec();
}


void CPrealertEdit::on_trvDutyTypes_itemClicked(QTreeWidgetItem *item, int column)
{
    m_dtMenu->exec();
}

void CPrealertEdit::on_cmdNewDuty_clicked()
{
    m_dtMenu->exec(QCursor::pos());
}
