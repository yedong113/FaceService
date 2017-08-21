//
// Created by yedong on 17-8-20.
//

#ifndef FACESERVICE_FACEUPLOADRESULT_H
#define FACESERVICE_FACEUPLOADRESULT_H

#include "UserInclude.h"
#include "FaceStruct.h"
#include "QueueCondition.h"


class FaceUploadResult {
public:
    FaceUploadResult(){}


private:
    void genCompareResult2Json(ptree &pt_request, FaceServiceRequestPtr request);
    void addMachingPerson2Json(ptree & pt_person, CompareResultPtr compPtr);
    std::string getFaceCaptureBase64(FaceServiceRequestPtr request, FaceRecognitionResultPtr faceRecognitionResult);
    std::string cvMat2Base64(cv::Mat input);
    std::string getRawCaptureBase64(FaceServiceRequestPtr request, cv::Mat im);
private:
    int procUploadResult();
private:
    QueueCondition<FaceServiceRequestPtr >queueUploadResult;
    boost::thread_group threadGroup;//线程控制句柄
};


#endif //FACESERVICE_FACEUPLOADRESULT_H
