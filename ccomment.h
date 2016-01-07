/********************************************************************
*
*   File: ccomment.h    Class: CComment
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
#ifndef CCOMMENT_H
#define CCOMMENT_H

// System-Header
#include <QWidget>
#include <QDateTime>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>

// Projekt-Header
#include "cpersonal.h"

class CComment
{
private:
    QObject*    m_parent;
    int         m_ID;
    CPersonal*  m_Pers;
    QDateTime*  m_Timestamp;
    QString*    m_CommentText;

public:
    CComment(QObject* parent);
    ~CComment();

    // Getter-/Setter-Funktionen
    int ID() const;
    void setID(int ID);
    CPersonal *Pers() const;
    void setPers(CPersonal *Pers);
    QDateTime *Timestamp() const;
    void setTimestamp(QDateTime *Timestamp);
    QString *CommentText() const;
    void setCommentText(QString CommentText);

    // Public Calls
    void saveToDB();
    CComment();
};

#endif // CCOMMENT_H