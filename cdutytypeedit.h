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

private:
    Ui::CDutyTypeEdit *ui;
    QMdiSubWindow* m_SubWnd;
    QSqlQuery* m_qry;

};

#endif // CDUTYTYPEEDIT_H
