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

    tuple<QVector<Table *> *, AccessMode> readXmlFile(const QString &);

    tuple<QVector<Table *>*, AccessMode> fillTables() override;

    void save();

private:
    QString filePath;
    QXmlStreamWriter xmlWriter;
    QVector<Table* > *tables;
};

#endif // XMLDB_H
