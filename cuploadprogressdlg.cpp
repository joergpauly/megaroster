/********************************************************************
*
*   File: cuploadprogressdlg.cpp    Class: CUploadProgressDlg
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2016 Joerg Pauly
*   Created 04.01.2016 by joerg
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
#include "cuploadprogressdlg.h"
#include "ui_cuploadprogressdlg.h"

CUploadProgressDlg::CUploadProgressDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CUploadProgressDlg)
{
    ui->setupUi(this);
}

CUploadProgressDlg::~CUploadProgressDlg()
{
    delete ui;
}

void CUploadProgressDlg::setProgress(qint64 pSent, qint64 pTotal)
{
    ui->progressBar->setValue(pTotal * pSent / 100);
}
