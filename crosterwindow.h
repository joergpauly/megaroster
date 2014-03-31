/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 31.03.2014 by joerg
*   All Rights reserved
*
*   ChartButler ist Freie Software: Sie können es unter den Bedingungen
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

#ifndef CROSTERWINDOW_H
#define CROSTERWINDOW_H

#include <QWidget>

namespace Ui {
class CRosterWindow;
}

class CRosterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CRosterWindow(QWidget *parent = 0);
    explicit CRosterWindow(QWidget *parent, int pMonth, int pYear);
    ~CRosterWindow();

private:
    // Properties
    Ui::CRosterWindow *ui;
    int m_Month;
    int m_Year;
};

#endif // CROSTERWINDOW_H
