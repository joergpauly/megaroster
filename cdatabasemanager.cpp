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

