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

#include "cbranch.h"

CBranch::CBranch()
{
    m_ID = 0;
    m_Name1 = "";
    m_Name2 = "";
    m_Name3 = "";
    m_Adress1 = "";
    m_Adress2 = "";
    m_Adress3 = "";
    m_Adress4 = "";
    m_Adress5 = "";
    m_Hours = "";
    m_Valid = true;
}

CBranch::CBranch(int pID)
{
    m_Valid = false;
    QSqlQuery lqry;
    lqry.prepare("SELECT * FROM tblBranches WHERE ID = :ID;");
    lqry.bindValue(":ID", QVariant(pID));
    lqry.exec();
    lqry.first();

    if(!lqry.isValid())
    {
        return;
    }
    else
    {
        m_Valid = true;
    }

    m_ID = pID;
    m_Name1 = lqry.value(lqry.record().indexOf("Name1")).toString();
    m_Name2 = lqry.value(lqry.record().indexOf("Name2")).toString();
    m_Name3 = lqry.value(lqry.record().indexOf("Name3")).toString();
    m_Adress1 = lqry.value(lqry.record().indexOf("Adress1")).toString();
    m_Adress2 = lqry.value(lqry.record().indexOf("Adress2")).toString();
    m_Adress3 = lqry.value(lqry.record().indexOf("Adress3")).toString();
    m_Adress4 = lqry.value(lqry.record().indexOf("Adress4")).toString();
    m_Adress5 = lqry.value(lqry.record().indexOf("Adress5")).toString();
    m_Hours = lqry.value(lqry.record().indexOf("Hours")).toString();
}

CBranch::~CBranch()
{

}

void CBranch::saveToDB()
{
    QSqlQuery lqry;
    lqry.prepare("UPDATE tblBranches SET Name1 = :Name1, Name2 = :Name2, Name3 = :Name3, Adress1 = :Addr1, Adress2 = :Addr2, Adress3 = :Addr3, Adress4 = :Addr4, Adress5 = :Addr5, Hours = :Hrs WHERE ID = :ID;");
    lqry.bindValue(":Name1", m_Name1);
    lqry.bindValue(":Name2", m_Name2);
    lqry.bindValue(":Name3", m_Name3);
    lqry.bindValue(":Addr1", m_Adress1);
    lqry.bindValue(":Addr2", m_Adress2);
    lqry.bindValue(":Addr3", m_Adress3);
    lqry.bindValue(":Addr4", m_Adress4);
    lqry.bindValue(":Addr5", m_Adress5);
    lqry.bindValue(":Hrs", m_Hours);
    lqry.bindValue(":ID", m_ID);
    lqry.exec();
}

int CBranch::ID() const
{
    return m_ID;
}

void CBranch::setID(int ID)
{
    m_ID = ID;
}

QString CBranch::Name1() const
{
    return m_Name1;
}

void CBranch::setName1(const QString &Name1)
{
    m_Name1 = Name1;
}

QString CBranch::Name2() const
{
    return m_Name2;
}

void CBranch::setName2(const QString &Name2)
{
    m_Name2 = Name2;
}

QString CBranch::Name3() const
{
    return m_Name3;
}

void CBranch::setName3(const QString &Name3)
{
    m_Name3 = Name3;
}

QString CBranch::Adress1() const
{
    return m_Adress1;
}

void CBranch::setAdress1(const QString &Adress1)
{
    m_Adress1 = Adress1;
}

QString CBranch::Adress2() const
{
    return m_Adress2;
}

void CBranch::setAdress2(const QString &Adress2)
{
    m_Adress2 = Adress2;
}

QString CBranch::Adress3() const
{
    return m_Adress3;
}

void CBranch::setAdress3(const QString &Adress3)
{
    m_Adress3 = Adress3;
}

QString CBranch::Adress4() const
{
    return m_Adress4;
}

void CBranch::setAdress4(const QString &Adress4)
{
    m_Adress4 = Adress4;
}

QString CBranch::Adress5() const
{
    return m_Adress5;
}

void CBranch::setAdress5(const QString &Adress5)
{
    m_Adress5 = Adress5;
}

QString CBranch::Hours() const
{
    return m_Hours;
}

void CBranch::setHours(const QString &Hours)
{
    m_Hours = Hours;
}

int CBranch::Valid() const
{
    return m_Valid;
}

void CBranch::setValid(int Valid)
{
    m_Valid = Valid;
}












