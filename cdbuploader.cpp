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

void CDbUploader::doUpload()
{
    QUrl lUrl("ftp://ftp.it-kramer.eu/mmv/brd/mr.sqlite");
    lUrl.setUserName("u40207960");
    lUrl.setPassword("P3rsephone");

    if(m_fileDB->open(QIODevice::ReadOnly))
    {
        m_netReply = m_netMan->put(QNetworkRequest(lUrl),m_fileDB);
    }

    connect(m_netReply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(uploadProgress(qint64,qint64)));
    m_upDlg = new CUploadProgressDlg((CMainWindow*)m_parent);
    m_upDlg->setProgress(0, 100);
    m_upDlg->show();
}

void CDbUploader::uploadFinished(QNetworkReply *pReply)
{
    QMessageBox lbox;
    lbox.setWindowTitle("Fertig!");
    lbox.setText(pReply->errorString());
    lbox.exec();
    m_upDlg->close();
    m_upDlg->deleteLater();
    m_netReply->deleteLater();
    m_fileDB->deleteLater();
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

