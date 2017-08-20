//
// Created by yedong on 8/19/17.
//

#ifndef FACESERVICE_FACECONF_H
#define FACESERVICE_FACECONF_H

#include <string>
using namespace  std;


#include "config.h"


class FaceConf {
public:
    FaceConf();
    ~FaceConf(){}
public:
    void loadFaceConf(ConfigPtr ptr);
public:
    std::string   raw_person_path;
    int           yaw_size; //脸部前后偏离角度
    int           pitch_size;//脸部上下偏离角度
    int           roll_size; //脸部左右偏离角度
    int           face_size; //脸部大小
    short         extract_threads;//人脸特征提取线程数
    int           Quality;        //检测图像质量 低于此质量的人像自动忽略
    std::string   post_url;
    std::string   base_url;
    float         comp_source;
    double        scale;
    double        face_scale;//脸部存储缩放比例
    float         factor;
    float         thresh;
    int           step;
    int           openDoorTime;//打开自动门时间
    float         openDoorScore;
    bool          openAccessControl;
    std::string   accessControlAddress;
    int           accessControlPort;
    std::string   accessControlSignal;
};


#endif //FACESERVICE_FACECONF_H
