#ifndef CRULE_H
#define CRULE_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QList>

#include "cdutytype.h"


class CRule
{
public:
    CRule(int pID);

    QList<CDutyType> *tList() const;
    void setTList(QList<CDutyType> *tList);

    int ID() const;
    void setID(int ID);

    QString Name() const;
    void setName(const QString &Name);

private:



    QList<CDutyType> *m_tList;
    int m_ID;
    QString m_Name;
};

#endif // CRULE_H
