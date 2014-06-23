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
    void testCurrentIndexFiles();
    void testCurrentIndexFiles_data();
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

void TestCPackage::testCurrentIndexFiles()
{
    //QBuffer buffer;
    //const char data[] = {};
    //buffer.setData( data, sizeof( data ) );

    QFETCH( QString, file_name );
    QFETCH( quint32, block_count );
    CPackage pack;
    pack.open( file_name );
    QCOMPARE( pack.getBlockCount(), block_count );

    //QFETCH(QString, data);
    //QVERIFY2(true, "Failure");
}

void TestCPackage::testCurrentIndexFiles_data()
{
    QTest::addColumn<QString>( "file_name" );
    QTest::addColumn<quint32>( "block_count" );
    QTest::newRow("0")  << ":/misc/Client64.index"  << 3u;
    QTest::newRow("1")  << ":/misc/Patch.index"     << 3u;
}

QTEST_APPLESS_MAIN(TestCPackage)

#include "test_c_package.moc"
