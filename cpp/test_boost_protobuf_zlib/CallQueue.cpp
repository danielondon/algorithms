
#include "CallQueue.h"
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------------------------------
std::ostream& operator << (std::ostream& ostr, const CallQueue& callQueue)
{
    return ostr << callQueue.callCount() << (callQueue.inProgress() ? "+1" : "");
}

//-------------------------------------------------------------------------------------------------
void CallQueue::executeNextCall()
{
    cout<<"executeNextCall"<<endl;
    if (!m_calls.size()
            || m_callInProcess)
    {
        cout<<"executeNextCall : return"<<endl;
        return;
    }

    m_callInProcess = true;

    Call call = m_calls.front();
    m_calls.pop();

    cout<<"executeNextCall-> call"<<endl;
    call();
}
//-------------------------------------------------------------------------------------------------
void CallQueue::callFinished()
{
    cout<<"CallQueue::callFinished"<<endl;
    m_callInProcess = false;

    executeNextCall();
}
//-------------------------------------------------------------------------------------------------
void CallQueue::executeCall(Call call)
{
    cout<<"CallQueue::executeCall"<<endl;
    m_calls.push(call);

    executeNextCall();
}
//-------------------------------------------------------------------------------------------------
void CallQueue::clear()
{
    m_calls = std::queue<Call>();
    m_callInProcess = false;
}
//-------------------------------------------------------------------------------------------------
