/****************************************************************************************
*
*   File: csingleprealertedit.h
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

#ifndef CSINGLEPREALERTEDIT_H
#define CSINGLEPREALERTEDIT_H

// Qt-Header
#include <QDialog>
#include <QMenu>
#include <QMessageBox>

// Projekt-Header
#include "cprealert.h"


namespace Ui {
class CSinglePrealertEdit;
}

class CSinglePrealertEdit : public QDialog
{
    Q_OBJECT

public:
    explicit CSinglePrealertEdit(CPersonal *pPers, QDate pDate = QDate::currentDate(), bool pExists = false, QWidget *parent = 0);
    explicit CSinglePrealertEdit(CPrealert *pPreAlert, QWidget *parent = 0);
    ~CSinglePrealertEdit();

private slots:
    void on_dtMenu(QAction*pAction);

    void on_cmdNewDuty_clicked();

    void on_dteTo_editingFinished();

private:
    Ui::CSinglePrealertEdit *ui;
    CDatabaseManager *m_db;
    QMenu *m_dtMenu;
    QList<CPrealert> *m_Prealerts;
    QList<CPrealertType> *m_paTypes;
    QList<CDutyType> *m_DutyTypes;
    QList<CPersonal> *m_PersList;
    CPersonal *m_actPers;
    CPrealert* m_actAlert;
    bool m_newAlert;


    void updateTypes();
    QList<CPrealert> *setupNewPrealerts();
};

#endif // CSINGLEPREALERTEDIT_H
