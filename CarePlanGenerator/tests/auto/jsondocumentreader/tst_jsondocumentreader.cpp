#include <QtTest>

#include "jsondocumentreader.h"

class JsonDocumentReaderTest : public QObject
{
    Q_OBJECT

public:
    JsonDocumentReaderTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testReadValidFile();
    void testReadInvalidFile();
};

JsonDocumentReaderTest::JsonDocumentReaderTest()
{
}

void JsonDocumentReaderTest::initTestCase()
{
}

void JsonDocumentReaderTest::cleanupTestCase()
{
}

void JsonDocumentReaderTest::testReadValidFile()
{
    auto jsonDocumentReader = JsonDocumentReader();
    auto errorNum = jsonDocumentReader.parseFile("validFile.json");
    QVERIFY2(errorNum == 0, "Failure in read valid test");
}

void JsonDocumentReaderTest::testReadInvalidFile()
{
    auto jsonDocumentReader = JsonDocumentReader();
    auto errorNum = jsonDocumentReader.parseFile("invalidFile.json");
    QVERIFY2(errorNum == 1, "Failure in read valid test");
}

QTEST_APPLESS_MAIN(JsonDocumentReaderTest)

#include "tst_jsondocumentreader.moc"
