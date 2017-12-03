#include <QDebug>

#include "XmlDB.h"
#include "Table.h"

XmlDB::XmlDB(const QString &fp) : filePath(fp)
{
    readXmlFile(filePath);
    fields.clear();
    rows.clear();
}

void XmlDB::readXmlFile(const QString &path)
{
    QFile* file = new QFile(path);

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        qDebug() << "Error: File not open" << file->errorString();
        return;
    }

    QXmlStreamReader xmlReader(file);

    while( !xmlReader.atEnd() && !xmlReader.hasError() )
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();

        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }

        if(token == QXmlStreamReader::StartElement)
        {

            if(xmlReader.name() == "Database")
            {
                int numOfTables = xmlReader.attributes().value("tablesCount").toString().toInt();
                tables = new QVector<Table*>;
                tables->reserve(numOfTables);

                xmlReader.readNext();

                int accessMode = xmlReader.attributes().value("accessMode").toString().toInt();
                //qDebug() << "Count of tables: " << numOfTables << " Access mode: " << accessMode;
            }

            if(xmlReader.name() == "Table")
            {
                parseTable(xmlReader);
            }
        }
    }
}

void XmlDB::parseTable(QXmlStreamReader& xmlReader)
{
    if(xmlReader.tokenType() != QXmlStreamReader::StartElement
            && xmlReader.name() != "Table")
    {
        qDebug() << "praseTable() :: Called wrong XML tag: " << xmlReader.name();
        return;
    }

    Table* tb = new Table();

    //set table's name
    QString tName = xmlReader.attributes().value("tableName").toString();
    tb->setName(tName);
    //qDebug() << "tables name" << tb->getName();

    //set counts of fields and rows
    int countOfFields = xmlReader.attributes().value("fieldsCount").toString().toInt();
    int countOfRows = xmlReader.attributes().value("rowsCount").toString().toInt();
    //qDebug() << "get counts" << tb->getFieldsCount() << tb->getRowsCount();

    //set table's model size
    int current = 0;
    QStandardItemModel* model = new QStandardItemModel(countOfRows, 2);
    QStandardItemModel* model2 = new QStandardItemModel(countOfRows, countOfFields);

    int index = 0;

    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement
            && xmlReader.name() == "Table"))
    {
        if(xmlReader.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xmlReader.name() == "DispalyParams")
            {
                int xCoord = xmlReader.attributes().value("xCoord").toString().toInt();
                int yCoord = xmlReader.attributes().value("yCoord").toString().toInt();
                int width = xmlReader.attributes().value("width").toString().toInt();
                int heigh = xmlReader.attributes().value("heigh").toString().toInt();

                tb->setCoord(xCoord, yCoord, (DisplayMode) index);
                tb->resize(width, heigh, (DisplayMode) index);

                ++index;

                //qDebug() << displayMode << xCoord << yCoord << width << heigh;

            }

            if(xmlReader.name() == "Fields")
            {
                for(int i = 0; i < xmlReader.attributes().size(); i++)
                {
                    model->setItem(i, 0, new QStandardItem(xmlReader.attributes().at(i).name().toString())  );
                    model->setItem(i, 1, new QStandardItem(xmlReader.attributes().at(i).value().toString()) );
                    ////qDebug() << xmlReader.attributes().at(i).name() << xmlReader.attributes().at(i).value();
                }
                tb->setObjectsModel(model);
            }

            if(xmlReader.name() == "Row")
            {
                for(int j = 0; j < countOfFields; j++)
                {
                    model2->setItem(current, j, new QStandardItem(xmlReader.attributes().at(j).value().toString())  );
                }
                ++current;

                tb->setRowsModel(model2);
            }
        }
        xmlReader.readNext();
    }

    tables->push_back(tb);

    return;
}

QVector<Table *>* XmlDB::fillTables()
{
    return tables;
}
