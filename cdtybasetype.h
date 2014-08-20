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

#ifndef CDTYBASETYPE_H
#define CDTYBASETYPE_H

#include <QString>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>

class CDtyBaseType
{
public:
    CDtyBaseType();
    CDtyBaseType(int id);

    QString Desc() const;
    void setDesc(const QString &Desc);

    QString CLetter() const;
    void setCLetter(const QString &CLetter);

    int id() const;
    void setId(int id);

private:
    int         m_id;
    QString     m_CLetter;
    QString     m_Desc;
};

#endif // CDTYBASETYPE_H
