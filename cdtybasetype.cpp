/****************************************************************************************
*
*   This file is part of the MEGASeries Project.
*   Copyright (C) 2014 Joerg Pauly
*   All Rights reserved
*
*   Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
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


#include "cdtybasetype.h"

CDtyBaseType::CDtyBaseType()
{
}

CDtyBaseType::CDtyBaseType(int id)
{
    QSqlQuery *lqry = new QSqlQuery();
    lqry->prepare("SELECT * FROM tblDtyBase WHERE ID = :ID;");
    lqry->bindValue(":ID", id);
    lqry->exec();
    lqry->first();
    m_id = id;
    m_CLetter = lqry->value(lqry->record().indexOf("Codeletter")).toString();
    m_Desc = lqry->value(lqry->record().indexOf("Desc")).toString();
    delete lqry;
}

QString CDtyBaseType::Desc() const
{
    return m_Desc;
}

void CDtyBaseType::setDesc(const QString &Desc)
{
    m_Desc = Desc;
}

QString CDtyBaseType::CLetter() const
{
    return m_CLetter;
}

void CDtyBaseType::setCLetter(const QString &CLetter)
{
    m_CLetter = CLetter;
}

int CDtyBaseType::id() const
{
    return m_id;
}

void CDtyBaseType::setId(int id)
{
    m_id = id;
}



