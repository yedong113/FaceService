//
// Created by yedong on 8/20/17.
//

#ifndef FACESERVICE_FACESTRUCT_H
#define FACESERVICE_FACESTRUCT_H

#if _MSC_VER > 1500
#include <cstdint>
#else
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#endif




#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

typedef struct
{
    int32_t x;
    int32_t y;
    int32_t width;
    int32_t height;
    /* view of face (Euler angle) */
    double roll;  /**< rotation around x aixs */
    double pitch; /**< rotation around y axis */
    double yaw;   /**< rotation around z axis */
    double score;
} IFFaceInfo;


struct IFFaceInfoTracker
{
    IFFaceInfoTracker(){};
    IFFaceInfoTracker(int _pid, int _frame_no, int _x, int _y, int _width, int _height, int _step = 0){
        PID = _pid;
        frame_no = _frame_no;
        step = _step;
        pos.x = _x;
        pos.y = _y;
        pos.width = _width;
        pos.height = _height;
    };
    IFFaceInfoTracker(int _pid, int _frame_no, IFFaceInfo& _pos, int _step = 0){
        PID = _pid;
        frame_no = _frame_no;
        step = _step;
        pos = _pos;
    };

    int PID;
    int frame_no;
    int step;
    IFFaceInfo pos;
};

typedef std::vector<IFFaceInfoTracker >SequenceIFFaceInfoTracker;

class IFRect{
public:
    IFRect()
    {
        left = 0;
        top = 0;
        right = 0;
        bottom = 0;
    }
    IFRect(const IFRect & ifrect)
    {
        left = ifrect.left;
        top = ifrect.top;
        right = ifrect.right;
        bottom = ifrect.bottom;

    }
public:
    int    left;
    int    top;
    int    right;
    int    bottom;
};

class IFPoint{
public:
    IFPoint()
    {
        x = 0;
        y = 0;
    }
    IFPoint(const IFPoint & ifpoint)
    {
        x = ifpoint.x;
        y = ifpoint.y;
    }
public:
    int x;
    int y;
};

class  IFAngleFace{
public:
    IFAngleFace()
    {
        yaw = 0.0f;
        pitch = 0.0f;
        roll = 0.0f;
    }
    IFAngleFace(const IFAngleFace & ifaface)
    {
        yaw = ifaface.yaw;
        pitch = ifaface.pitch;
        roll = ifaface.roll;

    }
public:
    double   yaw;//angle of yaw,from -90 to +90,left is negative,right is postive
    double   pitch;//angle of pitch,from -90 to +90,up is negative,down is postive
    double   roll;//angle of roll,from -90 to +90,left is negative,right is postive
};


class IFFacePos{
public:
    IFFacePos()
    {
        age = 0;
        sex = 0;
        faceID = -1;
    }
    IFFacePos(const IFFacePos & ifacepos)
    {
        rcFace = ifacepos.rcFace;
        ptLeftEye = ifacepos.ptLeftEye;
        ptRightEye = ifacepos.ptRightEye;
        ptMouth = ifacepos.ptMouth;
        ptLeftMouth = ifacepos.ptLeftMouth;
        ptRightMouth = ifacepos.ptRightMouth;
        ptNose = ifacepos.ptNose;
        fAngle = ifacepos.fAngle;
        age = 0;
        sex = 0;
    }
public:
    IFRect      rcFace;
    IFPoint     ptLeftEye;//coordinate of left eye
    IFPoint	    ptRightEye;//coordinate of right eye
    IFPoint		ptMouth;//coordinate of mouth
    IFPoint     ptLeftMouth;
    IFPoint     ptRightMouth;
    IFPoint		ptNose;//coordinate of nose
    IFAngleFace   	fAngle;//value of face angle
    int         age;//年龄
    int         sex;//性别
    float       nQuality;//quality of face(from 0 to 100)
    int         faceID;
};

typedef boost::shared_ptr<IFFacePos > IFFacePosPtr;
typedef float* FaceFeatures;


/*
1:N 识别结果

*/
typedef struct CompareResult
{
    std::string   person_id;
    std::string   web_url;
    std::string   certificate_no;//证件编号
    std::string   name;//姓名
    int           organization_id;//组织架构ID
    std::string   organization_name;
    int           person_type; //人员类型
    std::string   person_type_name;//人员类型名称
    float         sources;
}CompareResult;


typedef boost::shared_ptr<CompareResult >CompareResultPtr;

typedef std::vector<CompareResultPtr > SequenceSingleFaceRecogntionResult;



class  IFFacePosFeat
{
public:
    IFFacePosFeat(){
        feat = NULL;
    }
    IFFacePosFeat(const IFFacePosFeat & faceposfeat)
    {
        facepos = faceposfeat.facepos;
        feat = NULL;
    }
    ~IFFacePosFeat()
    {
        if (feat!=NULL)
        {
            delete[] feat;
        }
    }
public:
    SequenceSingleFaceRecogntionResult  seqFaceRecogntionResult;//识别的结果
    int            faceId;
    IFFacePos      facepos;
    FaceFeatures   feat;
};


typedef boost::shared_ptr<IFFacePosFeat > IFFacePosFeatPtr;
typedef std::vector<IFFacePosFeatPtr > SequenceFacePosFeat;



#endif //FACESERVICE_FACESTRUCT_H
