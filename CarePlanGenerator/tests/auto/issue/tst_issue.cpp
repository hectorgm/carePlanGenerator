#include <QtTest>

#include "issue.h"

class IssueTest : public QObject
{
    Q_OBJECT

public:
    IssueTest();
    ~IssueTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testIssueComparison();
    void testIssueName();
    void testIssueDescription();
};

IssueTest::IssueTest()
{

}

IssueTest::~IssueTest()
{

}

void IssueTest::initTestCase()
{

}

void IssueTest::cleanupTestCase()
{

}

void IssueTest::testIssueComparison()
{
    auto issue1 = Issue("Name", "Description");
    auto issue2 = Issue("Name", "Description");

    QVERIFY2 (issue1 == issue2, "Failure in issue comparison test");
}

void IssueTest::testIssueName()
{
    auto issue = Issue();
    QString name ("Name");
    issue.setName (name);

    QVERIFY2 (issue.getName() == name, "Failure in issue name test");
}

void IssueTest::testIssueDescription()
{
    auto issue = Issue();
    QString description ("Description");
    issue.setDescription (description);

    QVERIFY2 (issue.getDescription() == description, "Failure in issue description test");
}

QTEST_MAIN (IssueTest)

#include "tst_issue.moc"
