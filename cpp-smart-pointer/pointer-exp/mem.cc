#include <iostream>
#include <memory>
#include <string>

struct Obj
{
    int x;
    std::string str;

    Obj(const int x, const std::string str) : x(x), str(str)
    {
        std::cout << "construct Obj" << std::endl;
    }

    Obj(const Obj& obj)
    {
        std::cout << "copy construct Obj" << std::endl;
        x = obj.x;
        str = obj.str;
    }
};

std::shared_ptr<Obj> build_shared_ptr_obj()
{
    int x = 10;
    std::string str = "abcd";
    return std::make_shared<Obj>(x, str);
}

std::shared_ptr<Obj> build_shared_ptr_obj_2()
{
    int x = 10;
    std::string str = "abcd";
    // should avoid it because it introduce an additional copy
    Obj obj(x, str);
    return std::make_shared<Obj>(obj);
}

int main()
{
    std::cout << "==== Test - 1 ====" << std::endl;
    {
        auto shared_ptr_obj = build_shared_ptr_obj();
        std::cout << shared_ptr_obj->x << "  " << shared_ptr_obj->str << std::endl;
    }
    
    std::cout << "==== Test - 2 ====" << std::endl;
    {
        auto shared_ptr_obj = build_shared_ptr_obj_2();
        std::cout << shared_ptr_obj->x << "  " << shared_ptr_obj->str << std::endl;
    }
}