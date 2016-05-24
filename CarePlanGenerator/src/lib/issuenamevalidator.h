#ifndef ISSUENAMEVALIDATOR_H
#define ISSUENAMEVALIDATOR_H

#include <QValidator>

class IssueNameValidator : public QValidator
{
    Q_OBJECT
public:
   explicit IssueNameValidator (QList<QString> invalidNames, QObject *parent = 0);

   QValidator::State validate (QString& input, int& pos) const;

private:
   QList<QString> invalidNames;
};

#endif // ISSUENAMEVALIDATOR_H
