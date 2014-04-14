/****************************************************************************************
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 14.04.2014 by joerg
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

#ifndef CPREALERT_H
#define CPREALERT_H

#include <QString>
#include <QVariant>
#include <QDate>
#include <QSqlQuery>
#include <QList>

#include "cdatabasemanager.h"
#include "cpersonal.h"
#include "cdutytype.h"
#include "cprealerttype.h"


class CPrealert
{
public:
    CPrealert();
    CPrealert(int pPID, QDate pDate);
    CPrealert(int pID);

    CPersonal *Pers() const;
    void setPers(CPersonal *Pers);

    QList<CPrealertType> *paTypes() const;
    void setPaTypes(QList<CPrealertType> *paTypes);

    QDate Date() const;
    void setDate(const QDate &Date);

    int id() const;
    void setId(int id);

private:
    int m_id;
    CPersonal *m_Pers;
    QList<CPrealertType> *m_paTypes;
    QDate m_Date;
    QList<CPrealertType>* getTypes(int id);

};

#endif // CPREALERT_H
