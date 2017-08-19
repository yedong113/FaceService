//
// Created by yedong on 8/19/17.
//

#ifndef FACESERVICE_PERSON_H
#define FACESERVICE_PERSON_H

#include "UserInclude.h"

class PersonBasemap;

typedef boost::shared_ptr<PersonBasemap >PersonBasemapPtr;


class PersonBasemap
{
public:
    PersonBasemap(const std::string & pid,const std::string &w_path):person_id(pid),web_path(w_path),feat(NULL){}
    ~PersonBasemap()
    {
        if (feat!=NULL)
        {
            delete[](feat);
        }
    }
public:
    std::string   person_id;
    float       * feat;
    std::string   web_path;    //web保存底图路径
    std::string   path;        //本地保存底图路径
};






#endif //FACESERVICE_PERSON_H
