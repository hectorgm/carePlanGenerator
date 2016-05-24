#ifndef CAREPLANGENERATOR_H
#define CAREPLANGENERATOR_H

#include <QList>

#include "issue.h"

class CarePlanGenerator
{
public:
    CarePlanGenerator() noexcept;
    CarePlanGenerator (QString inputFile) noexcept;

    QList<Issue> generateIssueList (QString inputFile) noexcept;

    void issueListToFile (QString outputFile) noexcept;

    QList<Issue> getIssueList() const noexcept;

    QList<QString> getIssueNameList() const noexcept;

    Issue getIssue (QString issueName) const noexcept;

    void addIssue (QString issueName, QString issueDescription) noexcept;

    bool containsIssue (QString issueName) const noexcept;

    void updateIssue (QString oldIssueName, QString newIssueName, QString newDescription) noexcept;

    void deleteIssue (QString issueName) noexcept;

private:
    QList<Issue> issueList;
};

#endif // CAREPLANGENERATOR_H
