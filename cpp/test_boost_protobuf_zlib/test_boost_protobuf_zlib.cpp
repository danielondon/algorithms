#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <zlib.h>
#include <tripcommon.pb.h>
#include <future>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <array>
#include "CallQueue.h"
#include <chrono>
#include <random>

using namespace std;

using cb_void = std::function<void()>;

void sleep()
{
    std::mt19937_64 eng{std::random_device{}()};  // or seed however you want
    std::uniform_int_distribution<> dist{1, 5};
    auto milli = std::chrono::seconds{dist(eng)};
    cout<<"sleeping for "<< milli.count()<<endl;
    std::this_thread::sleep_for(milli);
    cout<<"end sleep"<<endl;
}

void anotherFunctionThatTakesTime (cb_void callback)
{
    cout<<"anotherFunctionThatTakesTime "<<endl;
    sleep();
    for ( unsigned long i =0; i < 1000000; ++i)
    {
        double x = 125.62 * i / 235.5;
        x++;
    }
    cout<<"end calculation "<<endl;
    callback();
    cout<<"end function "<<endl;
}

void someFunction (cb_void callback)
{
    cout<<"Some function "<<endl;
    anotherFunctionThatTakesTime([callback](){
        callback();
    } );
    cout<<"end Some function "<<endl;
}

class LifeCicleItem
{
public:
    void start(cb_void cb)
    {
        cout<<"start..."<<endl;
        anotherFunctionThatTakesTime([cb](){ cb(); });
        //cb();
        cout<<"...start"<<endl;
    }

};

class MapManager
{

private:
    void startLifeCycleItems(cb_void cb)//, vector<future<void>> &futures)
    {
        cout<<"startLifeCycleItems..."<<endl;
        unique_lock<mutex> lock(m_mutex);
        //vector<future<void>> futures(m_lifeCycleItems.size());

        //for(auto & item : m_lifeCycleItems)
        for (size_t i =0; i< m_lifeCycleItems.size(); ++i)
        {
            auto & item = m_lifeCycleItems[i];
            auto syncCall = [this](){
                cout<<"startLifeCycleItems::notifying semaphore"<<endl;
                m_semaphore.notify_one();
            };
            //futures[i] = std::async(std::launch::async, &LifeCicleItem::start, &item, syncCall);
            futures.emplace_back(std::async(std::launch::async, &LifeCicleItem::start, &item, syncCall));
        }

        cout<<"startLifeCycleItems...each cycle item was started"<<endl;

        for (size_t i =0; i< m_lifeCycleItems.size(); ++i)
        {
            cout<<"startLifeCycleItems::Waiting for semaphore"<<endl;
            m_semaphore.wait(lock);
        }

        //cout<<"Waiting for futures"<<endl;
        //for (auto &future : futures)
       // {
        //    future.get();
        //}

        cout<<"startLifeCycleItems...callback"<<endl;
        cb();
        cout<<"...startLifeCycleItems"<<endl;
    }

    void nextFunction()
    {
        cout<<"nextFunction"<<endl;
    }

public:

    void initializeMapInstances()
    {        
        //vector<future<void>> futures(m_lifeCycleItems.size());
        cout<<"Before Start Life Cycle"<<endl;
        m_calls.executeCall(std::bind(&MapManager::startLifeCycleItems, this,
                                      [this](){
                                        m_calls.callFinished();}
                                        ));//, std::ref(futures)));
        cout<<"After Start Life Cycle"<<endl;
        m_calls.executeCall(std::bind(&MapManager::nextFunction, this));
        cout<<"After Next function"<<endl;
    }
private:
    vector<future<void>> futures;
    array<LifeCicleItem, 2> m_lifeCycleItems;
    CallQueue m_calls;
    std::mutex m_mutex;
    std::condition_variable m_semaphore;
};


int main()
{
    cout<<"Test for zlib, protobug and valhalla including proto"<<endl<<endl;
    //::google::protobuf::uint32 begin_heading;
    auto f = std::async(std::launch::async, someFunction, [](){ cout<<"We are finished"<<endl;});
    cout<<"bye"<<endl;
    f.get();
    //someFunction([](){ cout<<"We are finished"<<endl;} );

    cout<<"-------------"<<endl;
    MapManager mapManager;
    mapManager.initializeMapInstances();
    cout<<"----end"<<endl;
    return 0;
}
