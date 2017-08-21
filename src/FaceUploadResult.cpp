//
// Created by yedong on 17-8-20.
//

#include "FaceUploadResult.h"
#include <sstream>

int FaceUploadResult::procUploadResult() {
    while (true)
    {
        FaceServiceRequestPtr request;
        bool bRet = queueUploadResult.Pop(request);
        if(!bRet)
        {
            break;
        }
        ptree pt_request;
        //genFaceTrackerCompareResult2Json(pt_request, request);
        genCompareResult2Json(pt_request, request);
        std::ostringstream os;
        write_json(os, pt_request);
    }
    return 0;
}

void FaceUploadResult::genCompareResult2Json(ptree &pt_request, FaceServiceRequestPtr request)
{
    ptree pt_faces, pt_camera;

    cv::Mat im = cv::Mat(request->srcImg);

    pt_camera.put("capture_time", request->capture_time);
    for(auto & ptr : request->seqFaceRecogntionResult)
    {
        ptree pt_face;
        /**
        *       将原图中的每张人脸的Base64编码和质量加入json中
        *       face_img    :   "抓取人脸照片base64编码后字符",
        *       img_quality :   "采集人脸图片质量",
        */
        pt_face.add("face_img", getFaceCaptureBase64(request,ptr));
        //        pt_face.add("face_img","");
        pt_face.add<int>("img_quality", ceil(ptr->faceposfeat->facepos.nQuality));

        ptree pt_persons;
        for(auto& compPtr : ptr->compResult)
        {
            ptree pt_person;
            addMachingPerson2Json(pt_person, compPtr);
            pt_persons.push_back(make_pair("", pt_person));
        }
        pt_face.add_child("persons", pt_persons);
        pt_faces.push_back(make_pair("", pt_face));
    }
    std::string ss = getRawCaptureBase64(request, im);
    pt_camera.put("capture_img", ss);
    pt_camera.add_child("faces", pt_faces);
    char buf[10] = { 0 };
    sprintf(buf, "%d", request->camera_id);
    pt_request.add_child(std::string(buf), pt_camera);
    im.release();
}

void FaceUploadResult::addMachingPerson2Json(ptree &pt_person, CompareResultPtr compPtr) {

}

#include <fstream>
#include "ZBase64.h"
#include "public.h"


std::string FaceUploadResult::cvMat2Base64(cv::Mat input) {
    std::string base_path = "./picture/";
    std::string file_path = base_path + get_uuid_string() + ".jpg";
    imwrite(file_path, input);
    std::ifstream fs(file_path.c_str(), std::ios_base::binary);
    int begin = fs.tellg();
    int end = begin;
    int FileSize = 0;
    fs.seekg(0, std::ios_base::end);
    end = fs.tellg();
    FileSize = end - begin;

    fs.seekg(std::ios::beg);
    char *buff = new char[FileSize];
    fs.read(buff, FileSize);
    fs.close();
    const unsigned  char * pbBinary = (const unsigned  char *)buff;

    ZBase64 base64;
    std::string base64Code = base64.Encode(pbBinary, FileSize);
    delete[] buff;
    remove(file_path.c_str());
    return base64Code;
}

std::string FaceUploadResult::getFaceCaptureBase64(FaceServiceRequestPtr request, FaceRecognitionResultPtr faceRecognitionResult)
{
    int face_x = faceRecognitionResult->faceposfeat->facepos.rcFace.left;
    int face_y = faceRecognitionResult->faceposfeat->facepos.rcFace.top;
    int face_w = faceRecognitionResult->faceposfeat->facepos.rcFace.right - faceRecognitionResult->faceposfeat->facepos.rcFace.left;
    int face_h = faceRecognitionResult->faceposfeat->facepos.rcFace.bottom - faceRecognitionResult->faceposfeat->facepos.rcFace.top;
    cv::Rect rect = cv::Rect(face_x,face_y,face_w,face_h);
    cv::Mat p = cv::Mat(request->srcImg, rect);
    cv::Size dsize = cv::Size((int)p.cols, (int)p.rows);
    cv::Mat image2 = cv::Mat(dsize, CV_32S);
    cv::resize(p, image2, dsize);
    return cvMat2Base64(image2);
}

std::string FaceUploadResult::getRawCaptureBase64(FaceServiceRequestPtr request, cv::Mat im)
{
    return cvMat2Base64(im);
}

