//
// Created by yedong on 8/20/17.
//

#ifndef FACESERVICE_QUEUECONDITION_H
#define FACESERVICE_QUEUECONDITION_H




#include <deque>
#include <boost/thread/condition.hpp>

//定义线程安全的队列
//功能:在加入数据时保证线程安全，并在取出数据时，如果队列为空，则阻塞调用，当加入数据时，能及时唤醒，并马上返回
//提供关闭队列的功能，当其他线程阻塞调用
template<class T>
class QueueCondition
{
protected:

    std::deque< T > m_deque;//数据队列
    boost::mutex m_mutex;//线程安全变量
    boost::condition m_condition_variable;//条件变量
    int m_state;//队列状态
public:
    typedef boost::mutex::scoped_lock LOCK;
    //
    QueueCondition() :m_state(1)
    {

    }
    virtual ~QueueCondition()
    {
        //		Close();
    }
    int GetState()
    {
        return m_state;
    }

    void  Reset()
    {
        m_state = 1;
    }

    size_t Size()
    {
        //		LOCK lock(m_mutex);
        return m_deque.size();

    }
    bool Empty()
    {
        return m_deque.empty();
    }

    //模块名称:
    int Push(T &t)
    {
        LOCK lock(m_mutex);
        if(m_state==0)//如果状态无效，返回错误
            return -1;
        m_deque.push_back(t);
        m_condition_variable.notify_one();
        return 1;
    };

    //将数据插入到队列头
    int PushFront(T &t)
    {
        LOCK lock(m_mutex);
        if(m_state==0)//如果状态无效，返回错误
            return -1;
        m_deque.push_front(t);
        m_condition_variable.notify_one();
        return 1;

    }
    void Clear()
    {
        LOCK lock(m_mutex);
        m_deque.clear();

    }

    //模块名称:获取队列头数据
    //模块功能:从队列头取出数据，将数据从队列中移除，如果队列为空，则阻塞调用，直到队列中有数据或者队列关闭
    //输入参数:
    //t:存放数据的引用
    //返回值:
    //true:成功
    //false:队列已关闭
    bool Pop(T &t)
    {
        LOCK lock(m_mutex);
        if(m_state==0)
            return false;

        while(m_deque.empty())
        {
            if(m_state==0)
                return false;
            m_condition_variable.wait(lock);
        }
        if(m_deque.empty())
            return false;
        t=m_deque.front();
        m_deque.pop_front();
        return true;
    }

    //模块名称:关闭队列
    //模块功能:设置队列状态值，并通知所有的阻塞线程退出，Pop函数返回-1
    void Close()
    {
        //		LOCK lock(m_mutex);
        m_state=0;
        m_condition_variable.notify_all();
    }
};





#endif //FACESERVICE_QUEUECONDITION_H
