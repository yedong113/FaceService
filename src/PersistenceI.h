//
// Created by yedong on 8/19/17.
//

#ifndef FACESERVICE_PERSISTENCEI_H
#define FACESERVICE_PERSISTENCEI_H

#include "person.h"

#include <list>
#include <vector>
#include <cppconn/connection.h>
#include <mysql_driver.h>

#include "camera.h"

#include "config.h"

struct DBInfo
{
    std::string name;
    std::string host;
    std::string user;
    std::string pass;
    unsigned  short port;
};


class PersistenceI {

public:
    PersistenceI();
    void setDBInfo(const std::string &n,const std::string &h,const std::string &u,const std::string &p, unsigned short pt);

public:
    sql::Connection * getConnect();
    bool readCamera();
    bool readPersonBasemap();
    bool readConfig();
private:
    std::vector<ConfigPtr >      vectorConfig;
    std::vector<CameraPtr> listCamera;
    std::list<PersonBasemapPtr > listPersonBasemap;
    DBInfo db_info;
};


#endif
