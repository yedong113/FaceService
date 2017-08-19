//
// Created by yedong on 8/19/17.
//

#include "FaceConf.h"

#include <iostream>
#include <boost/lexical_cast.hpp>

FaceConf::FaceConf()
{
    openDoorTime = 10;
    openDoorScore = 0.65;
    this->factor = 0.0f;
    this->step = 4;
    this->comp_source = 0.65;
    face_size = 60;
    yaw_size = 15;
    pitch_size = 15;
    roll_size = 15;
    scale = 0.5;
    face_scale = 1;
    post_url = "http://10.20.1.41:8080/pec/monitor/rest/capture";
    extract_threads = 5;
    base_url = "http://10.20.1.41:8080";
    accessControlAddress = "10.20.10.123";
    accessControlPort = 3001;
    accessControlSignal = "on";
    openAccessControl = false;
    thresh = 0.70f;
}

void FaceConf::loadFaceConf(ConfigPtr ptr)
{
    std::stringstream ss;
    std::cout << "配置参数:" << ptr->name << " 参数值:" << ptr->values << " 参数说明:" << ptr->desc<<std::endl;

    if (ptr->name == "face_size")
    {
        face_size = boost::lexical_cast<int>(ptr->values);
    }
    else if (ptr->name == "yaw_size")
    {
        yaw_size = boost::lexical_cast<int>(ptr->values);
    }
    else if (ptr->name == "pitch_size")
    {
        pitch_size = boost::lexical_cast<int>(ptr->values);
    }
    else if (ptr->name == "roll_size")
    {
        roll_size = boost::lexical_cast<int>(ptr->values);
    }
    else if (ptr->name == "scale")
    {
        scale = boost::lexical_cast<float>(ptr->values);
    }
    else if (ptr->name == "face_scale")
    {
        face_scale = boost::lexical_cast<float>(ptr->values);
    }
    else if (ptr->name == "Quality")
    {
        Quality = boost::lexical_cast<int>(ptr->values);
    }
    else if (ptr->name == "post_url")
    {
        this->post_url = ptr->values;
    }
    else if (ptr->name == "extract_threads")
    {
        this->extract_threads = boost::lexical_cast<short>(ptr->values);
    }
    else if (ptr->name == "base_url")
    {
        this->base_url = ptr->values;
    }
    else if (ptr->name=="access_control_address")
    {
        this->accessControlAddress = ptr->values;
    }
    else if (ptr->name == "access_control_signal")
    {
        this->accessControlSignal = ptr->values;
    }
    else if (ptr->name == "access_control_port")
    {
        this->accessControlPort = boost::lexical_cast<int>(ptr->values);
    }
    else if (ptr->name=="opendoorscore")
    {
        this->openDoorScore = boost::lexical_cast<float>(ptr->values);
    }
    else if (ptr->name=="open_ccess_control")
    {
        if (boost::lexical_cast<int>(ptr->values)==0)
        {
            openAccessControl = false;
        }
        else
        {
            openAccessControl = true;
        }
    }
    else if (ptr->name=="thresh")
    {
        thresh = boost::lexical_cast<float>(ptr->values);
    }
}



