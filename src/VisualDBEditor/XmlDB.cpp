#include <QDebug>

#include "XmlDB.h"
#include "Table.h"

XmlDB::XmlDB(const QString &fp) : filePath(fp)
{

}

uint tableCounter = 0;

QString XmlDB::displayModeToString(DisplayMode mode)
{
    QString str;
    switch(mode)
    {
    case CLASSES:
        str = "CLASSES";
        break;
    case FIELDS:
        str = "FIELDS";
        break;
    case OBJECTS:
        str = "OBJECTS";
        break;
    default:
        str = "UNKNOWN";
    }
    return str;
}

DisplayMode XmlDB::stringToDisplayMode(QString str)
{
    DisplayMode mode;
    if(str == "CLASSES") mode = CLASSES;
    if(str == "FIELDS")  mode = FIELDS;
    if(str == "OBJECTS") mode = OBJECTS;
    return mode;
}

tuple<QVector<Table *> *, QVector<Relation *> *> XmlDB::readXmlFile(const QString &path)
{
    QFile* file = new QFile(path);
    QVector<Table*> *tables = new QVector<Table*>;
    QVector<Relation*> *relations = new QVector<Relation*>;

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        qDebug() << "Error: File not open" << file->errorString();
    }

    xmlReader.setDevice(file);

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
                tables->reserve(numOfTables);

                xmlReader.readNext();

                //int accessMode = xmlReader.attributes().value("accessMode").toString().toInt();
                //accessMode = (AccessMode)xmlReader.attributes().value("accessMode").toString().toInt();
                //                qDebug() << "Count of tables: "
                //                         << numOfTables << " Access mode: "
                //                         << accessMode;
            }

            if(xmlReader.name() == "Table")
            {
                parseTable(tables);
            }

            if(xmlReader.name() == "Relation")
            {
                Relation* r = new Relation();
                QString leftTableName = xmlReader.attributes()
                        .value("leftTableName").toString();
                //QString leftFieldName = xmlReader.attributes().value("leftFieldName").toString();
                QString rightTableName = xmlReader.attributes()
                        .value("rightTableName").toString();
                //QString rightFieldName = xmlReader.attributes().value("rightFieldName").toString();

                qDebug() << tableID["Teachers"];
                qDebug() << tableID["Info"];

                for(int i = 0; i < tableID.size(); i++)
                {
                    if(leftTableName == "Teachers")
                    {
                        r->setFirstTableId(tableID["Teachers"]);
                    }

                    if(rightTableName == "Info")
                    {
                        r->setSecondTableId(tableID["Info"]);
                    }
                }

                relations->push_back(r);
            }
        }
    }
    return tuple<QVector<Table *> *, QVector<Relation*>*>(tables, relations);
}

void XmlDB::parseTable(QVector<Table *> *tables)
{
    if(xmlReader.tokenType() != QXmlStreamReader::StartElement
            && xmlReader.name() != "Table")
    {
        qDebug() << "parseTable() :: Called wrong XML tag: " << xmlReader.name();
        return;
    }

    Table* tb = new Table();

    //set table's name
    QString tName = xmlReader.attributes().value("tableName").toString();
    tb->setName(tName);

    //set counts of fields and rows
    int countOfFields = xmlReader.attributes().value("fieldsCount").toString().toInt();
    int countOfRows = xmlReader.attributes().value("rowsCount").toString().toInt();

    //set table's model size
    int current = 0;
    QStandardItemModel* fieldsModel = new QStandardItemModel(countOfFields, 2);
    QStandardItemModel* objectsModel = new QStandardItemModel(countOfRows, countOfFields);

    //int index = 0;

    tableID.insert(tb->getName(), tableCounter);

    ++tableCounter;

    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement
            && xmlReader.name() == "Table"))
    {
        if(xmlReader.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xmlReader.name() == "DisplayParams")
            {
                DisplayMode displayMode = stringToDisplayMode(xmlReader.attributes().value("displayMode").toString());
                //QString displayMode = xmlReader.attributes().value("displayMode").toString();
                int xCoord = xmlReader.attributes().value("xCoord").toString().toInt();
                int yCoord = xmlReader.attributes().value("yCoord").toString().toInt();
                int width = xmlReader.attributes().value("width").toString().toInt();
                int heigh = xmlReader.attributes().value("heigh").toString().toInt();

                //tb->setDisplayMode();
                tb->setCoord(xCoord, yCoord, displayMode);
                tb->resize(width, heigh, displayMode);

                //++index;
                //if(displayMode == stringToDisplayMode("CLASSES") || displayMode == stringToDisplayMode("OBJECTS") || displayMode == stringToDisplayMode("FIELDS")) qDebug() << "YES";
                //else qDebug() << "NO";

                qDebug() << displayModeToString(displayMode) << " " << xmlReader.attributes().value("displayMode").toString() << xCoord << yCoord << width << heigh;

            }

            if(xmlReader.name() == "Fields")
            {
                for(int i = 0; i < xmlReader.attributes().size(); i++)
                {
                    fieldsModel->setItem(i, 0, new QStandardItem(xmlReader.attributes().at(i).name().toString())  );
                    fieldsModel->setItem(i, 1, new QStandardItem(xmlReader.attributes().at(i).value().toString()) );
                    //qDebug() << xmlReader.attributes().at(i).name() << xmlReader.attributes().at(i).value();
                }
                tb->setFieldsModel(fieldsModel);
            }

            if(xmlReader.name() == "Row")
            {
                for(int j = 0; j < countOfFields; j++)
                {
                    objectsModel->setItem(current, j, new QStandardItem(xmlReader.attributes().at(j).value().toString())  );
                }
                ++current;

                tb->setObjectsModel(objectsModel);
            }
        }
        xmlReader.readNext();
    }

    /// debug Header labels settings. Need to think where we must place it.
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

tuple<QVector<Table *> *, QVector<Relation *> *> XmlDB::fillTables()
{
    return readXmlFile(filePath);
}





void XmlDB::save(QVector<Table *> *tables)
{
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        qDebug() << "Error: File not saved";
        return;
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
            xmlWriter.writeStartElement("DisplayParams");
            xmlWriter.writeAttribute("displayMode", displayModeToString(DisplayMode(j)));
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

    file.close();
}
