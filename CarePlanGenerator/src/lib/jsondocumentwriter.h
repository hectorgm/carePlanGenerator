#ifndef JSONDOCUMENTWRITER_H
#define JSONDOCUMENTWRITER_H

#include <QJsonDocument>

#include "documentwriter.h"

class JsonDocumentWriter : public DocumentWriter
{
public:
    JsonDocumentWriter() noexcept;
    virtual ~JsonDocumentWriter() = default;

    int writeOutputFile (QString outputFile, QVariantMap outputData) override;

private:
    QJsonObject getJsonObject (QVariantMap variantMap);
};

#endif // JSONDOCUMENTWRITER_H
