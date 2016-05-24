#include <QDebug>
#include <QFile>
#include <QJsonObject>

#include "jsondocumentwriter.h"

JsonDocumentWriter::JsonDocumentWriter() noexcept
{
}

int JsonDocumentWriter::writeOutputFile (QString outputFile, QVariantMap outputData)
{
    QFile file {outputFile};

    if (!file.open (QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Error opening the file " << outputFile << ". " << file.errorString();
        auto error = file.error();
        file.close();
        return error;
    }

    auto jsonObject = getJsonObject(outputData);
    file.write (QJsonDocument {jsonObject}.toJson());

    file.close();

    return 0;
}

QJsonObject JsonDocumentWriter::getJsonObject(QVariantMap variantMap)
{
    QJsonObject jsonObject;
    for (auto it = variantMap.cbegin(); it != variantMap.cend(); ++it)
    {
        jsonObject.insert (it.key(), QJsonValue::fromVariant (it.value()));
    }
    return jsonObject;
}
