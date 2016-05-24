#ifndef DOCUMENTREADER_H
#define DOCUMENTREADER_H

#include <QVariantMap>
#include <QVariantHash>

class DocumentReader
{
public:
    DocumentReader() noexcept;
    virtual ~DocumentReader() = default;

    virtual int parseFile (QString filePath) = 0;

    virtual QVariantMap getVariantMap (QString key) = 0;
    virtual QVariantMap getVariantMap() = 0;
    virtual QVariantHash getVariantHash (QString key) = 0;
    virtual QVariantHash getVariantHash() = 0;
};

#endif // DOCUMENTREADER_H
