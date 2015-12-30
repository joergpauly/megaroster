/****************************************************************************************
*
*   File: cholidayedit.h    Class: CHolidayEdit
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 30.12.2015 by joerg
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
#ifndef CHOLIDAYEDIT_H
#define CHOLIDAYEDIT_H

#include <QDialog>

namespace Ui {
class CHolidayEdit;
}

class CHolidayEdit : public QDialog
{
    Q_OBJECT

public:
    explicit CHolidayEdit(QWidget *parent = 0);
    ~CHolidayEdit();

private:
    Ui::CHolidayEdit *ui;
};

#endif // CHOLIDAYEDIT_H
