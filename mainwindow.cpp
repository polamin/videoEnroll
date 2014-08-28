#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include "video_reader.h"
#include "my_qlabel.h"
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lbVideo1,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_current_pos()));
    connect(ui->lbVideo1,SIGNAL(Mouse_Pressed()),this,SLOT(Mouse_Pressed()));
    connect(ui->lbVideo1,SIGNAL(Mouse_Left()),this,SLOT(Mouse_left()));
    connect(ui->lbVideo1,SIGNAL(Mouse_Released()),this,SLOT(Mouse_Released()));
    connect(ui->lbVideo2,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_current_pos()));
    connect(ui->lbVideo2,SIGNAL(Mouse_Pressed()),this,SLOT(Mouse_Pressed()));
    connect(ui->lbVideo2,SIGNAL(Mouse_Left()),this,SLOT(Mouse_left()));
    connect(ui->lbVideo2,SIGNAL(Mouse_Released()),this,SLOT(Mouse_Released()));
    connect(ui->lbVideo3,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_current_pos()));
    connect(ui->lbVideo3,SIGNAL(Mouse_Pressed()),this,SLOT(Mouse_Pressed()));
    connect(ui->lbVideo3,SIGNAL(Mouse_Left()),this,SLOT(Mouse_left()));
    connect(ui->lbVideo3,SIGNAL(Mouse_Released()),this,SLOT(Mouse_Released()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_btPlay_clicked()
{
    video_path = "/media/polamin/ad73bd2e-e1ca-4fd1-a5b3-08b598c6e14b/IDMI/20140804_112403.mkv";
    VideoReader video(video_path);
    frame_count = 0;


    cv::Mat frame;
    cv::Size size(640,480);

    qDebug() << video.get_video_length();
    ui->horizontalScrollBar->setMaximum(video.get_video_length());


    while (1)
    {
        video.set_video_index(frame_count);
        cv::Mat frame2 = video.get_current_frame();
        if (frame2.empty())
        {
            break;
        }
        frame_count++;
        ui->horizontalScrollBar->setValue(frame_count);


        cv::resize(frame2,frame,size);
        cv::cvtColor(frame,frame,CV_BGR2RGB);
        QPixmap  imgInLabel = QPixmap::fromImage(QImage((unsigned char*) frame.data,
                                                        frame.cols,
                                                        frame.rows,
                                                        QImage::Format_RGB888));

        ui->lbVideo1->setPixmap(imgInLabel);
        ui->lbVideo1->show();



        delay(25);
    }


}

void MainWindow::Mouse_Released()
{
}

void MainWindow::Mouse_current_pos()
{

    //finalX = ui->lblMouse->x;
    //finalY = ui->lblMouse->y;

}


void MainWindow::Mouse_Pressed()
{
    //qDebug("abc");

}

void MainWindow::Mouse_left()
{

}

void MainWindow::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}





void MainWindow::on_horizontalScrollBar_sliderReleased()
{
    frame_count = ui->horizontalScrollBar->value();
    stop_all    = false;
}

void MainWindow::on_horizontalScrollBar_sliderPressed()
{
    stop_all = true;
    stopProcess();
}


void MainWindow::stopProcess()
{
    while (1)
    {
        if (stop_all)
            delay(100);
        else
            break;
    }
}
