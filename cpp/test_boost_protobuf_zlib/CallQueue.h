#include <functional>
#include <queue>
#include <ostream>

//-------------------------------------------------------------------------------------------------
class CallQueue
{
public:
    using Call = std::function<void()>;

    /// puts call to queue. Call will be executed when all previous calls are finished.
    void executeCall(Call call);

    void clear();

    /// callFinished MUST be called in the callback of each call.
    void callFinished();

    size_t callCount() const { return m_calls.size(); }
    bool inProgress() const { return m_callInProcess; }

    bool isEmpty() const { return m_calls.empty() && !m_callInProcess; }


private:
    std::queue<Call> m_calls;
    bool m_callInProcess = false;

    void executeNextCall();
};

//-------------------------------------------------------------------------------------------------
std::ostream& operator << (std::ostream& ostr, const CallQueue& callQueue);
