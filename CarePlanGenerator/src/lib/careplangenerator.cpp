#include "careplangenerator.h"

#include <QVariantMap>

#include "jsondocumentreader.h"
#include "jsondocumentwriter.h"

CarePlanGenerator::CarePlanGenerator() noexcept
    : issueList()
{
}


CarePlanGenerator::CarePlanGenerator (QString inputFile) noexcept
    : issueList()
{
    issueList = generateIssueList (inputFile);
}


QList<Issue> CarePlanGenerator::generateIssueList (QString inputFile) noexcept
{
    auto jsonDocumentReader = JsonDocumentReader();
    auto errorNum = jsonDocumentReader.parseFile(inputFile);

    issueList.clear();

    if (errorNum != 0)
        return issueList;

    auto variantMap = jsonDocumentReader.getVariantMap ();

    for (auto i = variantMap.cbegin(); i != variantMap.cend(); ++i)
    {
        auto issue = Issue(i.key(), i.value().toString());
        issueList.push_back(issue);
    }

    return issueList;
}

void CarePlanGenerator::issueListToFile (QString outputFile) noexcept
{
    QVariantMap variantMap;

    for (auto issue : issueList)
    {
        variantMap.insert(issue.getName(), issue.getDescription());
    }

    auto jsonDocumentWriter = JsonDocumentWriter();
    jsonDocumentWriter.writeOutputFile(outputFile, variantMap);
}

QList<Issue> CarePlanGenerator::getIssueList() const noexcept
{
    return issueList;
}

QList<QString> CarePlanGenerator::getIssueNameList() const noexcept
{
    QList<QString> nameList;
    for (auto issue : issueList)
    {
        nameList.append(issue.getName());
    }

    return nameList;
}

Issue CarePlanGenerator::getIssue (QString issueName) const noexcept
{
    for (auto issue : issueList)
    {
        if (issue.getName().compare(issueName) == 0)
        {
            return issue;
        }
    }
    return Issue(issueName, QString());
}

void CarePlanGenerator::addIssue (QString issueName, QString issueDescription) noexcept
{
    auto issue = Issue(issueName, issueDescription);
    issueList.append(issue);
}

bool CarePlanGenerator::containsIssue (QString issueName) const noexcept
{
    for (auto issue : issueList)
    {
        if (issue.getName().compare(issueName) == 0)
        {
            return true;
        }
    }
    return false;
}

void CarePlanGenerator::updateIssue (QString oldIssueName, QString newIssueName, QString newDescription) noexcept
{
    auto issue = getIssue(oldIssueName);
    issue.setName(newIssueName);
    issue.setDescription(newDescription);
}

void CarePlanGenerator::deleteIssue (QString issueName) noexcept
{
    issueList.removeOne (getIssue (issueName));
}
