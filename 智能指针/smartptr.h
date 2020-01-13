#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <iostream>

using namespace std;

// 计数类
class _counter
{

public:
    _counter(int u,int v):count(u),count_weak(v){}
    ~_counter(){}
    int count;
    int count_weak;
};

// 智能指针模板
template <typename T>
class smart_ptr
{
    void clear()
    {
        if(ptr==nullptr)
        return ;

        pc->count--;
        if(pc->count==0)
        {
            delete ptr;
        }
        if(pc->count==0 && pc->count_weak==0)
        {
            delete pc;
        }

        pc = nullptr;
        ptr = nullptr;
    }


public:

    bool is_empty() const
    {
        return !(ptr == nullptr);
    }

    smart_ptr()
    {
        pc = nullptr;
        ptr = nullptr;
    }
    smart_ptr(T *t)
    {
        if(t==nullptr)
        {
            pc = nullptr;
            ptr = nullptr;
            return ;
        }

        pc = new _counter(1,0);
        ptr = t;
    }

    smart_ptr(const smart_ptr<T>& rhs)
    {
        pc = rhs.pc;
        ptr = rhs.ptr;
        if(rhs.is_empty())
        {
            return ;
        }
        pc->count++;
    }

    smart_ptr <T>& operator=(const smart_ptr<T>& rhs)
    {
        if(&rhs == this)
        {
            cout<<"指针相同"<<endl;
            return *this;
        }

        clear();
        if(rhs.is_empty())
        {
            return *this;
        }

        pc = rhs.pc;
        ptr = rhs.ptr;
        pc->count++;
        return *this;
    }

    ~smart_ptr()
    {
        clear();
    }

// 数据
    _counter *pc;
    T *ptr;
    T *operator->()
    {
        return ptr;
    }

};

template <typename T>
class smart_ptr_weak
{
    bool is_empty() const
    {
        return ptr == nullptr;
    }

    void clear()
    {
        if(ptr==nullptr)
        {
            return;
        }

        pc->count_weak--;
        if(pc->count==0 && pc->count_weak==0)
        {
            delete ptr;
            delete pc;
        }

        pc = nullptr;
        ptr = nullptr;

    }

public:
    smart_ptr_weak()
    {
        pc = nullptr;
        ptr = nullptr;
    }

    smart_ptr_weak(const smart_ptr<T>& rhs)
    {
        pc = rhs.pc;
        ptr = rhs.ptr;
    
        if(rhs.is_empty())
        {
            return;
        }

        pc->count_weak++;

    }

    smart_ptr_weak<T>& operator=(const smart_ptr<T>& rhs)
    {
        clear();
        if(rhs.is_empty())
        {
            return *this;
        }

        pc = rhs.pc;
        ptr = rhs.ptr;
        pc -> count_weak++;
        return *this;
    }

    _counter *pc;
    T* ptr;
    
    smart_ptr<T> lock()
    {
        smart_ptr<T> tmp;
        if(pc==nullptr||pc->count==0)
        {
            return tmp;
        }

        tmp.pc = pc;
        tmp.ptr = ptr;
        tmp.pc->count_weak++;
        return tmp;
    }

};


#endif
