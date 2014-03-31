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

#ifndef CDUTY_H
#define CDUTY_H

#include <QDate>
#include <QString>
#include <QTime>

#include "cpersonal.h"
#include "cdutytype.h"

class CDuty
{
public:
    CDuty();
    CDuty(QDate pDate, CPersonal pKollege, CDutyType pTyp);

    QDate Date() const;
    void setDate(const QDate &Date);

    CPersonal Kollege() const;
    void setKollege(const CPersonal &Kollege);

    CDutyType Typ() const;
    void setTyp(const CDutyType &Typ);

private:
    QDate       m_Date;
    CPersonal   m_Kollege;
    CDutyType   m_Typ;

};

#endif // CDUTY_H