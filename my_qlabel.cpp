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

    this->x     =   ev->x();
    this->y     =   ev->y();
    emit Mouse_Pos(this->objectName());

}

void my_qlabel::mousePressEvent(QMouseEvent *ev)
{
    emit Mouse_Pressed(this->objectName());
}

void my_qlabel::leaveEvent(QEvent *ev)
{
    emit Mouse_Left(this->objectName());
}

void my_qlabel::mouseReleaseEvent(QMouseEvent *ev)
{
    emit Mouse_Released(this->objectName());
}


