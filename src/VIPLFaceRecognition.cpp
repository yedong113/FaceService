//
// Created by yedong on 8/20/17.
//

#include "VIPLFaceRecognition.h"


VIPLFaceRecognition::VIPLFaceRecognition(const std::string &modelPath1, const std::string &modelPath2,
                                         const std::string &modelPath3, const std::string &modelPath4)
{

}

VIPLFaceRecognition::VIPLFaceRecognition(const std::string &detectorModelPath, const std::string &pointDetectModelPath,
                                         const std::string &faceRecognizerModel1,
                                         const std::string &faceRecognizerModel2, const std::string &qaModelPath)
{

}



int VIPLFaceRecognition::imageFeat(const std::string &token, const cv::Mat &srcImg, VIPLTrackingInfo face,
                                   SequenceFacePosFeat &seqfaceposfeat)
{
    VIPLImageData imgData = vipl_convert(srcImg);
    {

        float face_score = QA->Evaluate(imgData, face.pos);
        if (face_score < 0.85f)
        {
            //return 0;
        }
        IFFacePosFeatPtr faceposfeat(new IFFacePosFeat);
        faceposfeat->faceId = face.PID;
        cv::Rect capture_face_rect;
        capture_face_rect.x = face.pos.x;
        capture_face_rect.y = face.pos.y;
        capture_face_rect.width = face.pos.width;
        capture_face_rect.height = face.pos.height;
        capture_face_rect.x = capture_face_rect.x < 0 ? 0 : capture_face_rect.x;
        capture_face_rect.y = capture_face_rect.y < 0 ? 0 : capture_face_rect.y;
        capture_face_rect.width = srcImg.cols > capture_face_rect.x + capture_face_rect.width ? capture_face_rect.width : srcImg.cols - capture_face_rect.x;
        capture_face_rect.height = srcImg.rows > capture_face_rect.y + capture_face_rect.height ? capture_face_rect.height : srcImg.rows - capture_face_rect.y;
        faceposfeat->facepos.rcFace.left = capture_face_rect.x;
        faceposfeat->facepos.rcFace.right = capture_face_rect.x + capture_face_rect.width;
        faceposfeat->facepos.rcFace.top = capture_face_rect.y;
        faceposfeat->facepos.rcFace.bottom = capture_face_rect.y + capture_face_rect.height;
        faceposfeat->facepos.age = 0;
        faceposfeat->facepos.sex = -1;
        faceposfeat->facepos.nQuality = face_score*100;
        VIPLPoint5 points;
        point_detector->DetectLandmarks(imgData, face.pos, points);

        cv::Mat faceim(face_recognizer->GetCropHeight(), face_recognizer->GetCropWidth(), CV_8UC(face_recognizer->GetCropChannels()));
        VIPLImageData vface = vipl_convert(faceim);
        face_recognizer->CropFace(imgData, points, vface);

        faceposfeat->feat = new float[face_recognizer->GetFeatureSize()];
        face_recognizer->ExtractFeature(vface, faceposfeat->feat);
        seqfaceposfeat.push_back(faceposfeat);
    }
    return 1;
}

VIPLImageData VIPLFaceRecognition::vipl_convert(const cv::Mat &img)
{
    VIPLImageData vimg(img.cols, img.rows, img.channels());
    vimg.data = img.data;
    return vimg;
}

int VIPLFaceRecognition::imageFeat(const std::string &token, const cv::Mat &srcImg, IFFacePosFeat &faceposfeat) {

    VIPLImageData imgData(srcImg.cols, srcImg.rows, srcImg.channels());
    imgData.data = srcImg.data;



    /* Face Detection */
    int32_t faceNum = 0;
    std::vector<VIPLFaceInfo> faces = detector->Detect(imgData);
    faceNum = faces.size();

    if (faceNum == 0) {
        return 0;
    }

    int max_face_size = 0;
    int max_face_index = 0;
    max_face_size = faces[0].width;
    for (int32_t i = 0; i < faceNum; i++)
    {
        int curr_face_size = faces[i].width;
        if (curr_face_size > max_face_size)
        {
            max_face_size = curr_face_size;
            max_face_index = i;
        }
    }
    cv::Rect capture_face_rect;

    {


        int32_t i = max_face_index;

        if (faces[i].score < 10.0f)
        {
        }

        {
            capture_face_rect.x = faces[i].x;
            capture_face_rect.y = faces[i].y;
            capture_face_rect.width = faces[i].width;
            capture_face_rect.height = faces[i].height;

            capture_face_rect.x = capture_face_rect.x < 0 ? 0 : capture_face_rect.x;
            capture_face_rect.y = capture_face_rect.y < 0 ? 0 : capture_face_rect.y;
            capture_face_rect.width = srcImg.cols > capture_face_rect.x + capture_face_rect.width ? capture_face_rect.width : srcImg.cols - capture_face_rect.x;
            capture_face_rect.height = srcImg.rows > capture_face_rect.y + capture_face_rect.height ? capture_face_rect.height : srcImg.rows - capture_face_rect.y;


            faceposfeat.facepos.rcFace.left = capture_face_rect.x;
            faceposfeat.facepos.rcFace.right = capture_face_rect.x + capture_face_rect.width;
            faceposfeat.facepos.rcFace.top = capture_face_rect.y;
            faceposfeat.facepos.rcFace.bottom = capture_face_rect.y + capture_face_rect.height;
            faceposfeat.facepos.nQuality = faces[i].score * 100;
            faceposfeat.facepos.age = 0;
            faceposfeat.facepos.sex = -1;
            faceposfeat.facepos.fAngle.yaw = faces[i].yaw;
            faceposfeat.facepos.fAngle.pitch = faces[i].pitch;
            faceposfeat.facepos.fAngle.roll = faces[i].roll;


        }

        VIPLPoint5 points;
        point_detector->DetectLandmarks(imgData, faces[i], points);
        faceposfeat.facepos.nQuality = QA->Evaluate(imgData, faces[i]);

        {
            int point_index = 0;
            faceposfeat.facepos.ptLeftEye.x = points[point_index].x;
            faceposfeat.facepos.ptLeftEye.y = points[point_index].y;

            point_index++;
            faceposfeat.facepos.ptRightEye.x = points[point_index].x;
            faceposfeat.facepos.ptRightEye.y = points[point_index].y;


            point_index++;
            faceposfeat.facepos.ptNose.x = points[point_index].x;
            faceposfeat.facepos.ptNose.y = points[point_index].y;

            point_index++;
            faceposfeat.facepos.ptMouth.x = points[point_index].x;
            faceposfeat.facepos.ptMouth.y = points[point_index].y;

            faceposfeat.facepos.ptLeftMouth.x = points[point_index].x;
            faceposfeat.facepos.ptLeftMouth.y = points[point_index].y;

            point_index++;
            faceposfeat.facepos.ptRightMouth.x = points[point_index].x;
            faceposfeat.facepos.ptRightMouth.y = points[point_index].y;

        }

        cv::Mat dstImg(face_recognizer->GetCropHeight(),
                       face_recognizer->GetCropWidth(),
                       CV_8UC(face_recognizer->GetCropChannels()));
        VIPLImageData dstImgData(dstImg.cols, dstImg.rows, dstImg.channels());
        dstImgData.data = dstImg.data;

        VIPLImageData srcImgData(srcImg.cols, srcImg.rows, srcImg.channels());
        srcImgData.data = srcImg.data;

        faceposfeat.feat = new float[face_recognizer->GetFeatureSize()];
        face_recognizer->CropFace(srcImgData, points, dstImgData);
        face_recognizer->ExtractFeature(dstImgData, faceposfeat.feat);
    }
    return faceNum;
}


