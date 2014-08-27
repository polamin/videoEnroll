
/*
 * video_reader.cpp
 *
 *  Created on: 30 Apr, 2014
 *      Author: shixudongleo
 */

#include "video_reader.h"

VideoReader::VideoReader(string path) {
  bool is_open = video.open(path);

  if (!is_open)
    cout << "Video Open Fail" << endl;
}

VideoReader::~VideoReader() {
  video.release();
}

void VideoReader::set_video_index(int zero_start_frame_idx) {
  video.set(CV_CAP_PROP_POS_FRAMES, zero_start_frame_idx);
}

cv::Mat VideoReader::get_current_frame() {
  cv::Mat frame;
  bool is_read = video.read(frame);

  if (!is_read) {
    /* do not return NULL, instead check frame.empty() */
  }

  return frame;
}

int VideoReader::get_video_length() {
  return video.get(CV_CAP_PROP_FRAME_COUNT);
}
