#include "XmlDB.h"

#include <QObject>
#include <QDebug>

XmlDB::XmlDB(QString fp) : filePath(fp)
{
    readXmlFile(filePath);
    fields.clear();
    rows.clear();
}

void XmlDB::readXmlFile(QString path)
{
    QFile* file = new QFile(path);

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text) )
    {
       //qDebug() << "Error: File not open";
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
                //qDebug() << "[Database]: ";
                int numOfTables = xmlReader.attributes().value("tablesCount").toString().toInt();

                xmlReader.readNext();

                int accessMode = xmlReader.attributes().value("accessMode").toString().toInt();

                //xmlReader.readNext();

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
        //qDebug() << "Called XML parseQuestionElement "
        //         << "without a question Element in the XML stream!";

        return;
    }

    Table* tb = new Table();

    //set table's name
    QString tName = xmlReader.attributes().value("name").toString();
    tb->setName(tName);
    //qDebug() << "tables name" << tb->getName();

    //set counts of fields and rows
    int countOfFields = xmlReader.attributes().value("fieldsCount").toString().toInt();
    int countOfRows = xmlReader.attributes().value("rowsCount").toString().toInt();
    tb->setFieldsAndRows(countOfFields, countOfRows);
    //qDebug() << "get counts" << tb->getFieldsCount() << tb->getRowsCount();

    //set table's model size
    int current = 0;
    QStandardItemModel* model = new QStandardItemModel(countOfRows, 2);
    QStandardItemModel* model2 = new QStandardItemModel(countOfRows, countOfFields);

    //set table's coords
    int xCoord = xmlReader.attributes().value("xCoord").toString().toInt();
    int yCoord = xmlReader.attributes().value("yCoord").toString().toInt();
    tb->setCoord(xCoord, yCoord);
    //qDebug() << "get coords" << tb->getCoordX() << tb->getCoordY();

    //set table's resize
    int width = xmlReader.attributes().value("width").toString().toInt();
    int height = xmlReader.attributes().value("heigh").toString().toInt();
    tb->setResize(width, height);
    //qDebug() << "get resize" << tb->getWidth() << tb->getHeight();

    //xmlReader.readNext();

    while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement
            && xmlReader.name() == "Table"))
    {
        if(xmlReader.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xmlReader.name() == "Fields")
            {
                for(int i = 0; i < xmlReader.attributes().size(); i++)
                {
                    model->setItem(i, 0, new QStandardItem(xmlReader.attributes().at(i).name().toString())  );
                    model->setItem(i, 1, new QStandardItem(xmlReader.attributes().at(i).value().toString()) );
                    ////qDebug() << xmlReader.attributes().at(i).name() << xmlReader.attributes().at(i).value();
                }
                tb->setFieldsModel(model);
            }



            if(xmlReader.name() == "Row")
            {
                //int c = 0;
//                for(int i = 0; i < countOfRows; i++)
//                {
                    for(int j = 0; j < countOfFields; j++)
                    {
                        model2->setItem(current, j, new QStandardItem(xmlReader.attributes().at(j).value().toString())  );



                        //model->setItem(i, 1, new QStandardItem(xmlReader.attributes().at(i).value().toString()) );
                        //rows << xmlReader.attributes().at(i).value().toString();
                        ////qDebug() << xmlReader.attributes().at(i).name() << xmlReader.attributes().at(i).value();

                    }
                    ++current;
                    //c++;
//                }

                tb->setRowsModel(model2);
            }
            fillModel(tb, fields, rows);
        }
        xmlReader.readNext();
    }

    tables << tb;

    return;

}

void XmlDB::parseField(QXmlStreamReader &)
{

}

void XmlDB::fillModel(Table* tb, QStringList& fields, QStringList& rows)
{
    //qDebug() << "Here we are";
//    for(int i = 0; i < fields.size(); i++)
//    {
//        for(int j = 0; j < rows.size(); j++)
//        {
//            ////qDebug() << i << j << fields[i] << rows[j];
//        }
//    }

    //tb->getModel()->setItem(0, 0, new QStandardItem(rows[0]));
    //tb->getModel()->setItem(0, 1, new QStandardItem(rows[1]));
    //tb->getModel()->setItem(1, 0, new QStandardItem(rows[2]));
    //tb->model->setItem(1, 1, new QStandardItem(rows[3]));
}

QVector<Table *>* XmlDB::fillTables(DisplayMode m, QVector<Table *> *tables)
{
    return &(this->tables);
}
