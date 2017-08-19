cmake_minimum_required(VERSION 3.8)
project(FaceService)

set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/local/boost-1.60/include)
include_directories(/usr/local/OpenCV2.4.13/include)
include_directories(/usr/local/libvlc/include)
include_directories(/usr/local/libvlc/include/vlc)
include_directories(/usr/local/libvlcpp)
include_directories(/usr/local/mysql/include)
#/usr/local/VIPL_SDK
include_directories(/usr/local/VIPL_SDK/FaceDetector511/include)
include_directories(/usr/local/VIPL_SDK/FaceRecognizerMaster/include)
include_directories(/usr/local/VIPL_SDK/FaceTracking//include)
include_directories(/usr/local/VIPL_SDK/PointDetector/include)
include_directories(/usr/local/VIPL_SDK/PoseEstimation//include)
include_directories(/usr/local/VIPL_SDK/QualityAssessment/include)
include_directories(./src)



link_directories(
        /usr/local/boost-1.60/lib
        /usr/local/OpenCV2.4.13/lib
        /usr/local/libvlc/lib
        /usr/local/mysql/lib
        /usr/local/VIPL_SDK/lib
)


set(SOURCE_FILES main.cpp src/PersistenceI.cpp src/PersistenceI.h src/person.h
        src/camera.h src/ConfigManager.cpp src/ConfigManager.h src/UserInclude.h
        main.cpp src/config.h src/FaceConf.cpp src/FaceConf.h src/VIPLFaceRecognition.cpp src/VIPLFaceRecognition.h src/FaceStruct.h src/QueueCondition.h)


add_executable(FaceService ${SOURCE_FILES})



target_link_libraries(${PROJECT_NAME} -lopencv_highgui
        -lopencv_imgproc
        -lopencv_core
        -lmysqlcppconn
        -lmysqlclient
        -lboost_date_time
        -lboost_system
        -lboost_thread
        -lVIPLFaceDetector511
        -lVIPLPointDetector500
        -lVIPLPoseEstimation100
        -lVIPLQualityAssessment210
        -lVIPLFaceRecognizerMaster
        )



