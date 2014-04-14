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
    m_alerts = new QList<CPrealert>();
    m_paTypes = new QList<CPrealertType>();
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
    m_alerts = new QList<CPrealert>();
    QSqlQuery lqry;
    lqry.prepare("SELECT * FROM tblPrealert WHERE PersID = :PID ORDER BY DDate;");
    lqry.bindValue(":PID", m_actPers->id());
    lqry.exec();
    lqry.first();
    QString err = lqry.lastError().text();
    while(lqry.isValid())
    {
        CPrealert *lAlert = new CPrealert();
        lAlert->setDate(QDate::fromString(lqry.value(lqry.record().indexOf("DDate")).toString(),"yyyy-MM-dd"));
        lAlert->setId(lqry.value(lqry.record().indexOf("ID")).toInt());
        lAlert->setPers(m_actPers);
        m_alerts->append(*lAlert);
        lqry.next();
        delete lAlert;
    }
    updateAlerts();
}

void CPrealertEdit::on_dtMenu(QAction *pAction)
{
    CDutyType *dtyp = new CDutyType(pAction->data().toInt());
    CPrealertType ltype;
    ltype.setType(dtyp);
    if(m_actAlert->id())
    {
        int pID = m_actAlert->id();
        ltype.setPid(pID);
        QSqlQuery lqry;
        lqry.prepare("INSERT INTO tblPATypes (PAID, TypeID) VALUES (:PID, :TID);");
        lqry.bindValue(":PID", m_actAlert->id());
        lqry.bindValue(":TID", dtyp->id());
        lqry.exec();
    }
    m_paTypes->append(ltype);
    updateTypes();
}

void CPrealertEdit::on_trvDutyTypes_itemClicked(QTreeWidgetItem *item, int column)
{

}

void CPrealertEdit::on_cmdNewDuty_clicked()
{
    m_dtMenu->exec(QCursor::pos());
}

void CPrealertEdit::on_cmdNew_clicked()
{
    QSqlQuery lqry;
    lqry.prepare("INSERT INTO tblPrealert (DDate, PersID) VALUES (:Date, :PID);");
    lqry.bindValue(":Date", ui->datFromDate->date().toString("yyyy-MM-dd"));
    lqry.bindValue(":PID", m_actPers->id());
    lqry.exec();
    int ppid = lqry.lastInsertId().toInt();
    for(int i = 0; i < m_paTypes->count(); i++)
    {
        QSqlQuery ltqry;
        ltqry.prepare("INSERT INTO tblPATypes (PAID, TypeID) VALUES (:PAID, :TID);");
        ltqry.bindValue(":PAID", ppid);
        ltqry.bindValue(":TID", m_paTypes->at(i).type()->id());
        ltqry.exec();
    }
}

void CPrealertEdit::updateTypes()
{
    if(m_paTypes)
    {
        ui->trvDutyTypes->clear();
        for(int i = 0; i < m_paTypes->count(); i++)
        {
            QTreeWidgetItem* litem = new QTreeWidgetItem();
            litem->setText(0, m_paTypes->at(i).type()->Desc());
            QColor lclr(m_paTypes->at(i).type()->RosterColorR(),m_paTypes->at(i).type()->RosterColorG(),m_paTypes->at(i).type()->RosterColorB());
            litem->setBackground(0,QBrush(lclr));
            ui->trvDutyTypes->addTopLevelItem(litem);
        }
    }


}

void CPrealertEdit::updateAlerts()
{
    if(m_alerts)
    {
        for(int i = 0; i < m_alerts->count(); i++)
        {
            QTreeWidgetItem *litem = new QTreeWidgetItem();
            litem->setText(0,m_alerts->at(i).Date().toString("dd.MM.yyyy"));
            litem->setData(0,Qt::UserRole,m_alerts->at(i).id());
            ui->trvPrealerts->addTopLevelItem(litem);
        }
    }
}

void CPrealertEdit::on_trvPrealerts_itemClicked(QTreeWidgetItem *item, int column)
{
    m_actAlert = new CPrealert(item->data(0,Qt::UserRole).toInt());
    m_paTypes = m_actAlert->paTypes();
    updateTypes();
}
