#include <iostream>
#include <string>
#include "smartptr.h"

using namespace std;

class myptr
{
public:
    smart_ptr_weak<myptr> parent;
    smart_ptr<myptr> child;
    string name_t;
    myptr(string name):name_t(name)
    {
        cout<<"创建:"<<name_t<<endl;
    }

    ~myptr(){
        cout<<"销毁:"<<name_t<<endl;
    }

};

int main()
{
    smart_ptr<myptr> p1(new myptr("第一个"));
    smart_ptr<myptr> p2(new myptr("第二个"));
    p1->child=p2;
    p2->parent=p1;
    auto ptr = p2->parent.lock();
    cout<<ptr->name_t<<endl;

}

