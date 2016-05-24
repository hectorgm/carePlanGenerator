#include "jsondocumentreader.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>
#include <QDir>

JsonDocumentReader::JsonDocumentReader() noexcept
    : jsonDocument()
{
}

int JsonDocumentReader::parseFile (QString inputFile)
{
    QFile file(inputFile);

    if (!file.exists())
    {
        qDebug() << "The file " << inputFile << " doesn't exists in " << QDir::currentPath();
        file.close();
        return 1;
    }
    if (!file.open (QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error opening the file " << inputFile << ". " << file.errorString();
        auto error = file.error();
        file.close();
        return error;
    }

    QJsonParseError jsonParseError;
    jsonDocument = QJsonDocument::fromJson (file.readAll(), &jsonParseError);
    file.close();

    if (jsonParseError.error != QJsonParseError::NoError)
    {
        qDebug() << "Error parsing JSON:" << jsonParseError.errorString();
        return 1;
    }

    if (!jsonDocument.isObject())
    {
        qDebug() << "The JSON data is not an object";
        return 1;
    }

    return 0;
}

QJsonValue JsonDocumentReader::getJsonValue (QString key)
{
    QJsonValue jsonValue;
    if (!jsonDocument.isObject())
    {
        qDebug() << "The JSON document loaded is not an object";
        return jsonValue;
    }

    jsonValue = jsonDocument.object().value (key);
    if (jsonValue.isUndefined())
    {
        qDebug() << "Key not found on JSON document";
        return jsonValue;
    }

    return jsonValue;
}

QVariantMap JsonDocumentReader::getVariantMap (QString key)
{
    QJsonValue jsonValue = getJsonValue (key);

    if (!jsonValue.isObject())
    {
        qDebug() << "The key is not an object in the JSON document";
        return QVariantMap();
    }

    return jsonValue.toObject().toVariantMap();
}

QVariantMap JsonDocumentReader::getVariantMap ()
{
    return jsonDocument.object().toVariantMap();
}

QVariantHash JsonDocumentReader::getVariantHash (QString key)
{
    QJsonValue jsonValue = getJsonValue (key);

    if (!jsonValue.isObject())
    {
        qDebug() << "The key is not an object in the JSON document";
        return QVariantHash();
    }

    return jsonValue.toObject().toVariantHash();
}

QVariantHash JsonDocumentReader::getVariantHash ()
{
    return jsonDocument.object().toVariantHash();
}


