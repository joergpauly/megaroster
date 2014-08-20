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

#ifndef CDATABASEMANAGER_H
#define CDATABASEMANAGER_H

// System-Header
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QList>

// Projekt-Header
#include "cpersonal.h"
#include "cdutytype.h"
#include "cduty.h"

class CDatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit CDatabaseManager(QObject *parent = 0);

private:
    QObject* m_parent;
    QSqlDatabase m_db;

signals:

public slots:

public:
    QList<CPersonal>    *personalList(QDate fromDate, QDate toDate);
    QList<CDutyType>    *dutyTypeList();
    QList<CDuty>        *dutyList(QDate fromDate, QDate toDate, int PerID = 0);
    QList<CDtyBaseType> *dbaseList();


};

class CLogManager : public QObject
{
    Q_OBJECT

    struct sctLogEntry
    {
        QDateTime       timeStamp;
        CPersonal       user;
        CPersonal       personal;
        CDuty           oldDuty;
        CDuty           newDuty;
    };
public:
    explicit CLogManager(QObject *parent = 0);
    CLogManager(sctLogEntry pEntry, QObject *parent = 0);
    void writeEntry(sctLogEntry pEntry);

};



#endif // CDATABASEMANAGER_H
