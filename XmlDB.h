#ifndef XMLDB_H
#define XMLDB_H

#include <QtXml/QtXml>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QIODevice>
#include <QStringList>
#include <QTableView>

#include "table.h"
#include "abstractdb.h"

class XmlDB : public AbstractDB
{
public:
    XmlDB(QString fp);

    void parseTable(QXmlStreamReader& );
    void parseField(QXmlStreamReader& );

    void readXmlFile(QString);

    void fillModel(Table* tb, QStringList& fields, QStringList& rows);

    void fillTables(QVector<Table *> *tables);

    QTableView tv;

private:
    QString filePath;
    QVector<Table* > tables;
    QStringList fields;
    QStringList rows;
};

#endif // XMLDB_H
