//
// Created by yedong on 8/19/17.
//

#include "PersistenceI.h"


#include <cppconn/resultset.h>

#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <iostream>

#include "FaceConf.h"



PersistenceI::PersistenceI()
{

}


void PersistenceI::setDBInfo(const std::string &n, const std::string &h, const std::string &u, const std::string &p,
                             unsigned short pt) {
    db_info.name=n;
    db_info.host=h;
    db_info.user=u;
    db_info.pass=p;
    db_info.port=pt;
}


sql::Connection * PersistenceI::getConnect() {
    sql::Connection *conn = 0;
    sql::mysql::MySQL_Driver *driver;
    std::stringstream ss;
    sql::Statement *stmt;
    int  interactive_timeout = 1;
    ss << "tcp://" << db_info.host << ":" << db_info.port << "/" << db_info.name;
    driver = sql::mysql::get_mysql_driver_instance();
    conn = driver->connect(ss.str(), db_info.user, db_info.pass);
    if (interactive_timeout)
    {
        std::string sql = "set interactive_timeout=24*3600";
        stmt = conn->createStatement();
        stmt->execute(sql);
    }

    return conn;
}


bool PersistenceI::readCamera()
{
    sql::Connection *conn = 0;
    sql::Statement *stmt;
    sql::ResultSet *res;
    bool bRet = false;
    std::string sql_command="select id,rtsp_path from camera";
    try
    {
        conn = getConnect();
        stmt = conn->createStatement();
        stmt->execute("SET character set gbk");
        res = stmt->executeQuery(sql_command);
        while (res->next())
        {
            CameraPtr  ptr(new Camera);
            ptr->camera_id = res->getInt("id");
            ptr->rtsp_stream = res->getString("rtsp_path");
            std::cout<<"id="<<ptr->camera_id<<" rtsp_stream="<<ptr->rtsp_stream<<std::endl;
            listCamera.push_back(ptr);
            //FaceRecognitionISingle::instance().addCameraConfig(ptr);
        }
        res->close();
        stmt->close();
        conn->close();
        conn = NULL;
        bRet = true;
    }

    catch (sql::SQLException &ex)
    {
        if (conn != NULL)
        {
            conn->close();
            conn = NULL;
        }
        throw ex;
    }
    catch (std::exception & ex)
    {
        if (conn != NULL)
        {
            conn->close();
            conn = NULL;
        }
        throw ex;
    }
    return bRet;
}

bool PersistenceI::readPersonBasemap()
{
    std::string sql_command="select person_id,path,features from person_basemap";
    std::string file_path;
    sql::Connection *conn = 0;
    sql::Statement *stmt;
    sql::ResultSet *res;
    bool bRet = false;
    try {
        conn = getConnect();
        stmt = conn->createStatement();
        stmt->execute("SET character set gbk");
        res = stmt->executeQuery(sql_command);
        while (res->next())
        {
            PersonBasemapPtr ptr(new PersonBasemap);
            ptr->person_id=res->getString("person_id");
            ptr->path = res->getString("path");
            std::istream *stream = res->getBlob("features");
            if (stream!=NULL)
            {
                stream->seekg(0, std::ios::end);
                int len = stream->tellg();
                ptr->is_features = false;
                if(len>0)
                {
                    ptr->feat = new float[len/4];
                    char * byte2feat = new char[len];
                    stream->seekg(std::ios::beg);
                    stream->read(byte2feat, len);
                    memcpy((void *)ptr->feat,(void *)byte2feat,len);
                    ptr->is_features=true;
                }
            }
            listPersonBasemap.push_back(ptr);
        }
        res->close();
        stmt->close();
        conn->close();
        conn = NULL;
        bRet = true;
    }
    catch (sql::SQLException &ex)
    {

    }
    return bRet;
}

bool PersistenceI::readConfig()
{
    sql::Connection *conn = 0;
    sql::Statement *stmt;
    sql::ResultSet *res;
    bool bRet = false;
    std::string sql_command = "select param_id,param_values,param_description from system_param";
    try
    {
        conn = getConnect();
        stmt = conn->createStatement();
        //stmt->execute("SET character set gbk");
        res = stmt->executeQuery(sql_command);
        vectorConfig.clear();
        while (res->next())
        {
            ConfigPtr ptr(new Config);
            ptr->name = res->getString(1);
            ptr->values = res->getString(2);
            ptr->desc = res->getString(3);
            vectorConfig.push_back(ptr);
        }
        res->close();
        stmt->close();
        conn->close();
        conn = NULL;
        bRet = true;
    }

    catch (sql::SQLException &ex)
    {
        std::cout<<"readConfig ex.getErrorCode()=" << ex.getErrorCode() << " " << ex.what();
        if (conn != NULL)
        {
            conn->close();
            conn = NULL;
        }
        throw ex;
    }
    FaceConf faceconf;
    for(auto ptr:vectorConfig)
    {
        faceconf.loadFaceConf(ptr);
    }
    return bRet;
}