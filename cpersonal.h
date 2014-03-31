/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 31.03.2014 by joerg
*   All Rights reserved
*
*   ChartButler ist Freie Software: Sie können es unter den Bedingungen
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

#ifndef CPERSONAL_H
#define CPERSONAL_H

#include <QString>
#include <QDate>

class CPersonal
{
public:
    CPersonal();
    CPersonal(QString pName,
                QString pVName,
                QString pPersNo,
                QDate   pGebDat,
                int     pSollTag);

    QString Name() const;
    void setName(const QString &Name);

    QString VName() const;
    void setVName(const QString &VName);

    QString PersNo() const;
    void setPersNo(const QString &PersNo);

    int SollTag() const;
    void setSollTag(int SollTag);

    QDate GebDat() const;
    void setGebDat(const QDate &GebDat);

private:
    QString m_Name;
    QString m_VName;
    QString m_PersNo;
    QDate   m_GebDat;
    int     m_SollTag;

};

#endif // CPERSONAL_H
