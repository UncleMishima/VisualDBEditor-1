#include <QDebug>

#include "XmlDB.h"
#include "Table.h"

XmlDB::XmlDB(const QString &fp) : filePath(fp)
{

}

tuple<QVector<Table *> *, AccessMode> XmlDB::readXmlFile(const QString &path)
{
    QFile* file = new QFile(path);

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        qDebug() << "Error: File not open" << file->errorString();
    }

    AccessMode accessMode;

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

                //int accessMode = xmlReader.attributes().value("accessMode").toString().toInt();
                accessMode = (AccessMode)xmlReader.attributes().value("accessMode").toString().toInt();
                //                qDebug() << "Count of tables: "
                //                         << numOfTables << " Access mode: "
                //                         << accessMode;
            }

            if(xmlReader.name() == "Table")
            {
                parseTable(xmlReader);
            }
        }
    }
    return tuple<QVector<Table *> *, AccessMode>(tables, accessMode);
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
    QStandardItemModel* fieldsModel = new QStandardItemModel(countOfFields, 2);
    QStandardItemModel* objectsModel = new QStandardItemModel(countOfRows, countOfFields);

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

                tb->setCoord(xCoord, yCoord, (DisplayMode)index);
                tb->resize(width, heigh, (DisplayMode)index);

                ++index;

                //qDebug() << displayMode << xCoord << yCoord << width << heigh;

            }

            if(xmlReader.name() == "Fields")
            {
                for(int i = 0; i < xmlReader.attributes().size(); i++)
                {
                    fieldsModel->setItem(i, 0, new QStandardItem(xmlReader.attributes().at(i).name().toString())  );
                    fieldsModel->setItem(i, 1, new QStandardItem(xmlReader.attributes().at(i).value().toString()) );
                    //qDebug() << xmlReader.attributes().at(i).name() << xmlReader.attributes().at(i).value();
                }
                tb->setObjectsModel(fieldsModel);
            }

            if(xmlReader.name() == "Row")
            {
                for(int j = 0; j < countOfFields; j++)
                {
                    objectsModel->setItem(current, j, new QStandardItem(xmlReader.attributes().at(j).value().toString())  );
                }
                ++current;

                tb->setRowsModel(objectsModel);
            }
        }
        xmlReader.readNext();
    }

    // debug Header labels settings. Need to think where we must place it.
    fieldsModel->setHorizontalHeaderLabels(QStringList() << "Name" << "Type");

    QStringList objectsModelHHLabels;
    for (int i = 0; i < fieldsModel->rowCount(); i++)
    {
        objectsModelHHLabels << fieldsModel->item(i, 0)->data(Qt::DisplayRole).toString();
    }
    objectsModel->setHorizontalHeaderLabels(objectsModelHHLabels);

    tables->push_back(tb);

    return;
}

tuple<QVector<Table *> *, AccessMode> XmlDB::fillTables()
{
    return readXmlFile(filePath);
}





void XmlDB::save()
{
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        qDebug() << "Error: File not saved";
        return;
    }

    for(int i = 0; i < tables->size(); i++)
    {
        int fieldsCount = tables->at(i)->getFieldsModel()->columnCount();
//        int rowsCount = tables->at(i)->getObjectsModel()->rowCount();
//        qDebug() << "Table #" << i+1;
        qDebug() << "Fields" << fieldsCount;
//        qDebug() << "Rows" << rowsCount;
//        qDebug() << " ";
//        qDebug() << "Row 0, Fiels 0" << tables->at(i)->getFieldsModel()->data(tables->at(i)->getFieldsModel()->index(i, 0)).toString();
//        qDebug() << "Row 0, Fiels 0" << tables->at(i)->getFieldsModel()->item(0, 0)->data(Qt::DisplayRole).toString();
//        qDebug() << "Row 0, Fiels 1" << tables->at(i)->getFieldsModel()->item(0, 1)->data(Qt::DisplayRole).toString();
//        qDebug() << "Row 1, Fiels 0" << tables->at(i)->getFieldsModel()->item(1, 0)->data(Qt::DisplayRole).toString();
//        qDebug() << "Row 1, Fiels 1" << tables->at(i)->getFieldsModel()->item(1, 1)->data(Qt::DisplayRole).toString();
//        qDebug() << " ";
//        qDebug() << " ";
    }

    xmlWriter.setDevice(&file);

    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("Database");
    xmlWriter.writeAttribute("tablesCount", QString::number(tables->size()));
    xmlWriter.writeAttribute("accessMode", "2");

    for(int i = 0; i < tables->size(); i++)
    {
        int fieldsCount = tables->at(i)->getFieldsModel()->rowCount();
        int rowsCount = tables->at(i)->getObjectsModel()->rowCount();
        xmlWriter.writeStartElement("Table");

        xmlWriter.writeAttribute("tableName", tables->at(i)->getName());
        xmlWriter.writeAttribute("fieldsCount", QString::number(fieldsCount));
        xmlWriter.writeAttribute("rowsCount", QString::number(rowsCount));

        for(int j = 0; j < DISPLAY_MODES_COUNT; j++)
        {
            xmlWriter.writeStartElement("DispalyParams");
            xmlWriter.writeAttribute("fieldsCount", QString::number(j));
            xmlWriter.writeAttribute("xCoord", QString::number(tables->at(i)->getCoordX((DisplayMode)j)));
            xmlWriter.writeAttribute("yCoord", QString::number(tables->at(i)->getCoordY((DisplayMode)j)));
            xmlWriter.writeAttribute("width", QString::number(tables->at(i)->getWidth((DisplayMode)j)));
            xmlWriter.writeAttribute("heigh", QString::number(tables->at(i)->getHeight((DisplayMode)j)));
            xmlWriter.writeEndElement();
        }

        xmlWriter.writeStartElement("Fields");

        for(int j = 0; j < fieldsCount; j++)
        {
            xmlWriter.writeAttribute(tables->at(i)->getFieldsModel()->item(j, 0)->data(Qt::DisplayRole).toString(),
                                     //tables->at(i)->getFieldsModel()->data(tables->at(i)->getFieldsModel()->index(0, j)).toString());
                                     tables->at(i)->getFieldsModel()->item(j, 1)->data(Qt::DisplayRole).toString());
            //qDebug() << tables->at(i)->getFieldsModel()->item(i, j)->data().toString();

            //qDebug() << tables->at(i)->getFieldsModel()->data(tables->at(i)->getFieldsModel()->index(0, j)).toString();
        }
        xmlWriter.writeEndElement();


        for(int k = 0; k < rowsCount; k++)
        {
            xmlWriter.writeStartElement("Row");
            for(int j = 0; j < fieldsCount; j++)
            {
                xmlWriter.writeAttribute(tables->at(i)->getFieldsModel()->item(j, 0)->data(Qt::DisplayRole).toString(),
                                         //tables->at(i)->getObjectsModel()->data(tables->at(i)->getFieldsModel()->index(j, k)).toString());
                                         tables->at(i)->getObjectsModel()->item(k, j)->data(Qt::DisplayRole).toString());
            }
            xmlWriter.writeEndElement();
        }

        xmlWriter.writeEndElement(); //end of Table
    }

    xmlWriter.writeEndElement(); //end of Database
    xmlWriter.writeEndDocument(); // end of doc
}
