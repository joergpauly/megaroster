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

#include "cprinttablecell.h"


CPrintTableCell::CPrintTableCell()
{
}

CPrintTableCell::CPrintTableCell(QPoint pPos, int pWidth, int pHeight, QString pText)
{
    m_Rect.setTopLeft(pPos);
    m_Rect.setWidth(pWidth);
    m_Rect.setHeight(pHeight);
    m_Text = pText;
}

void CPrintTableCell::setWidth(int pWidth)
{
    m_Rect.setWidth(pWidth);
}

void CPrintTableCell::setHeight(int pHeight)
{
    m_Rect.setHeight(pHeight);
}

void CPrintTableCell::setPosition(QPoint pPos)
{
    m_Rect.setTopLeft(pPos);
}

QFont CPrintTableCell::Font() const
{
    return m_Font;
}

void CPrintTableCell::setFont(const QFont &Font)
{
    m_Font = Font;
}

QRect CPrintTableCell::Rect() const
{
    return m_Rect;
}

void CPrintTableCell::setRect(const QRect &Rect)
{
    m_Rect = Rect;
}

QString CPrintTableCell::Text() const
{
    return m_Text;
}

void CPrintTableCell::setText(const QString &Text)
{
    m_Text = Text;
}

void CPrintTableCell::draw(QPainter *pPainter)
{
    pPainter->drawRect(m_Rect);
    pPainter->drawText(m_Rect,Qt::AlignCenter,m_Text);
}

