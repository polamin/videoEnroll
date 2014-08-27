#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include "video_reader.h"
#include "my_qlabel.h"
#include "qdebug.h"
#include <opencv2/opencv.hpp>


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

    string video_path = "/Users/polaminsinghasuwich/Documents/20140804_112403.mkv";
    VideoReader video(video_path);
    int frameCount = 0;
    while (1)
    {
        cv::Mat frame2 = video.get_current_frame();
        if (frame2.empty())
        {
            break;
        }
        frameCount++;

        cv::Mat frame;
        cv::Size size(640,480);
        cv::resize(frame2,frame,size);
        cv::cvtColor(frame,frame,CV_BGR2RGB);
        QPixmap  imgInLabel = QPixmap::fromImage(QImage((unsigned char*) frame.data,
                                                        frame.cols,
                                                        frame.rows,
                                                        QImage::Format_RGB888));

        ui->lbVideo1->setPixmap(imgInLabel);
        ui->lbVideo1->show();
    }
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


