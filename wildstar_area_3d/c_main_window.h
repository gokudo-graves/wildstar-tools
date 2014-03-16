#ifndef C_MAIN_WINDOW_H
#define C_MAIN_WINDOW_H

#include <QMainWindow>

#include "c_area_widget.h"

class CMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CMainWindow();
    virtual ~CMainWindow();

    virtual void setArea( const wildstar::data::area::CArea* area );

protected:
    void keyPressEvent( QKeyEvent *event );

private:
    CAreaWidget     area_widget_;
};

#endif // C_MAIN_WINDOW_H
