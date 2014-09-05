#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPixmap>
#include <vector>
#include "video_data.h"
#include "video_reader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    QString object_name_filter;
    int originX;
    int originY;
    int finalX;
    int finalY;
    bool stop_all;
    bool clicked = false;
    int frame_count;
    bool person1_label_set = false;
    QPixmap person1;
    QPixmap person2;
    vector<video_data>  videoes_data;
    vector<VideoReader> videoes_reader;

private slots:
    void Mouse_current_pos(QString);
    void Mouse_Pressed(QString);
    void Mouse_left(QString);
    void Mouse_Released(QString);
    void on_pushButton_clicked();
    void on_btPlay_clicked();
    void delay(int millisecondsToWait);

    void on_horizontalScrollBar_sliderReleased();
    void on_horizontalScrollBar_sliderPressed();
    void stopProcess();
    void DrawRec(QString);
    void update_Person(int startX,int startY,int width,int height);


    void on_btPause_clicked();


    void on_btReidentificate_clicked();
};

#endif // MAINWINDOW_H
