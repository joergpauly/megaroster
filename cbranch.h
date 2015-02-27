/****************************************************************************************
*
*   File:
*
*   This file is part of the MEGASeries Project.
*   Copyright (C) 2015 Joerg Pauly, MEGAMover.de
*   File created 27.02.2015 by joerg
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

#ifndef CBRANCH_H
#define CBRANCH_H

#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlError>

class CBranch
{
public:
    CBranch();
    CBranch(int pID);
    ~CBranch();

    bool saveToDB();

    int ID() const;
    void setID(int ID);

    QString Name1() const;
    void setName1(const QString &Name1);

    QString Name2() const;
    void setName2(const QString &Name2);

    QString Name3() const;
    void setName3(const QString &Name3);

    QString Adress1() const;
    void setAdress1(const QString &Adress1);

    QString Adress2() const;
    void setAdress2(const QString &Adress2);

    QString Adress3() const;
    void setAdress3(const QString &Adress3);

    QString Adress4() const;
    void setAdress4(const QString &Adress4);

    QString Adress5() const;
    void setAdress5(const QString &Adress5);

    QString Hours() const;
    void setHours(const QString &Hours);

    int Valid() const;
    void setValid(int Valid);

private:
    int     m_ID;
    QString m_Name1;
    QString m_Name2;
    QString m_Name3;
    QString m_Adress1;
    QString m_Adress2;
    QString m_Adress3;
    QString m_Adress4;
    QString m_Adress5;
    QString m_Hours;
    int     m_Valid;

};

#endif // CBRANCH_H
