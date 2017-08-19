//
// Created by yedong on 8/19/17.
//

#include "PersistenceI.h"

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


