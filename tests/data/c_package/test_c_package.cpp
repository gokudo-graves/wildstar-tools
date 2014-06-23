#include <QString>
#include <QtTest>

#include <wildstar/data/c_package.h>

using wildstar::data::CPackage;

class TestCPackage : public QObject
{
    Q_OBJECT

public:
    TestCPackage();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase1_data();
};

TestCPackage::TestCPackage()
{
}

void TestCPackage::initTestCase()
{
}

void TestCPackage::cleanupTestCase()
{
}

void TestCPackage::testCase1()
{
    QBuffer buffer;
    const char data[] = {};
    buffer.setData( data, sizeof( data ) );

    CPackage pack;
    pack.open( buffer );

    //QFETCH(QString, data);
    //QVERIFY2(true, "Failure");
}

void TestCPackage::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_APPLESS_MAIN(TestCPackage)

#include "test_c_package.moc"
