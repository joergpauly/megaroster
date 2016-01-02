/****************************************************************************************
*
*   File: cbranchedit.h
*
*   This file is part of the MEGASeries Project.
*   Copyright (C) 2015 Joerg Pauly, MEGAMover.de
*   File created 27.02.2015 by joerg
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

#ifndef CBRANCHEDIT_H
#define CBRANCHEDIT_H

// System-Header
#include <QDialog>
#include <QMdiSubWindow>
#include <QMessageBox>

// Projekt-Header
#include "cbranch.h"

namespace Ui
{
    class CBranchEdit;
}

class CBranchEdit : public QDialog
{
    Q_OBJECT

public:
    explicit CBranchEdit(QWidget *parent = 0);
    ~CBranchEdit();

    void setSubWnd(QMdiSubWindow* pSubWnd);

private slots:
    void on_txtName1_editingFinished();
    void on_txtName2_editingFinished();
    void on_txtName3_editingFinished();
    void on_txtAdress1_editingFinished();
    void on_txtAdress2_editingFinished();
    void on_txtAdress3_editingFinished();
    void on_txtAdress4_editingFinished();
    void on_txtAdress5_editingFinished();
    void on_txtHours_editingFinished();
    void on_cmdNew_clicked();
    void on_cmdDelete_clicked();
    void on_cmdClose_clicked();
    void on_tbvBranches_cellClicked(int row, int column);

private:
    // Member
    Ui::CBranchEdit *ui;
    QMdiSubWindow* m_subWnd;
    CBranch *m_actBranch;

    // Funktionen
    void saveToDB();
    void setupUiFields();
    void setupBranchList();
};

#endif // CBRANCHEDIT_H
