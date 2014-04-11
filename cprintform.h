/****************************************************************************************
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 11.04.2014 by joerg
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

#ifndef CPRINTFORM_H
#define CPRINTFORM_H

#include <QWidget>
#include <QTableWidget>
#include <QMdiSubWindow>

namespace Ui {
class CPrintForm;
}

class CPrintForm : public QWidget
{
    Q_OBJECT

public:
    explicit CPrintForm(QWidget *parent = 0);
    ~CPrintForm();
    void setGraph();
    void setTextTopLeft(QString pTxt);
    void setTextTipMid(QString pTxt);
    void setTextTopRight(QString pTxt);
    void setTextFooter(QString pTxt);
    void setTable(QTableWidget *table);
    void setSubWnd(QMdiSubWindow *pSubWnd);

private:
    Ui::CPrintForm *ui;
    QMdiSubWindow *m_SubWnd;
};

#endif // CPRINTFORM_H
