#ifndef C_MAIN_WINDOW_H
#define C_MAIN_WINDOW_H

#include <QWindow>
#include <QTime>

class AbstractScene;

class QOpenGLContext;

class CMainWindow : public QWindow
{
    Q_OBJECT

public:
    CMainWindow( QScreen* screen = 0 );

    virtual void setArea( const wildstar::data::area::CArea* area );

private:
    void initializeGL();

protected slots:
    void resizeGL();
    void paintGL();
    void updateScene();

protected:
    void keyPressEvent( QKeyEvent* e );
    void keyReleaseEvent( QKeyEvent* e );
    void mousePressEvent( QMouseEvent* e );
    void mouseReleaseEvent( QMouseEvent* e );
    void mouseMoveEvent( QMouseEvent* e );

private:
    QOpenGLContext* m_context;
    AbstractScene* m_scene;
    bool m_leftButtonPressed;
    QPoint m_prevPos;
    QPoint m_pos;
    QTime m_time;
    CAreaWidget     area_widget_;
};

#endif // C_MAIN_WINDOW_H
