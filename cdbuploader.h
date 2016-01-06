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
    void doUpload();

signals:

public slots:
    void uploadFinished(QNetworkReply *pReply);
    void uploadProgress(qint64 pSent, qint64 pTotal);
    void authenticate(QNetworkReply* pRply, QAuthenticator* pAuth);

private:
    QObject*                m_parent;
    QNetworkAccessManager*  m_netMan;
    QNetworkReply*          m_netReply;
    QFile*                  m_fileDB;
    CUploadProgressDlg*     m_upDlg;
};

#endif // CDBUPLOADER_H
