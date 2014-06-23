#include <QString>
#include <QtTest>

class TestCArchiveIndex : public QObject
{
    Q_OBJECT

public:
    TestCArchiveIndex();

private Q_SLOTS:
    void testCase1();
};

TestCArchiveIndex::TestCArchiveIndex()
{
}

void TestCArchiveIndex::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestCArchiveIndex)

#include "test_c_archive_index.moc"
