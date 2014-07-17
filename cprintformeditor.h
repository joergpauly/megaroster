/***************************************************************************************
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 17.07.2014 by joerg
*   All Rights reserved
*
*   Alle Programme der MEGA-Serie sind Freie Software: Sie können sie unter den
*   Bedingungen der GNU Lesser General Public License (LGPL), wie von der
*   Free Software Foundation, Version 3 der Lizenz oder (nach Ihrer Option)
*   jeder späteren veröffentlichten Version, weiterverbreiten und/oder
*   modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
*   OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
*   Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU Lesser General Public License für weitere Details.
*
*   Sie sollten eine Kopie der GNU Lesser General Public License zusammen mit diesem
*   Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*
*   All programs of the MEGA-series are Free Software: You can distribute and/or modify
*   them under the terms of the GNU Lesser General Public License (LGPL), as published
*   by the Free Software Foundation, version 3 or (your option) any later published
*   version.
*
*   This program is provided in the hope that it will be usefull, but WITHOUT ANY
*   WARRANTY; even without the implicit warrant of COMMERCIAL BENEFIT or ABILITY FOR A
*   DEFINED UNSAGE.
*   See GNU Lesser General Public License for more details.
*
*   You should have obtained a copy of the GNU Lesser General Public License with this
*   software. If not, see <http://www.gnu.org/licenses/>.
*
****************************************************************************************/

#ifndef CPRINTFORMEDITOR_H
#define CPRINTFORMEDITOR_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "cprinttablecell.h"

namespace Ui {
class CPrintFormEditor;
}

class CPrintFormEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CPrintFormEditor(QWidget *parent = 0);
    ~CPrintFormEditor();
    void setImage(QImage *image);

private:
    Ui::CPrintFormEditor *ui;
    QWidget *m_parent;
};

#endif // CPRINTFORMEDITOR_H
