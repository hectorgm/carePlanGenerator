#include "issuenamevalidator.h"

IssueNameValidator::IssueNameValidator (QList<QString> invalidNames, QObject *parent) :
    QValidator (parent),
    invalidNames (invalidNames)
{
}

QValidator::State IssueNameValidator::validate (QString &input, int & /*pos*/) const
{
    if (input.isEmpty())
    {
        return QValidator::Intermediate;
    }

    for (QString name : invalidNames)
    {
        if (input.compare(name) == 0)
        {
            return QValidator::Intermediate;
        }
    }

    return QValidator::Acceptable;
}
