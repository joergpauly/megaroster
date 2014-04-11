/****************************************************************************************
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 11.04.2014 by joerg
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

#include "cprintform.h"
#include "ui_cprintform.h"

CPrintForm::CPrintForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CPrintForm)
{
    ui->setupUi(this);
    setGraph();
}

CPrintForm::~CPrintForm()
{
    delete ui;
}

void CPrintForm::setGraph()
{
    QGraphicsScene *scene = new QGraphicsScene();
    QString fname = qApp->applicationDirPath();
    fname.append("/wappen.jpeg");
    QPixmap *img = new QPixmap(fname);
    scene->addPixmap(*img);
    ui->graphicsView->setScene(scene);
}

void CPrintForm::setTextTopLeft(QString pTxt)
{
    ui->txtLeft->setText(pTxt);
}

void CPrintForm::setTextTipMid(QString pTxt)
{
    ui->txtMid->setText(pTxt);
}

void CPrintForm::setTextTopRight(QString pTxt)
{
    ui->txtRight->setText(pTxt);
}

void CPrintForm::setTextFooter(QString pTxt)
{
    ui->txtFooter->setText(pTxt);
}

void CPrintForm::setTable(QTableWidget *table)
{
    ui->tableWidget = table;
}

void CPrintForm::setSubWnd(QMdiSubWindow *pSubWnd)
{
    m_SubWnd = pSubWnd;
}
