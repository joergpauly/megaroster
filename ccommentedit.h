/********************************************************************
*
*   File: ccommentedit.h    Class: CCommentEdit
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2016 Joerg Pauly
*   Created 07.01.2016 by joerg
*   All Rights reserved
*
*   Alle Programme der MEGA-Serie sind Freie Software:
*   Sie können sie unter den Bedingungen
*   der GNU Lesser General Public License, wie von der
*   Free Software Foundation, Version 3 der Lizenz oder
*   (nach Ihrer Option) jeder späteren veröffentlichten
*   Version, weiterverbreiten und/oder modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es nützlich
*   sein wird, aber OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt;
*   sogar ohne die implizite Gewährleistung der MARKTFÄHIGKEIT
*   oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU Lesser General Public License für weitere Details.
*
*   Sie sollten eine Kopie der GNU Lesser General Public License
*   zusammen mit diesem Programm erhalten haben.
*   Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*
********************************************************************/
#ifndef CCOMMENTEDIT_H
#define CCOMMENTEDIT_H

// System-Header
#include <QDialog>

// Projekt-Header
#include "ccomment.h"

namespace Ui {
class CCommentEdit;
}

class CCommentEdit : public QDialog
{
    Q_OBJECT

public:
    explicit CCommentEdit(QWidget *parent = 0);
    ~CCommentEdit();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CCommentEdit *ui;
    CComment* m_comment;
};

#endif // CCOMMENTEDIT_H
