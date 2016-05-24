#ifndef JSONDOCUMENTREADER_H
#define JSONDOCUMENTREADER_H

#include <QJsonDocument>

#include "documentreader.h"

class JsonDocumentReader : public DocumentReader
{
public:
    JsonDocumentReader() noexcept;
    virtual ~JsonDocumentReader() = default;

    int parseFile (QString inputFile) override;

    QVariantMap getVariantMap (QString key) override;
    QVariantMap getVariantMap() override;
    QVariantHash getVariantHash (QString key) override;
    QVariantHash getVariantHash() override;

private:
    QJsonDocument jsonDocument;

    QJsonValue getJsonValue (QString key);
};

#endif // JSONDOCUMENTREADER_H
