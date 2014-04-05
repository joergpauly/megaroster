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

#include "cdatabasemanager.h"
#include "cmainwindow.h"
#include <QGuiApplication>

CDatabaseManager::CDatabaseManager(QObject *parent) :
    QObject(parent)
{
    // Save pointer of CMainWindow (as QObject)
    m_parent = parent;
    /* Define & open db
     * if the file doesn't exist, it will be created and
     * populated with the table definitions
     */
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbname = QGuiApplication::applicationDirPath();
    dbname.append("/mr.sqlite");
    m_db.setDatabaseName(dbname);

    // Let's check if the file exists
    QFile dbfile(dbname);
    bool dbmiss = false;
    if (!dbfile.open(QFile::ReadOnly))
    {
        // file isn't there; set a flag to create it
        dbmiss = true;
    }

    if (!m_db.open())
    {
        QMessageBox* msg = new QMessageBox();
        msg->setText("Fehler beim Öffnen der Datenbank!");
        msg->setInformativeText("Datenbank lässt sich nicht öffnen!");
        msg->setIcon(QMessageBox::Critical);
        QSqlError lError;
        lError = m_db.lastError();
        msg->setDetailedText(lError.text());
        msg->exec();
    }

    if (dbmiss)
    {
        // opening the db created a plain file; now let's create the tables
        QString sqlname = QGuiApplication::applicationDirPath();
        sqlname.append("/mr.sql");
        QFile sqlfile(sqlname);
        sqlfile.open(QFile::ReadOnly);
        while (!sqlfile.atEnd())
        {
            QString sql = sqlfile.readLine();
            QSqlQuery qry(sql);
            qry.exec();
        }
        sqlfile.close();
    }
}

QList<CPersonal> *CDatabaseManager::personalList(QDate fromDate, QDate toDate)
{
    QSqlQuery* lqry = new QSqlQuery();    
    lqry->prepare("SELECT * FROM tblPersonal WHERE Eintritt < :TO AND Austritt > :FROM ORDER BY Name;");
    lqry->bindValue(":TO", toDate.toString("yyyy-MM-dd"));
    lqry->bindValue(":FROM",fromDate.toString("yyyy-MM-dd"));
    lqry->exec();
    lqry->first();
    QList<CPersonal>* llist = new QList<CPersonal>();
    while (lqry->isValid())
    {
        CPersonal item;
        item.setId(lqry->value(lqry->record().indexOf("ID")).toInt());
        item.setName(lqry->value(lqry->record().indexOf("Name")).toString());
        item.setVName(lqry->value(lqry->record().indexOf("VName")).toString());
        item.setPersNo(lqry->value(lqry->record().indexOf("PNr")).toString());
        item.setSollTag(QTime::fromString(lqry->value(lqry->record().indexOf("SollTag")).toString(),"hh:mm:ss.zzz"));
        llist->append(item);
        lqry->next();
    }
    delete lqry;
    return llist;
}

QList<CDutyType> *CDatabaseManager::dutyTypeList()
{
    QList<CDutyType> *llist = new QList<CDutyType>();
    QSqlQuery* lqry = new QSqlQuery();
    lqry->exec("SELECT * FROM tblDutyTypes ORDER BY Mark;");
    lqry->first();
    while(lqry->isValid())
    {
        CDutyType item;
        item.setId(lqry->value(lqry->record().indexOf("ID")).toInt());
        item.setMark(lqry->value(lqry->record().indexOf("Mark")).toString());
        item.setDesc(lqry->value(lqry->record().indexOf("Decr")).toString());
        item.setTimeFrom(QTime::fromString(lqry->value(lqry->record().indexOf("TimeFrom")).toString(),"hh:mm:ss.zzz"));
        item.setTimeFrom2(QTime::fromString(lqry->value(lqry->record().indexOf("TimeFrom2")).toString(),"hh:mm:ss.zzz"));
        item.setTimeTo(QTime::fromString(lqry->value(lqry->record().indexOf("TimeTo")).toString(),"hh:mm:ss.zzz"));
        item.setTimeTo2(QTime::fromString(lqry->value(lqry->record().indexOf("TimeTo2")).toString(),"hh:mm:ss.zzz"));
        item.setTimeElapsed(QTime::fromString(lqry->value(lqry->record().indexOf("TimeElapsed")).toString(),"hh:mm:ss.zzz"));
        item.setTimeElapsed2(QTime::fromString(lqry->value(lqry->record().indexOf("TimeElapsed2")).toString(),"hh:mm:ss.zzz"));
        item.setMinOffBefore(QTime::fromString(lqry->value(lqry->record().indexOf("MinOffBefore")).toString(),"hh:mm:ss.zzz"));
        item.setMinOffAfter(QTime::fromString(lqry->value(lqry->record().indexOf("MinOffAfter")).toString(),"hh:mm:ss.zzz"));
        item.setRosterColorR(lqry->value(lqry->record().indexOf("ColorR")).toInt());
        item.setRosterColorG(lqry->value(lqry->record().indexOf("ColorG")).toInt());
        item.setRosterColorB(lqry->value(lqry->record().indexOf("ColorB")).toInt());
        llist->append(item);
        lqry->next();
    }
    return llist;
}

QList<CDuty> *CDatabaseManager::dutyList(QDate fromDate, QDate toDate)
{
    QList<CDuty> *llist = new QList<CDuty>();
    QSqlQuery* lqry = new QSqlQuery();
    lqry->prepare("SELECT * FROM tblDuty WHERE DDate >= :FROM AND DDate <= :TO ORDER BY DDate, PersID");
    lqry->bindValue(":FROM", fromDate.toString("yyyy-MM-dd"));
    lqry->bindValue(":TO",toDate.toString("yyyy-MM-dd"));
    lqry->exec();
    lqry->first();
    while(lqry->isValid())
    {
        CDuty item;
        item.setId(lqry->value(lqry->record().indexOf("ID")).toInt());
        item.setDate(QDate::fromString(lqry->value(lqry->record().indexOf("DDate")).toString(),"yyyy-MM-dd"));
        item.setKollege(CPersonal(lqry->value(lqry->record().indexOf("PersID")).toInt()));
        item.setTimeFrom(QTime::fromString(lqry->value(lqry->record().indexOf("TimeFrom")).toString(),"hh:mm:ss.zzz"));
        item.setTimeTo(QTime::fromString(lqry->value(lqry->record().indexOf("TimeTo")).toString(),"hh:mm:ss.zzz"));
        item.setTimeFrom2(QTime::fromString(lqry->value(lqry->record().indexOf("TimeFrom2")).toString(),"hh:mm:ss.zzz"));
        item.setTimeTo2(QTime::fromString(lqry->value(lqry->record().indexOf("TimeTo2")).toString(),"hh:mm:ss.zzz"));
        item.setTyp(CDutyType(lqry->value(lqry->record().indexOf("TypID")).toInt()));
        llist->append(item);
        lqry->next();
    }
    return llist;
}

