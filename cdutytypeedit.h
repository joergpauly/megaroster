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

#ifndef CDUTYTYPEEDIT_H
#define CDUTYTYPEEDIT_H

#include <QDialog>
#include <QMdiSubWindow>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QTableWidgetItem>
#include <QColorDialog>

#include "cdatabasemanager.h"

namespace Ui {
class CDutyTypeEdit;
}

class CDutyTypeEdit : public QDialog
{
    Q_OBJECT

public:
    explicit CDutyTypeEdit(QWidget *parent = 0);
    ~CDutyTypeEdit();
    void setSubWnd(QMdiSubWindow *pSubWnd);

private slots:
    void on_tblDutytps_cellClicked(int row, int column);

    void on_cmdColor_clicked();

    void on_cmdNew_clicked();

    void on_txtMark_editingFinished();

    void on_txtDescr_editingFinished();

    void on_timStart_editingFinished();

    void on_timEnd_editingFinished();

    void on_timBefore_editingFinished();

    void on_timAfter_editingFinished();

    void on_timStart2_editingFinished();

    void on_timEnd2_editingFinished();

    void setSelected(QWidget* pold, QWidget* pnew);

    void on_cmbBaseType_currentIndexChanged(int index);

private:
    // Member
    QObject *m_parent;
    Ui::CDutyTypeEdit *ui;
    QMdiSubWindow* m_SubWnd;
    QSqlQuery* m_qry;
    QColor m_clr;
    int m_ID;
    int m_lastInserted;

    // Funktionen
    void loadTable();
    void fillDTypeTable();
    void fillDBTcombo();
    void updateUI();
    void updateRecord(int pID);
    void getFromID(int pID);

};

#endif // CDUTYTYPEEDIT_H
