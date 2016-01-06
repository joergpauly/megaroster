/********************************************************************
*
*   File: cdbuploader.h    Class: CDbUploader
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2016 Joerg Pauly
*   Created %DATE% by %USER%
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
#ifndef CDBUPLOADER_H
#define CDBUPLOADER_H

#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QAuthenticator>
#include <QUrl>
#include <QFile>

#include "cuploadprogressdlg.h"

class CDbUploader : public QObject
{
    Q_OBJECT
public:
    explicit CDbUploader(QObject *parent = 0);
    ~CDbUploader();
    void doUpload();

signals:

public slots:
    void uploadFinished(QNetworkReply *pReply);
    void uploadProgress(qint64 pSent, qint64 pTotal);
    void authenticate(QNetworkReply* pRply, QAuthenticator* pAuth);

private:
    QObject*                m_parent;
    QNetworkAccessManager*  m_netMan;
    QNetworkReply*          m_netDbReply;
    QNetworkReply*          m_netTsReply;
    QFile*                  m_fileDB;
    QFile*                  m_fileTS;
    CUploadProgressDlg*     m_upDlg;
};

#endif // CDBUPLOADER_H
