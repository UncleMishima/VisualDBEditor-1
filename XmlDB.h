#ifndef XMLDB_H
#define XMLDB_H

#include <QtXml/QtXml>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QIODevice>
#include <QStringList>
#include <QTableView>

#include "Table.h"
#include "AbstractDB.h"

class XmlDB : public AbstractDB
{
public:
    XmlDB(QString fp);

    void parseTable(QXmlStreamReader& );

    void readXmlFile(QString);

    void fillModel(Table* tb, QStringList& fields, QStringList& rows);

    QVector<Table *>* fillTables() override;

    QTableView tv;

private:
    QString filePath;
    QVector<Table* > tables;
    QStringList fields;
    QStringList rows;
};

#endif // XMLDB_H
