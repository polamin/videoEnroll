#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::string video_path;
    int frame_count;
    bool stop_all;
    bool clicked = false;
    int originX;
    int originY;
    int finalX;
    int finalY;
    QPixmap imgInLabel;

private slots:
    void Mouse_current_pos();
    void Mouse_Pressed();
    void Mouse_left();
    void Mouse_Released();
    void on_pushButton_clicked();
    void on_btPlay_clicked();
    void delay(int millisecondsToWait);

    void on_horizontalScrollBar_sliderReleased();
    void on_horizontalScrollBar_sliderPressed();
    void stopProcess();
    void DrawRec();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
