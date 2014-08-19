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

#ifndef CPERSONAL_H
#define CPERSONAL_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class CPersonal
{
public:
    CPersonal(int pID);
    CPersonal();

    QString Name() const;
    void setName(const QString &Name);

    QString VName() const;
    void setVName(const QString &VName);

    QString PersNo() const;
    void setPersNo(const QString &PersNo);

    QTime SollTag() const;
    void setSollTag(const QTime &SollTag);

    QDate GebDat() const;
    void setGebDat(const QDate &GebDat);

    int id() const;
    void setId(int id);

    QDate Eintritt() const;
    void setEintritt(const QDate &Eintritt);

    QDate Austritt() const;
    void setAustritt(const QDate &Austritt);

    bool Edit() const;
    void setEdit(const bool pEd);

    bool Admin() const;
    void setAdmin(const bool pAd);

private:
    int m_id;
    QString m_Name;
    QString m_VName;
    QString m_PersNo;
    QDate   m_GebDat;
    QTime   m_SollTag;
    QDate   m_Eintritt;
    QDate   m_Austritt;
    bool    m_Edit;
    bool    m_Admin;

};

#endif // CPERSONAL_H
