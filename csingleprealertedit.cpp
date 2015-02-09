/****************************************************************************************
*
*   File: csingleprealertedit.cpp
*
*   This file is part of the MEGASeries Project.
*   Copyright (C) 2015 Joerg Pauly, MEGAMover.de
*   File created 06.02.2015 by joerg
*   All Rights reserved
*
*   Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
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

#include "csingleprealertedit.h"
#include "ui_csingleprealertedit.h"

CSinglePrealertEdit::CSinglePrealertEdit(CPersonal *pPers, QDate pDate, bool pExists, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSinglePrealertEdit)
{
    m_paTypes = new QList<CPrealertType>();
    ui->setupUi(this);
    m_actPers = pPers;
    this->setWindowTitle(QString("Vormerkung für %1, %2").arg(m_actPers->Name()).arg(m_actPers->VName()));
    m_DutyTypes= m_db->dutyTypeList();

    if(pExists)
    {
        ui->dteFrom->setDate(m_actAlert->Date());
        ui->dteTo->setDate(m_actAlert->Date());
        ui->dteTo->setReadOnly(true);
        m_newAlert = false;
    }
    else
    {
        m_newAlert = true;
        ui->dteFrom->setDate(pDate);
        ui->dteTo->setDate(pDate);
    }

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

CSinglePrealertEdit::CSinglePrealertEdit(CPrealert *pPreAlert, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSinglePrealertEdit)
{
    m_actAlert = pPreAlert;
    m_paTypes = m_actAlert->paTypes();
    ui->setupUi(this);
    m_actPers = pPreAlert->Pers();
    this->setWindowTitle(QString("Vormerkung für %1, %2").arg(m_actPers->Name()).arg(m_actPers->VName()));
    m_DutyTypes= m_db->dutyTypeList();

    ui->dteFrom->setDate(m_actAlert->Date());
    ui->dteTo->setDate(m_actAlert->Date());
    ui->dteTo->setReadOnly(true);
    updateTypes();
    m_newAlert = false;

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


CSinglePrealertEdit::~CSinglePrealertEdit()
{
    delete ui;
}

void CSinglePrealertEdit::on_dtMenu(QAction *pAction)
{
    CDutyType *dtyp = new CDutyType(pAction->data().toInt());
    CPrealertType ltype;
    ltype.setType(dtyp);

    if(m_actAlert)
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

void CSinglePrealertEdit::on_cmdNewDuty_clicked()
{
    on_dteTo_editingFinished();
    m_dtMenu->exec(QCursor::pos());
}

void CSinglePrealertEdit::updateTypes()
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
            litem->setData(0, Qt::UserRole, QVariant(m_paTypes->at(i).id()));
            ui->trvDutyTypes->addTopLevelItem(litem);
        }

    }
}

QList<CPrealert> *CSinglePrealertEdit::setupNewPrealerts()
{
    QList<CPrealert> *lPre = new QList<CPrealert>();

    for(QDate i = ui->dteFrom->date(); i <= ui->dteTo->date(); i = i.addDays(1))
    {
        CPrealert * lAlert = new CPrealert();
        lAlert->setDate(i);
        lAlert->setPers(m_actPers);        
        lPre->append(*lAlert);
    }

    return lPre;
}

void CSinglePrealertEdit::on_dteTo_editingFinished()
{
    if(ui->dteTo->date() < ui->dteFrom->date())
    {
        QMessageBox lBox;
        lBox.setWindowTitle("Fehler!");
        lBox.setText("Datum 'Bis' darf nicht vor Datum 'Von' liegen!");
        lBox.setStandardButtons(QMessageBox::Ok);
        lBox.exec();
        ui->dteTo->setDate(ui->dteFrom->date());
        ui->dteTo->setFocus();
        return;
    }

    if(ui->dteFrom->date() == ui->dteTo->date())
    {
        CPrealert * lAlert = new CPrealert();
        lAlert->setDate(ui->dteFrom->date());
        lAlert->setPers(m_actPers);
        m_Prealerts = new QList<CPrealert>();
        m_Prealerts->append(*lAlert);
        m_actAlert = lAlert;
        ui->cmdNewDuty->setFocus();
    }

    if(ui->dteFrom->date() < ui->dteTo->date())
    {
        m_Prealerts = setupNewPrealerts();
    }
}

void CSinglePrealertEdit::on_buttonBox_rejected()
{
    this->close();
}

void CSinglePrealertEdit::on_buttonBox_accepted()
{
    if(m_newAlert)
    {
        for(int j = 0; j < m_Prealerts->count(); j++)
        {
            QSqlQuery lqry;
            lqry.prepare("INSERT INTO tblPrealert (DDate, PersID) VALUES (:Date, :PID);");
            lqry.bindValue(":Date", m_Prealerts->at(j).Date().toString("yyyy-MM-dd"));
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
    }
    else
    {

    }
    close();
}

void CSinglePrealertEdit::on_cmdDelete_clicked()
{
    if(ui->trvDutyTypes->currentItem())
    {
        int pid = ui->trvDutyTypes->currentItem()->data(0, Qt::UserRole).toInt();
        QSqlQuery lqry;
        lqry.prepare("DELETE FROM tblPATypes WHERE ID = :ID;");
        lqry.bindValue(":ID", pid);
        lqry.exec();
    }
    updateTypes();
}
