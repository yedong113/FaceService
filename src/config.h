//
// Created by yedong on 8/19/17.
//

#ifndef FACESERVICE_CONFIG_H
#define FACESERVICE_CONFIG_H

#include <string>
#include <boost/shared_ptr.hpp>

using namespace std;



typedef struct Config
{
    std::string   name;
    std::string   values;
    std::string   desc;
}Config;


typedef boost::shared_ptr<Config >ConfigPtr;



#endif //FACESERVICE_CONFIG_H
