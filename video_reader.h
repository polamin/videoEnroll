/*
 * video_reader.h
 *
 *  Created on: 30 Apr, 2014
 *      Author: shixudongleo
 */

#ifndef VIDEO_READER_HPP_
#define VIDEO_READER_HPP_

#include <string>
#include <opencv2/opencv.hpp>
using namespace std;

class VideoReader {
 public:
  VideoReader(string path);
  ~VideoReader();
  void set_video_index(int zero_start_frame_idx);
  cv::Mat get_current_frame();
  int get_video_length();

  private:
   cv::VideoCapture video;
};

#endif /* VIDEO_READER_HPP_ */
