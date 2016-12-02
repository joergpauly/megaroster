/****************************************************************************************
*
*   This file is part of the MEGASeries Project.
*   Copyright (C) 2016 Joerg Pauly
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

#include "croster.h"

CRoster::CRoster()
{

}

CRoster::CRoster(QList<CPersonal> pCurrentOfficers, QDate *pDate)
{    
    // Je Satz in pCurrentOfficers mit Datum aufsteigend Index bilden,
    // Duty-Satz aus DB holen oder erzeugen; je pCurOff in m_PersDuties,
    // anschließend m_PersDuties an m_DutyRows anhängen.

    for(int i = 0; i < pCurrentOfficers.count(); i++)
    {
        QList<CDuty> lDutyRow;
        lDutyRow = dutyRow(pCurrentOfficers.at(i).id(), pDate);
        m_DutyRows.append(lDutyRow);
    }
}

CRoster::~CRoster()
{
    // Bislang nix zu tun...
}

QList<CDuty> CRoster::dutyRow(int pPerID, QDate *pDate)
{
    CRosterRow *lRow = new CRosterRow(pPerID, *pDate);
    return lRow->duties();
}

CDuty *CRoster::singleDuty(int pPerID, QDate pDate)
{
    return new CDuty(pPerID, pDate);
}

QList<QList<CDuty>> CRoster::roster()
{
    return m_DutyRows;
}

