/********************************************************************
*
*   File: cdbuploader.cpp    Class: CDbUploader
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2016 Joerg Pauly
*   Created 05.01.2015 by joerg
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
#include "cdbuploader.h"
#include "cmainwindow.h"

CDbUploader::CDbUploader(QObject *parent) : QObject(parent)
{
    m_parent = parent;
    // Datenbank auf FTP-Server hochladen; Datei "ver.dat" mit neuem Timestamp versehen. (?)
    m_netMan = new QNetworkAccessManager(this);

    connect(m_netMan, SIGNAL(finished(QNetworkReply*)), this, SLOT(uploadFinished(QNetworkReply*)));

    QString dbname = ((CMainWindow*)m_parent)->path()->absolutePath();
    dbname.append("/mr.sqlite");
    m_fileDB = new QFile(dbname);
}

CDbUploader::~CDbUploader()
{
    m_netDbReply->deleteLater();
    m_netTsReply->deleteLater();
    m_fileDB->deleteLater();
    m_fileTS->deleteLater();
    m_upDlg->deleteLater();
}

void CDbUploader::doUpload()
{
    m_fileTS = new QFile("./dbts.ver");
    m_fileTS->open(QIODevice::WriteOnly);
    m_fileTS->write(QDateTime::currentDateTime().toString("YYMMdd.hhmmss").toLocal8Bit());
    m_fileTS->close();

    QUrl lDbUrl("ftp://ftp.it-kramer.eu/mmv/brd/mr.sqlite");
    lDbUrl.setUserName("u40207960");
    lDbUrl.setPassword("P3rsephone");

    if(m_fileDB->open(QIODevice::ReadOnly))
    {
        m_netDbReply = m_netMan->put(QNetworkRequest(lDbUrl),m_fileDB);
    }

    connect(m_netDbReply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(uploadProgress(qint64,qint64)));
    m_upDlg = new CUploadProgressDlg((CMainWindow*)m_parent);
    m_upDlg->setProgress(25, 100);
    m_upDlg->show();

    QUrl lTsUrl("ftp://ftp.it-kramer.eu/mmv/brd/dbts.ver");
    lTsUrl.setUserName("u40207960");
    lTsUrl.setPassword("P3rsephone");
    m_fileTS = new QFile("./dbts.ver");

    if(m_fileTS->open(QIODevice::ReadOnly))
    {
        m_netTsReply = m_netMan->put(QNetworkRequest(lTsUrl),m_fileTS);
    }

    m_upDlg->setProgress(75, 100);
}

void CDbUploader::uploadFinished(QNetworkReply *pReply)
{    
    m_upDlg->close();
}

void CDbUploader::uploadProgress(qint64 pSent, qint64 pTotal)
{
    m_upDlg->setProgress(pSent, pTotal);
    m_upDlg->show();
}

void CDbUploader::authenticate(QNetworkReply *pRply, QAuthenticator *pAuth)
{
    pAuth->setUser("u40207960");
    pAuth->setPassword("P3rsephone");
}

