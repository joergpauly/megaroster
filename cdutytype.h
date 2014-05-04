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

#ifndef CDUTYTYPE_H
#define CDUTYTYPE_H

#include <QString>
#include <QTime>
#include <QColor>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class CDutyType
{
public:
    CDutyType();
    CDutyType(QString pMark);
    CDutyType(int pID);

    QString Mark() const;
    void setMark(const QString &Mark);

    QString Desc() const;
    void setDesc(const QString &Desc);

    QTime TimeFrom() const;
    void setTimeFrom(const QTime &TimeFrom);

    QTime TimeTo() const;
    void setTimeTo(const QTime &TimeTo);

    QTime TimeElapsed() const;
    void setTimeElapsed(const QTime &TimeElapsed);

    QTime MinOffBefore() const;
    void setMinOffBefore(const QTime &MinOffBefore);

    QTime MinOffAfter() const;
    void setMinOffAfter(const QTime &MinOffAfter);

    QTime TimeFrom2() const;
    void setTimeFrom2(const QTime &TimeFrom2);

    QTime TimeTo2() const;
    void setTimeTo2(const QTime &TimeTo2);

    QTime TimeElapsed2() const;
    void setTimeElapsed2(const QTime &TimeElapsed2);

    int RosterColorR() const;
    void setRosterColorR(int RosterColorR);

    int RosterColorG() const;
    void setRosterColorG(int RosterColorG);

    int RosterColorB() const;
    void setRosterColorB(int RosterColorB);

    int id() const;
    void setId(int id);

    bool Checked() const;
    void setChecked(bool Checked);

private:
    int     m_id;
    QString m_Mark;
    QString m_Desc;
    QTime   m_TimeFrom;
    QTime   m_TimeFrom2;
    QTime   m_TimeTo;
    QTime   m_TimeTo2;
    QTime   m_TimeElapsed;
    QTime   m_TimeElapsed2;
    QTime   m_MinOffBefore;
    QTime   m_MinOffAfter;
    int     m_RosterColorR;
    int     m_RosterColorG;
    int     m_RosterColorB;
    bool    m_Checked;

    void readDB(QSqlQuery* pqry);
};

#endif // CDUTYTYPE_H
