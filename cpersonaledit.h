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

#ifndef CPERSONALEDIT_H
#define CPERSONALEDIT_H

#include <QDialog>
#include <QMdiSubWindow>
#include <QMessageBox>
#include "cdatabasemanager.h"

namespace Ui {
class CPersonalEdit;
}

class CPersonalEdit : public QDialog
{
    Q_OBJECT

public:
    explicit CPersonalEdit(QWidget *parent = 0);
    ~CPersonalEdit();
    void setSubWnd(QMdiSubWindow* pSubWnd);

private slots:
    void on_tblPersonal_cellClicked(int row, int column);

    void on_cmdNew_clicked();

    void on_txtName_editingFinished();

    void on_txtVName_editingFinished();

    void on_datGebDat_editingFinished();

    void on_txtPersNo_editingFinished();

    void on_timSollTag_editingFinished();

    void on_cmdSave_clicked();

    void on_cmdKill_clicked();

    void on_datEintritt_editingFinished();

    void on_datAustritt_editingFinished();

    void setSelected(QWidget* pold, QWidget* pnew);

    void on_chkEdit_clicked();

    void on_chkAdmin_clicked();

private:
    // Member
    Ui::CPersonalEdit *ui;
    QObject* m_parent;
    CPersonal *m_actUsr;
    QMdiSubWindow *m_SubWnd;
    QSqlQuery* m_qry;
    int m_id;
    int m_lastInserted;

    // Funktionen
    void loadTable();
    void fillPersTable();
    void updateUI();
    void getFromID(int pID);
    void updateRecord(int pID);

};

#endif // CPERSONALEDIT_H
