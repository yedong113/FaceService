//
// Created by yedong on 8/19/17.
//

#ifndef FACESERVICE_CAMERA_H_H
#define FACESERVICE_CAMERA_H_H

#include <string>
#include <boost/shared_ptr.hpp>

struct Camera;
typedef boost::shared_ptr<Camera >CameraPtr;

struct Camera
{
    int camera_id;
    std::string rtsp_stream;
};





#endif //FACESERVICE_CAMERA_H_H
