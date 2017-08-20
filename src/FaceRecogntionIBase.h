//
// Created by yedong on 8/20/17.
//

#ifndef FACESERVICE_FACERECOGNTIONIBASE_H
#define FACESERVICE_FACERECOGNTIONIBASE_H


#include "FaceStruct.h"

#include "UserInclude.h"

#include "VIPLFaceRecognition.h"
#include "QueueCondition.h"


class FaceRecogntionIBase {
public:
    FaceRecogntionIBase();

public:
    int procExteact(VIPLFaceRecognition *faceRecognition);
private:
    int calcSimilarity(FaceServiceRequestPtr request,VIPLFaceRecognition *faceRecognition);
    int calcSimilarity(IFFacePosFeatPtr faceposfeat,VIPLFaceRecognition *faceRecognition,std::vector<CompareResultPtr>&v);
private:
    QueueCondition<FaceServiceRequestPtr >queueExtract;
};


#endif //FACESERVICE_FACERECOGNTIONIBASE_H
