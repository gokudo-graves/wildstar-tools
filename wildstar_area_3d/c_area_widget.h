#ifndef C_AREA_WIDGET_H
#define C_AREA_WIDGET_H

#include <QGLWidget>

#include "wildstar/data/area/c_area.h"

class CAreaWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit CAreaWidget(QWidget *parent = 0);

    virtual ~CAreaWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    virtual void setArea( const wildstar::data::area::CArea* area );

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

private:
    int xRot;
    int yRot;
    int zRot;
    int xPos;
    int yPos;
    int zPos;
    QPoint lastPos;
    const wildstar::data::area::CArea* area_;
};

#endif // C_AREA_WIDGET_H
