//
// Created by yedong on 8/20/17.
//

#ifndef FACESERVICE_VIPLFACERECOGNITION_H
#define FACESERVICE_VIPLFACERECOGNITION_H
#include <VIPLFaceDetector.h>
#include <VIPLPointDetector.h>
#include <VIPLFaceRecognizer.h>
#include <VIPLQualityAssessment.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;
#include <VIPLMoreStruct.h>
#include <string>
#include "FaceStruct.h"


class VIPLFaceRecognition {
public:
    VIPLFaceRecognition(const std::string & modelPath1,
                        const std::string & modelPath2, const std::string & modelPath3,const std::string &modelPath4);
    VIPLFaceRecognition(const std::string &detectorModelPath, const std::string &pointDetectModelPath,
                        const std::string &faceRecognizerModel1, const std::string &faceRecognizerModel2,
                        const std::string &qaModelPath);
    ~VIPLFaceRecognition(){}

public:
    ////提取人脸追踪的检测到的人脸特征值
    int imageFeat(const std::string &token,const  cv::Mat &im, VIPLTrackingInfo face,SequenceFacePosFeat & seqfaceposfeat);
    VIPLImageData vipl_convert(const cv::Mat &img);

    int imageFeat(const std::string &token, const cv::Mat &srcImg, IFFacePosFeat & faceposfeat);
private:
    VIPLFaceDetector   *detector;
    VIPLFaceRecognizer *face_recognizer;
    VIPLPointDetector  *point_detector;
    VIPLQualityAssessment *QA;

};


#endif //FACESERVICE_VIPLFACERECOGNITION_H
