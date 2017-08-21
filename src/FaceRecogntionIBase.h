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
    boost::thread_group threadGroup;//线程控制句柄
    int calcSimilarity(FaceServiceRequestPtr request,VIPLFaceRecognition *faceRecognition);
    int calcSimilarity(IFFacePosFeatPtr faceposfeat,VIPLFaceRecognition *faceRecognition,std::vector<CompareResultPtr>&v);
private:
    QueueCondition<FaceServiceRequestPtr >queueExtract;

public:
    boost::mutex   mutexIdentifiedSet;
    std::set <int >IdentifiedSet;//已识别的FaceID
    bool faceIdIdentified(int faceID);//faeid是否已识别
    void addFaceID2IdentifiedSet(int faceID);
};


#endif //FACESERVICE_FACERECOGNTIONIBASE_H
