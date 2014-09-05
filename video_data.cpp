#include "video_data.h"



video_data::video_data(std::string path)
{
    video_path = path;
}

std::string video_data::get_video_path()
{
    return video_path;
}
