//
// Created by yedong on 8/19/17.
//

#ifndef FACESERVICE_CONFIGMANAGER_H
#define FACESERVICE_CONFIGMANAGER_H

#include "UserInclude.h"

class ConfigManager
{
public:
    bool InitConfigFile(const std::string& Filename);
    std::string GetConfigValues(const std::string& Key);
    boost::property_tree::ptree GetConfigTree(const std::string& Key);

    bool  save(boost::property_tree::ptree pt);

protected:

    std::string mFileName;

    boost::property_tree::ptree mPT;//

    RW_MUTEX mMutex;
};

//typedef boost::detail::thread::singleton<ConfigManager> CONFIG_MANAGER;


#endif //FACESERVICE_CONFIGMANAGER_H
