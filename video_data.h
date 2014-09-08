#ifndef VIDEO_DATA_H
#define VIDEO_DATA_H
#include <QPixmap>
#include "video_reader.h"
#include <opencv2/opencv.hpp>
class video_data
{
public:
    video_data(std::string path);
    std::string get_video_path();

    QString object_name; //What is name of label
    QPixmap img_in_label;
    cv::Mat frame;

private:
    std::string video_path;

};


#endif // VIDEO_DATA_H
