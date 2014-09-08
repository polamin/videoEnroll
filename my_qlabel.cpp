#include "my_qlabel.h"
#include <QLabel>
#include <QPixmap>
#include <QDebug>

my_qlabel::my_qlabel(QWidget *parent) :
    QLabel(parent)
{

}

void my_qlabel::mouseMoveEvent(QMouseEvent *ev)
{
    x     =   ev->x();
    y     =   ev->y();
    emit Mouse_Pos(this->objectName(),x,y);

}

void my_qlabel::mousePressEvent(QMouseEvent *ev)
{
    x     =   ev->x();
    y     =   ev->y();
    emit Mouse_Pressed(x,y);
}

void my_qlabel::leaveEvent(QEvent *ev)
{
    emit Mouse_Left(this->objectName());
}

void my_qlabel::mouseReleaseEvent(QMouseEvent *ev)
{
    emit Mouse_Released(this->objectName());
}


