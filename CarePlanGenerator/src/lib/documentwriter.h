#ifndef DOCUMENTWRITER_H
#define DOCUMENTWRITER_H

#include <QVariantMap>

class DocumentWriter
{
public:
    DocumentWriter() noexcept;
    virtual ~DocumentWriter() = default;

    virtual int writeOutputFile (QString fileName, QVariantMap outputData) = 0;
};

#endif // DOCUMENTWRITER_H
