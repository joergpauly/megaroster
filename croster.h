/****************************************************************************************
*
*   This file is part of the MEGASeries Project.
*   Copyright (C) 2014 joerg
*   All Rights reserved
*
*   Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
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

#ifndef CROSTER_H
#define CROSTER_H

// System-Header
#include <QList>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>

// Projekt-Header
#include "cduty.h"
#include "cdutytype.h"
#include "cpersonal.h"
#include "crosterrow.h"

class CRoster
{
public:
    CRoster();
    CRoster(QList<CPersonal> pCurrentOfficers, QDate* pDate);
    ~CRoster();


    CDuty* singleDuty(int pPerID, QDate pDate);
    QList<CRosterRow*>roster();

private:    
    QList<QList<CDuty>> m_DutyRows;
    QList<CRosterRow*>  m_RosterRows;
    CRosterRow* dutyRow(int pPerID, QDate *pDate);

};

#endif // CROSTER_H
