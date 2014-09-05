#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include "video_reader.h"
#include "my_qlabel.h"
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <QTime>
#include <QPainter>
#include <QRubberBand>
#include <QProcess>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    videoes_data.push_back(video_data("/media/polamin/ad73bd2e-e1ca-4fd1-a5b3-08b598c6e14b/IDMI/dry.run.20140806.1/ICube_l1_Cam04_sync.mkv"));
    videoes_data.push_back(video_data("/media/polamin/ad73bd2e-e1ca-4fd1-a5b3-08b598c6e14b/IDMI/dry.run.20140806.1/ICube_l1_Cam05_sync.mkv"));
    videoes_data.push_back(video_data("/media/polamin/ad73bd2e-e1ca-4fd1-a5b3-08b598c6e14b/IDMI/dry.run.20140806.1/ICube_l1_Cam06_sync.mkv"));

    object_name_filter = "lbVideo";

    int videoes_count = 0;
    foreach (QLabel *label, findChildren<QLabel *>())
    {
        if(label->objectName().indexOf(object_name_filter) == -1)
            continue;
        connect(label,SIGNAL(Mouse_Pos(QString)),this,SLOT(Mouse_current_pos(QString)));
        connect(label,SIGNAL(Mouse_Pressed(QString)),this,SLOT(Mouse_Pressed(QString)));
        connect(label,SIGNAL(Mouse_Left(QString)),this,SLOT(Mouse_left(QString)));
        connect(label,SIGNAL(Mouse_Released(QString)),this,SLOT(Mouse_Released(QString)));
        videoes_data[videoes_count].object_name = object_name_filter + QString::number(videoes_count+1);
        videoes_count++;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btPlay_clicked()
{


    int vec_size = videoes_data.size();//vec_size keep how many video we use
    for (int i = 0 ; i < vec_size ; i++)
    {
        videoes_reader.push_back(videoes_data[i].get_video_path());
    }

    frame_count = 0;

    cv::Size size(640,480);

    qDebug() << videoes_reader[0].get_video_length();

    ui->horizontalScrollBar->setMaximum(videoes_reader[0].get_video_length());


    while (1)
    {
        cv::Mat frame[vec_size];
        //Get frame
        for (int i = 0 ; i < vec_size ; i++)
        {
             videoes_reader[i].set_video_index(frame_count);
             videoes_data[i].frame =  videoes_reader[i].get_current_frame();
        }

        if (videoes_data[0].frame.empty())
        {
            break;
        }
        frame_count++;
        ui->horizontalScrollBar->setValue(frame_count);

        //Change CV to Qt
        for (int i = 0 ; i < vec_size ; i++)
        {
            cv::resize(videoes_data[i].frame,frame[i],size);
            cv::cvtColor(frame[i],frame[i],CV_BGR2RGB);
            videoes_data[i].imgInLabel = QPixmap::fromImage(QImage((unsigned char*) frame[i].data,
                                                            frame[i].cols,
                                                            frame[i].rows,
                                                            QImage::Format_RGB888));
        }

        //Iterator for every label for change the image on them
        int i = 0;
        foreach (QLabel *label, findChildren<QLabel *>())
        {
            if(label->objectName().indexOf(object_name_filter) == -1)
                continue;
            label->setPixmap(videoes_data[i].imgInLabel);
            label->show();

            i++;
            if(i == vec_size)
                i = 0;
        }
        //End of iterator
        delay(5);
    }
}

void MainWindow::Mouse_Released(QString name)
{
    //DrawRec();
    clicked = false;

    int startX;
    int startY;
    //Find XY
    if(finalX < originX && finalY < originY)
    {
        startX = finalX;
        startY = finalY;
    }
    else if (finalX < originX && finalY > originY)
    {
        startX = finalX;
        startY = originY;
    }
    else if (finalX > originX && finalY < originY)
    {
        startX = originX;
        startY = finalY;
    }
    else if (finalX > originX && finalY > originY)
    {
        startX = originX;
        startY = originY;
    }

        int width = abs(finalX-originX);
        int height =  abs(finalY-originY);
        update_Person(startX,startY,width,height);
}


void MainWindow::update_Person(int startX,int startY,int width,int height)
{
    QPixmap pixmap = videoes_data[0].imgInLabel;

    QPixmap person = pixmap.copy(startX,startY,width,height);

    if(!person1_label_set)
    {
        person1 = person;
        ui->lbPerson1->setPixmap(person);
        ui->lbPerson1->show();
        person1_label_set = true;
    }
    else
    {
        person2 = person;
        ui->lbPerson2->setPixmap(person);
        ui->lbPerson2->show();
    }

}
void MainWindow::on_btReidentificate_clicked()
{
    QString img_path ="/media/polamin/ad73bd2e-e1ca-4fd1-a5b3-08b598c6e14b/1.png";
    QString img_path2 = "/media/polamin/ad73bd2e-e1ca-4fd1-a5b3-08b598c6e14b/2.png";
    QFile file(img_path);
    QFile file2(img_path2);
    file.open(QIODevice::WriteOnly);
    file2.open(QIODevice::WriteOnly);
    person1.save(&file, "PNG");
    person2.save(&file2, "PNG");

    QString exec_path = "/media/polamin/ad73bd2e-e1ca-4fd1-a5b3-08b598c6e14b/FYPREINDENTIFICATION/MatlabCode/sdalf/run_L_main_tagging_SvsS.sh ";
    QString matlab_path = "/usr/local/MATLAB/R2013a/ ";
    QProcess::execute (exec_path + matlab_path + img_path + " " + img_path2);
}


void MainWindow::Mouse_current_pos(QString name)
{
//    QLabel *label = findChild<QLabel*>(name);
    if(clicked)
    {

        DrawRec(name);
        finalX = ui->lbVideo1->x;
        finalY = ui->lbVideo1->y;

    }
}



void MainWindow::Mouse_Pressed(QString name)
{
    //ui->lblMouse_Current_Event->setText("Mouse Presseds!");
    originX = ui->lbVideo1->x;
    originY = ui->lbVideo1->y;

       clicked = true;
}

void MainWindow::DrawRec(QString name)
{
    QLabel *label = findChild<QLabel*>(name);


    QPixmap pixmap = videoes_data[0].imgInLabel;
    QPainter painter(&pixmap);
    QPen Red((QColor(255,0,0)),5);
    painter.setPen(Red);

    painter.drawLine(originX,originY,ui->lbVideo1->x,originY); //right
    painter.drawLine(ui->lbVideo1->x,originY,ui->lbVideo1->x,ui->lbVideo1->y); //down
    painter.drawLine(ui->lbVideo1->x,ui->lbVideo1->y,originX,ui->lbVideo1->y); //left
    painter.drawLine(originX,ui->lbVideo1->y,originX,originY); //up

    label->setPixmap(pixmap);
    label->show();

    if (!clicked)
        videoes_data[0].imgInLabel = pixmap;
}

void MainWindow::Mouse_left(QString name)
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

void MainWindow::on_btPause_clicked()
{
    if(stop_all)
        stop_all = false;
    else
        stop_all = true;
    stopProcess();
}


