//
// Created by yedong on 8/20/17.
//

#include "FaceRecogntionIBase.h"

#include "PersistenceI.h"
#include "FaceConf.h"

int FaceRecogntionIBase::procExteact(VIPLFaceRecognition *faceRecognition)
{

    while (true)
    {
        FaceServiceRequestPtr request;
        bool bRet = queueExtract.Pop(request);
        if(!bRet)
        {
            break;
        }
        for (auto face:request->faces)
        {
            faceRecognition->imageFeat("a",request->srcImg,face,request->seqFaceFosFeat);
        }
    }

    return 0;
}

int FaceRecogntionIBase::calcSimilarity(FaceServiceRequestPtr request, VIPLFaceRecognition *faceRecognition)
{
    for(auto & faceposfeat:request->seqFaceFosFeat)
    {

    }
    return 0;
}

boost::mutex mutexPersonBasemap;



bool compare_result(CompareResultPtr ptr1, CompareResultPtr ptr2)
{
    return ptr1->sources > ptr2->sources;
}

int FaceRecogntionIBase::calcSimilarity(IFFacePosFeatPtr faceposfeat, VIPLFaceRecognition *faceRecognition,
                                        std::vector<CompareResultPtr> &v)
{
    std::vector<CompareResultPtr > vec_t;
    float max_score = 0.0f;

    {
        SCOPED_LOCK lock(mutexPersonBasemap);
        auto listPersonBasemap = PersistenceISingle::instance().getListPersonBasemap();
        for(auto personBasemap:listPersonBasemap)
        {
            float score = faceRecognition->calcSimilarity(faceposfeat->feat,personBasemap->feat);
            CompareResultPtr c_ptr(new CompareResult);
            c_ptr->person_id=personBasemap->person_id;
            c_ptr->sources=score;
            if(score>max_score)
            {
                max_score=score;
            }
            vec_t.push_back(c_ptr);
        }

    }

    std::sort(vec_t.begin(), vec_t.end(), compare_result);
    int flag=0;
    for(auto &ptr:vec_t)
    {
        int flag1 = 0;
        for(auto &ptr1:v)
        {
            if (ptr1->person_id == ptr->person_id)
            {
                flag1++;
                break;
            }
        }

        if (!flag1)
        {
            v.push_back(ptr);
        }

        if (v.size() >= 10)
        {
            break;
        }
        if (flag == 0)
        {
            flag++;
        }
    }

    if (max_score>FACECONFI.openDoorScore)
    {
        if (FACECONFI.openAccessControl)//是否要打开门禁设备
        {
            printf("opendoor score=%0.2f  opendoorsource=%f\n", max_score, FACECONFI.openDoorScore);
        }
        addFaceID2IdentifiedSet(faceposfeat->faceId);
    }

    return 0;
}



bool FaceRecogntionIBase::faceIdIdentified(int faceID)
{
    bool bRet = false;
    SCOPED_LOCK lock(mutexIdentifiedSet);
    auto pos = IdentifiedSet.find(faceID);
    if (pos!=IdentifiedSet.end())
    {
        bRet = true;
    }
    return bRet;
}

void FaceRecogntionIBase::addFaceID2IdentifiedSet(int faceID)
{
    SCOPED_LOCK lock(mutexIdentifiedSet);
    IdentifiedSet.insert(faceID);
}



