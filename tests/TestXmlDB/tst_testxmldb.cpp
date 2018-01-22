#include <QtTest>

#include "XmlDB.h"
#include "Table.h"

class TestXmlDB : public QObject
{
    Q_OBJECT

public:
    TestXmlDB();
    ~TestXmlDB();

private slots:
    void initTestCase();
    void save();
    void cleanupTestCase();

private:
    const QString testFileName = "wellFormedTest.xml";
    QVector<Table*> testTables; // store data from testFileName
};

TestXmlDB::TestXmlDB()
{
}

TestXmlDB::~TestXmlDB()
{

}

void TestXmlDB::initTestCase()
{
    testTables.reserve(2);

    Table *table = new Table;
    QStandardItemModel *fieldsModel = new QStandardItemModel(2, 2);
    QStandardItemModel *objectsModel = new QStandardItemModel(2, 2);

    fieldsModel->setItem(0, 0, new QStandardItem(QString("Name")));
    fieldsModel->setItem(0, 1, new QStandardItem(QString("String")));
    fieldsModel->setItem(1, 0, new QStandardItem(QString("id")));
    fieldsModel->setItem(1, 1, new QStandardItem(QString("int")));

    objectsModel->setItem(0, 0, new QStandardItem(QString("Alex")));
    objectsModel->setItem(0, 1, new QStandardItem(QString("1")));
    objectsModel->setItem(1, 0, new QStandardItem(QString("Kolya")));
    objectsModel->setItem(1, 1, new QStandardItem(QString("2")));

    table->setName(QString("Workers"));
    table->setFieldsModel(fieldsModel);
    table->setObjectsModel(objectsModel);

/* need to fix display mode in test case
    table->setGeometry(QRect(5, 19, 100, 37), CLASSES);
    table->setGeometry(QRect(57, 23, 100, 100), FIELDS);
    table->setGeometry(QRect(61, 43, 143, 300), OBJECTS);
*/
    testTables << table;

    table = new Table;
    fieldsModel = new QStandardItemModel(2, 2);
    objectsModel = new QStandardItemModel(2, 2);

    fieldsModel->setItem(0, 0, new QStandardItem(QString("WorkerId")));
    fieldsModel->setItem(0, 1, new QStandardItem(QString("int")));
    fieldsModel->setItem(1, 0, new QStandardItem(QString("post")));
    fieldsModel->setItem(1, 1, new QStandardItem(QString("string")));

    objectsModel->setItem(0, 0, new QStandardItem(QString("1")));
    objectsModel->setItem(0, 1, new QStandardItem(QString("CEO")));
    objectsModel->setItem(1, 0, new QStandardItem(QString("2")));
    objectsModel->setItem(1, 1, new QStandardItem(QString("Manager")));

    table->setName(QString("Aassignments"));
    table->setFieldsModel(fieldsModel);
    table->setObjectsModel(objectsModel);

 /* need to fix display mode in test case
    table->setGeometry(QRect(25, 19, 100, 37), CLASSES);
    table->setGeometry(QRect(90, 23, 100, 100), FIELDS);
    table->setGeometry(QRect(110, 43, 143, 300), OBJECTS);
*/
    testTables << table;
}

void TestXmlDB::save()
{
    QString actualFileName("savedFile.xml");
    QFile expectedFile(testFileName);
    QFile actualFile(actualFileName);
    XmlDB xmlDB(actualFileName);

    xmlDB.save(&testTables);

    if (!expectedFile.open(QIODevice::ReadOnly | QIODevice::Text))
        QFAIL(QString("Can't open file %1")
                                        .arg(testFileName).toLatin1().data());

    if (!actualFile.open(QIODevice::ReadOnly | QIODevice::Text))
        QFAIL("Can't open saved file");

    QTextStream expectedStream(&expectedFile);
    QTextStream actualStream(&actualFile);
    int lineNumber = 1;
    /*
    while(!expectedStream.atEnd())
    {
        QString actualFileLine = actualStream.readLine();
        QString expectedFileLine = expectedStream.readLine();
        QVERIFY2(actualFileLine == expectedFileLine, QString("error at line %1 "
                                             "Actual: %2 "
                                             "Expected: %3")
                                             .arg(lineNumber)
                                             .arg(actualFileLine)
                                             .arg(expectedFileLine)
                                             .toLatin1().data());

        lineNumber++;
    }
*/

    actualFile.remove();
    expectedFile.close();
    QFile::remove(actualFileName);
}

void TestXmlDB::cleanupTestCase()
{
    foreach (Table *t, testTables)
        delete t;

}

QTEST_APPLESS_MAIN(TestXmlDB)

#include "tst_testxmldb.moc"
