/********************************************************************
*
*   File: ccommentedit.cpp    Class: CCommentEdit
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
#include "ccommentedit.h"
#include "ui_ccommentedit.h"

CCommentEdit::CCommentEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCommentEdit)
{
    ui->setupUi(this);
    m_comment = new CComment(parent);
}

CCommentEdit::~CCommentEdit()
{
    delete ui;
}

void CCommentEdit::on_buttonBox_accepted()
{
    m_comment->setCommentText(ui->txtComment->text());
    m_comment->saveToDB();
    this->close();
}

void CCommentEdit::on_buttonBox_rejected()
{
    this->close();
}
