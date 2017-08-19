cmake_minimum_required(VERSION 3.8)
project(FaceService)

set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/local/boost-1.60/include)
include_directories(/usr/local/OpenCV2.4.13/include)
include_directories(/usr/local/libvlc/include)
include_directories(/usr/local/libvlc/include/vlc)
include_directories(/usr/local/libvlcpp)
include_directories(/usr/local/mysql/include)



link_directories(
        /usr/local/boost-1.60/lib
        /usr/local/OpenCV2.4.13/lib
        /usr/local/libvlc/lib
        /usr/local/mysql/lib
)


set(SOURCE_FILES main.cpp src/PersistenceI.cpp src/PersistenceI.h src/person.h
        src/camera.h src/ConfigManager.cpp src/ConfigManager.h src/UserInclude.h
        main.cpp)


add_executable(FaceService ${SOURCE_FILES})



target_link_libraries(${PROJECT_NAME} -lopencv_highgui
        -lopencv_imgproc
        -lopencv_core
        -lmysqlclient
        -lmysqlcppconn
        -lboost_date_time
        -lboost_system
        -lboost_thread
        )



