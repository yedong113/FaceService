//
// Created by yedong on 8/19/17.
//

#ifndef FACESERVICE_USERINCLUDE_H
#define FACESERVICE_USERINCLUDE_H


#include <boost/thread/detail/singleton.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/typeof/typeof.hpp>

#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>



#include <boost/thread/detail/singleton.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/typeof/typeof.hpp>


typedef boost::shared_mutex RW_MUTEX;
typedef boost::shared_lock<RW_MUTEX> READ_LOCK;
typedef boost::unique_lock<RW_MUTEX> WRITE_LOCK;
typedef boost::mutex::scoped_lock SCOPED_LOCK;


namespace BP=boost::property_tree;




#endif //FACESERVICE_USERINCLUDE_H
