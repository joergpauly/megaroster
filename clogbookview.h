/****************************************************************************************
*
*   This file is part of the MEGASeries Project.
*   Copyright (C) 2014 joerg
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

#ifndef CLOGBOOKVIEW_H
#define CLOGBOOKVIEW_H

#include <QMdiSubWindow>
#include <QWidget>

#include "cdatabasemanager.h"
#include "cpersonal.h"
#include "cduty.h"
#include "cdutytype.h"


namespace Ui {
class CLogbookView;
}

class CLogbookView : public QWidget
{
    Q_OBJECT

public:
    explicit CLogbookView(QWidget *parent = 0);
    ~CLogbookView();
    void setSubWnd(QMdiSubWindow* pSubWnd);

private slots:
    void on_datFrom_editingFinished();
    void on_datTo_editingFinished();

private:
    Ui::CLogbookView *ui;
    void loadLog();
    QMdiSubWindow* m_SubWnd;
};

#endif // CLOGBOOKVIEW_H
