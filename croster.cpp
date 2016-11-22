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
    //TODO: Duties per PerID und Datum aufsteigend für den Monat aus DB holen und in Liste anhängen.
    QList<CDuty> lList;
    QSqlQuery lqry;
    QDate lFrom, lTo;
    // Monatsanfang und Ende bestimmen
    lFrom.setDate(pDate->year(), pDate->month(), 1);
    lTo.setDate(pDate->year(), pDate->month(), pDate->daysInMonth());
    // Abfrage aufbauen
    lqry.prepare("SELECT ID FROM tblDuty WHERE PersID = :PID AND DDate >= :FDT AND DDate <= :TDT ORDER BY DDate;");
    lqry.bindValue(":PID", pPerID);
    lqry.bindValue(":FDT", lFrom.toString("yyyy-MM-dd"));
    lqry.bindValue(":TDT", lTo.toString("yyyy-MM-dd"));
    // Ausführen und auf erstes Element setzen
    lqry.exec();
    QString err = lqry.lastError().text();
    lqry.first();

    // Solange Daten gültig sind, Dienst-Daten in Objekte laden und an Liste anhängen
    while (lqry.isValid())
    {
        CDuty lDty(lqry.value(lqry.record().indexOf("ID")).toInt());
        lList.append(lDty);
        lqry.next();
    }

    // Liste zurückgeben
    return lList;
}

CDuty *CRoster::singleDuty(int pPerID, QDate pDate)
{        
}

QList<QList<CDuty>> CRoster::roster()
{
    return m_DutyRows;
}

