#include "c_main_window.h"

#include <QHBoxLayout>
#include <QKeyEvent>

//------------------------------------------------------------------------------
CMainWindow::CMainWindow() :
    area_widget_( this )
{
    QHBoxLayout *layout( new QHBoxLayout );
    layout->addWidget( &area_widget_ );
    setLayout( layout );

    setWindowTitle(tr("Hello GL"));
}

//------------------------------------------------------------------------------
CMainWindow::~CMainWindow()
{
}

//------------------------------------------------------------------------------
void
CMainWindow::setArea( const wildstar::data::area::CArea* area )
{
    area_widget_.setArea( area );
}

//------------------------------------------------------------------------------
void
CMainWindow::keyPressEvent( QKeyEvent *e )
{
    if ( e->key() == Qt::Key_Escape )
        close();
    else
        QWidget::keyPressEvent( e );
}

//------------------------------------------------------------------------------
