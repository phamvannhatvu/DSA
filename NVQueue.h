#ifndef NV_QUEUE
#define NV_QUEUE

template<typename T>
class NVQueue
{
public:
    virtual void enQueue(T element) = 0;
    virtual T deQueue() = 0;
    virtual T top() = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual void print() = 0;
};

#endif // !NV_QUEUE