#include "clogonassign.h"
#include "ui_clogonassign.h"
#include "cmainwindow.h"

CLogonAssign::CLogonAssign(QString pName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CLogonAssign)
{
    m_parent = parent;
    ui->setupUi(this);
    ui->lblName->setText(pName);
    setupPersCombo();
}

CLogonAssign::~CLogonAssign()
{
    delete ui;
}

void CLogonAssign::setupPersCombo()
{
    m_db = ((CMainWindow*)m_parent)->dataBase();
    m_PersList = m_db->personalList(QDate::currentDate(),QDate::currentDate());

    for(int i = 0; i < m_PersList->count(); i++)
    {
        QString lFullName = m_PersList->at(i).Name() + ", " + m_PersList->at(i).VName();
        ui->cmbUsers->addItem(lFullName, QVariant(m_PersList->at(i).id()));
    }

}

void CLogonAssign::on_buttonBox_accepted()
{
    QSqlQuery lqry;
    lqry.prepare("INSERT INTO tblLogon (PID, LogonName) VALUES (:PID, :LNAME);");
    lqry.bindValue(":PID", ui->cmbUsers->currentData().toInt());
    lqry.bindValue(":LNAME", ui->lblName->text());
    lqry.exec();
    ((CMainWindow*)m_parent)->setUserID(ui->cmbUsers->currentData().toInt());
    close();
}
