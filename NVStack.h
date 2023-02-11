#ifndef NV_STACK
#define NV_STACK

template<typename T>
class NVStack
{
public:
    virtual void push(T element) = 0;
    virtual T pop() = 0;
    virtual T top() = 0;
    virtual void clear() = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void print() = 0;
};

#endif
