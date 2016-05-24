#include <QtTest>

#include "issuenamevalidator.h"

class IssueNameValidatorTest : public QObject
{
    Q_OBJECT

public:
    IssueNameValidatorTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testInvalidValue();
    void testValidValue();

private:
    QList <QString> invalidNames;
};

IssueNameValidatorTest::IssueNameValidatorTest()
{
}

void IssueNameValidatorTest::initTestCase()
{
    invalidNames = {"Name1", "Name2", "Name3", "Name4"};
}

void IssueNameValidatorTest::cleanupTestCase()
{
}

void IssueNameValidatorTest::testInvalidValue()
{
    IssueNameValidator validator (invalidNames);
    int pos {0};
    auto validation = validator.validate (invalidNames[0], pos);

    QVERIFY2 (validation == QValidator::Intermediate, "Failure in invalid value test");
}

void IssueNameValidatorTest::testValidValue()
{
    IssueNameValidator validator (invalidNames);
    QString name {"Valid name"};
    int pos {0};
    auto validation = validator.validate (name, pos);

    QVERIFY2 (validation == QValidator::Acceptable, "Failure in valid value test");
}

QTEST_MAIN(IssueNameValidatorTest)

#include "tst_issuenamevalidatortest.moc"
