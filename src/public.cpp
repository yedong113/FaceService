//
// Created by yedong on 17-8-21.
//

#include "public.h"

#include <boost/lexical_cast.hpp>

std::string get_uuid_string()
{
    std::string uuid = boost::lexical_cast<std::string>(boost::uuids::random_generator()()).c_str();
    std::string::iterator new_end = remove_if(uuid.begin(), uuid.end(), std::bind2nd(std::equal_to<char>(), '-'));
    uuid.erase(new_end, uuid.end());
    return uuid;
}