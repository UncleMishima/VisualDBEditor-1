#include "AbstractDB.h"
#include "XmlDB.h"

AbstractDB::AbstractDB()
{

}

AbstractDB *AbstractDB::openConnection(DBType type,
                                       QStringList options,
                                       uint flags)
{
    switch (type)
    {
        case XML_FILE:
            return new XmlDB(options.first());

        default:
            return nullptr;
    }
}

