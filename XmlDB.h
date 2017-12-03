#ifndef XMLDB_H
#define XMLDB_H

#include <QtXml/QtXml>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QIODevice>
#include <QStringList>
#include <QTableView>

#include "AbstractDB.h"

class Table;

class XmlDB : public AbstractDB
{
public:
    XmlDB(const QString &fp);

    void parseTable(QXmlStreamReader& );

    void readXmlFile(const QString &);

    void fillModel(Table* tb, QStringList& fields, QStringList& rows);

    QVector<Table *>* fillTables() override;

private:
    QString filePath;
    QVector<Table* > *tables;
    QStringList fields;
    QStringList rows;
};

#endif // XMLDB_H
