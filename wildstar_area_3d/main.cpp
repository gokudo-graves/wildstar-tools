#include <QDebug>

#include <QApplication>
#include <QDataStream>
#include <QFile>

#include "wildstar/data/area/c_area.h"
#include "c_main_window.h"

using wildstar::data::area::CArea;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMainWindow w;
    QFile area_file( a.arguments().at( 1 ) );
    area_file.open( QIODevice::ReadOnly );

    QDataStream stream( &area_file );
    stream.setByteOrder( QDataStream::LittleEndian );

    CArea area;
    area.read( stream );

    qDebug() << area_file.fileName();
    w.setArea( &area );

    w.show();
    return a.exec();
}
