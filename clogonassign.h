#ifndef CLOGONASSIGN_H
#define CLOGONASSIGN_H

#include <QDialog>
#include <QList>
#include <QSqlQuery>
#include <QSqlRecord>
#include "cdatabasemanager.h"
#include "cpersonal.h"


namespace Ui {
class CLogonAssign;
}

class CLogonAssign : public QDialog
{
    Q_OBJECT

public:
    explicit CLogonAssign(QString pName, QWidget *parent = 0);
    ~CLogonAssign();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CLogonAssign *ui;
    QWidget* m_parent;
    CDatabaseManager* m_db;
    QList<CPersonal> *m_PersList;
    void setupPersCombo();
};

#endif // CLOGONASSIGN_H
