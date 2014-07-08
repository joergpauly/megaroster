/****************************************************************************************
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 08.07.2014 by joerg
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

#ifndef CPRINTTABLECELL_H
#define CPRINTTABLECELL_H

#include <QRect>
#include <QPoint>
#include <QFont>
#include <QColor>
#include <QString>
#include <QPainter>


class CPrintTableCell
{

private:
    QRect   m_Rect;
    QFont   m_Font;
    QString m_Text;



public:
    CPrintTableCell();
    CPrintTableCell(QPoint pPos, int pWidth = 0, int pHeight = 0, QString pText = "");


    void setWidth(int pWidth);
    void setHeight(int pHeight);
    void setPosition(QPoint pPos);

    QFont Font() const;
    void setFont(const QFont &Font);
    QRect Rect() const;
    void setRect(const QRect &Rect);
    QString Text() const;
    void setText(const QString &Text);

    void draw(QPainter *pPainter);
};

#endif // CPRINTTABLECELL_H
