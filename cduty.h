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

#ifndef CDUTY_H
#define CDUTY_H

#include <QDate>
#include <QString>
#include <QTime>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

#include "cpersonal.h"
#include "cdutytype.h"

class CDuty
{
public:
    CDuty();    
    CDuty(int pid);
    ~CDuty();

    QDate Date() const;
    void setDate(const QDate &Date);

    CPersonal *Kollege() const;
    void setKollege(const CPersonal &Kollege);

    CDutyType *Typ() const;
    void setTyp(const CDutyType &Typ);

    int id() const;
    void setId(int id);

    QTime TimeFrom() const;
    void setTimeFrom(const QTime &TimeFrom);

    QTime TimeTo() const;
    void setTimeTo(const QTime &TimeTo);

    QTime TimeFrom2() const;
    void setTimeFrom2(const QTime &TimeFrom2);

    QTime TimeTo2() const;
    void setTimeTo2(const QTime &TimeTo2);

    QTime Duration() const;
    void setDuration(const QTime &Duration);

    QTime Duration2() const;
    void setDuration2(const QTime &Duration2);

    bool Request() const;
    void setRequest(bool Request);

private:
    int         m_id;
    QDate       m_Date;
    CPersonal   *m_Kollege;
    CDutyType   *m_Typ;
    bool        m_Request;
    QTime       m_TimeFrom;
    QTime       m_TimeTo;
    QTime       m_Duration;
    QTime       m_TimeFrom2;
    QTime       m_TimeTo2;
    QTime       m_Duration2;
};

#endif // CDUTY_H
