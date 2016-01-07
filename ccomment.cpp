/********************************************************************
*
*   File: ccomment.cpp    Class: CComment
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
#include "ccomment.h"
#include "cmainwindow.h"

// Con-/Destructor
CComment::CComment(QObject *parent)
{
    m_parent = parent;
    m_CommentText = new QString();
    m_Timestamp = new QDateTime(QDateTime::currentDateTime());
    m_Pers = new CPersonal(((CMainWindow*)m_parent)->getUserID());
}

CComment::~CComment()
{
    delete m_Pers;
    delete m_CommentText;
    delete m_Timestamp;
}

// Getter-/Setter-Funktionen
int CComment::ID() const
{
    return m_ID;
}

void CComment::setID(int ID)
{
    m_ID = ID;
}

CPersonal *CComment::Pers() const
{
    return m_Pers;
}

void CComment::setPers(CPersonal *Pers)
{
    m_Pers = Pers;
}

QDateTime *CComment::Timestamp() const
{
    return m_Timestamp;
}

void CComment::setTimestamp(QDateTime *Timestamp)
{
    m_Timestamp = Timestamp;
}

QString *CComment::CommentText() const
{
    return m_CommentText;
}

void CComment::setCommentText(QString CommentText)
{
    m_CommentText = &CommentText;
}

void CComment::saveToDB()
{
    QString lstr(*m_CommentText);
    QSqlQuery lqry;
    lqry.prepare("INSERT INTO tblComment (PID, TimeStamp, Comment) VALUES (:PID, :TSTP, :COMM);");
    lqry.bindValue(":PID", m_Pers->id());
    lqry.bindValue(":TSTP", m_Timestamp->toString("yyyy-MM-dd hh:mm:ss.zzz"));
    lqry.bindValue(":COMM", lstr);
    lqry.exec();
}

