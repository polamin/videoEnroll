#ifndef MY_QLABEL_H
#define MY_QLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>
#include <QPixmap>

class my_qlabel : public QLabel
{
    Q_OBJECT
public:
    explicit my_qlabel(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *);
    void mouseReleaseEvent(QMouseEvent *ev);
    int x,y;

signals:
    void Mouse_Pressed(int,int);
    void Mouse_Pos(QString,int,int);
    void Mouse_Left(QString);
    void Mouse_Released(QString);


public slots:

};

#endif // MY_QLABEL_H
