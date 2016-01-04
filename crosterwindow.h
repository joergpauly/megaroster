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
#ifndef CROSTERWINDOW_H
#define CROSTERWINDOW_H

// System-Header
#include <QWidget>
#include <QMdiSubWindow>
#include <QList>
#include <QTableWidgetItem>
#include <QPrintDialog>
#include <QPrinter>
#include <QPrintPreviewWidget>
#include <QPainter>
#include <QXmlStreamReader>
#include <QStringRef>
#include <QImage>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QFile>

// Projekt-Header
#include "cdatabasemanager.h"
#include "cpersonal.h"
#include "cdutytype.h"
#include "cduty.h"
#include "cdtybasetype.h"
#include "choliday.h"
#include "cprealert.h"
#include "cprealerttype.h"
#include "crule.h"
#include "cprinttable.h"
#include "cuploadprogressdlg.h"


namespace Ui {
class CRosterWindow;
}

class CRosterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CRosterWindow(QWidget *parent = 0);
    explicit CRosterWindow(QWidget *parent, int pMonth, int pYear);
    ~CRosterWindow();
    void setSubWnd(QWidget* pSubWnd);


private slots:
    void on_dtedMonthChoice_dateChanged(const QDate &date);    
    void on_cmbDutyType_currentIndexChanged(const QString &arg1);
    void on_tbwRoster_itemClicked(QTableWidgetItem *item);
    void on_tbwRoster_itemSelectionChanged();
    void on_tbwRoster_itemChanged(QTableWidgetItem *item);
    void on_tbwRoster_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_cmdPrint_clicked();   
    void on_tblPrealerts_itemDoubleClicked(QTableWidgetItem *item);
    void on_cbShowAlerts_clicked(bool checked);
    void on_cmdCheckRoster_clicked();
    void on_timFrom_timeChanged(const QTime &time);
    void on_timTo_timeChanged(const QTime &time);
    void on_timFrom2_timeChanged(const QTime &time);
    void on_timTo2_timeChanged(const QTime &time);
    void on_chkRTCheck_stateChanged(int arg1);
    void on_cmdBlocks_toggled(bool checked);
    void on_cmdNextMonth_clicked();
    void on_cmdPreviousMonth_clicked();
    void on_chkReq_clicked(bool checked);
    void on_cmdPublish_clicked();
    void uploadFinished(QNetworkReply *pReply);
    void uploadProgress(qint64 pSent, qint64 pTotal);


private:
    // Properties    
    QWidget*            m_subWnd;
    QString             m_Prefix;
    int                 m_Month;
    int                 m_Year;
    QWidget*            m_parent;
    CDatabaseManager*   m_dbman;
    CHoliday*           m_Holidays;
    //QList<CDuty>*       m_duty;
    bool                m_init;
    bool                m_edit;
    int                 oldRow;
    CDutyType*          m_DType;
    QList<CRule>*       m_ruleList;
    CDuty               m_previousDuty;
    CDuty*              m_currentDuty;
    bool                m_updatingDetails;
    CPersonal*          m_actUser;
    Ui::CRosterWindow*  ui;
    bool                m_checkingRules;

    // Nur für DB-Upload
    QNetworkAccessManager*   m_netMan;
    QNetworkReply*      m_netReply;
    QFile*              m_fileDB;
    CUploadProgressDlg* m_upDlg;



    // Funktionen
    void setTabTitle(QString pPrefix, QDate pDate);
    void makeRows(QDate pDate);
    void makeColumns(QDate pDate);
    void makeSollH(QDate pDate, int pwdays, int pcol);
    void makeIstH();
    void makeIstH(int prow);
    void makeDiff(int prow);
    void makeRoster(QDate pDate);
    void updateDetails(int prow, int pcol);
    void updateDetails(CDuty* pDuty);
    void updatePrealerts(CDuty* pDuty);
    void loadRules();
    bool checkRules(QDate pdate);
    bool checkRuleSet(QList<CDutyType> pList);
    void updateDutyDB();
    void checkBaseTarget(CDuty *pDuty);
    int  checkBaseActual(CDtyBaseType* pType);
    int  getTotalManPower(CDuty *pDuty);
    int  getSingleManPower(CDuty *pDuty);
    void saveFromTable(int row, int col);
    void saveFromTable(QTableWidgetItem *item);

};

#endif // CROSTERWINDOW_H
