/********************************************************************
*
*   File: ccurrentofficers.cpp    Class: CCurrentOfficers
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2016 Joerg Pauly
*   Created 21.11.2016 by joerg
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
/********************************************************************
 *
 * Liste aller im Dienst befindlichen Kollegen
 *
 * *****************************************************************/

#include "ccurrentofficers.h"

CCurrentOfficers::CCurrentOfficers()
{

}

CCurrentOfficers::CCurrentOfficers(QDate pFrom, QDate pTo)
{
    m_dateFrom = pFrom;
    m_dateTo = pTo;
}

QDate CCurrentOfficers::dateFrom() const
{
    return m_dateFrom;
}

void CCurrentOfficers::setDateFrom(const QDate &dateFrom)
{
    m_dateFrom = dateFrom;
}

QDate CCurrentOfficers::dateTo() const
{
    return m_dateTo;
}

void CCurrentOfficers::setDateTo(const QDate &dateTo)
{
    m_dateTo = dateTo;
}
