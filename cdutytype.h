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

#ifndef CDUTYTYPE_H
#define CDUTYTYPE_H

#include <QString>
#include <QTime>
#include <QColor>

class CDutyType
{
public:
    CDutyType();
    CDutyType(QString pMark,
                QString pDesc,
                QTime   pTimeFrom,
                QTime   pTimeTo,
                QTime   pTimeElapsed,
                QTime   pMinOffBefore,
                QTime   pMinOffAfter,
                QColor  pRosterColor);

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

    QColor RosterColor() const;
    void setRosterColor(const QColor &RosterColor);

private:
    QString m_Mark;
    QString m_Desc;
    QTime   m_TimeFrom;
    QTime   m_TimeTo;
    QTime   m_TimeElapsed;
    QTime   m_MinOffBefore;
    QTime   m_MinOffAfter;
    QColor  m_RosterColor;
};

#endif // CDUTYTYPE_H
