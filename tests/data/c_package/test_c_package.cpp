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
    void testFiles();
    void testDevice();
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

void TestCPackage::testFiles()
{
    CPackage pack;
    pack.read( ":/misc/minimal.pack" );
    QCOMPARE( pack.getBlockCount(), 1u );
    QCOMPARE( pack.readTypeBlock(), QByteArray() );
    QCOMPARE( pack.readBlock( 0 ), QByteArray() );

    pack.read( ":/misc/small.pack" );
    QCOMPARE( pack.getBlockCount(), 3u );
    QCOMPARE( pack.readTypeBlock().data(), "Type Block" );
    QCOMPARE( pack.readBlock( 0 ).data(), "" );
    QCOMPARE( pack.readBlock( 1 ).data(), "Data Block 1" );
    QCOMPARE( pack.readBlock( 2 ), pack.readTypeBlock() );
}

void TestCPackage::testDevice()
{
    CPackage pack;
    pack.read( new QFile( ":/misc/small.pack" ) );
    QCOMPARE( pack.getBlockCount(), 3u );
    QCOMPARE( pack.readTypeBlock().data(), "Type Block" );
    QCOMPARE( pack.readBlock( 0 ).data(), "" );
    QCOMPARE( pack.readBlock( 1 ).data(), "Data Block 1" );
    QCOMPARE( pack.readBlock( 2 ), pack.readTypeBlock() );
}

/*
    //QFETCH(QString, data);
    //QVERIFY2(true, "Failure");
void TestCPackage::testCurrentIndexFiles_data()
{
    QTest::addColumn<quint32>( "block_count" );
    QTest::addColumn<QString>( "file_name" );
    QTest::newRow("0") << 3u << ":/misc/minimal.pack";
    QTest::newRow("1") << 3u << ":/misc/small.pack";
}
*/

QTEST_APPLESS_MAIN(TestCPackage)

#include "test_c_package.moc"
