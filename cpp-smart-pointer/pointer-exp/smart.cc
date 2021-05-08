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

std::unique_ptr<Obj> build_unique_ptr_obj()
{
    int x = 10;
    std::string str = "abcd";
    return std::make_unique<Obj>(x, str);
}

std::shared_ptr<Obj> build_shared_ptr_obj()
{
    int x = 10;
    std::string str = "abcd";
    return std::make_shared<Obj>(x, str);
}

int main()
{
    std::cout << "==== Test - 1 ====" << std::endl;
    {
        auto unique_ptr_obj = build_unique_ptr_obj();
        std::cout << unique_ptr_obj->x << "  " << unique_ptr_obj->str << std::endl;

        // compile error: can't copy unique ptr
        // auto unique_ptr_obj_2 = unique_ptr_obj;
        // std::cout << unique_ptr_obj_2->x << "  " << unique_ptr_obj_2->str << std::endl;

        auto unique_ptr_obj_2 = std::move(unique_ptr_obj);
        std::cout << unique_ptr_obj_2->x << "  " << unique_ptr_obj_2->str << std::endl;
    }
    
    std::cout << "==== Test - 2 ====" << std::endl;
    {
        std::weak_ptr<Obj> weak_ptr_obj; // nullptr

        {
            auto shared_ptr_obj = build_shared_ptr_obj();
            std::cout << shared_ptr_obj->x << "  " << shared_ptr_obj->str << std::endl;
        
            std::cout << "use count: " << shared_ptr_obj.use_count() << std::endl;

            weak_ptr_obj = shared_ptr_obj; // weak_ptr --> shared_ptr

            std::shared_ptr<Obj> locked_weak_ptr_obj = weak_ptr_obj.lock();

            std::cout << "use count: " << shared_ptr_obj.use_count() << std::endl;
            std::cout << "use count: " << locked_weak_ptr_obj.use_count() << std::endl;
        }
        
        // weak_ptr --> shared_ptr obj is deleted, so it's expired and can't be locked
        std::cout << "expired: " << weak_ptr_obj.expired() << std::endl;

        // segment fault
        // std::cout << weak_ptr_obj.lock()->x << "  " << weak_ptr_obj.lock()->str << std::endl;
    }

    std::cout << "==== Test - 3 ====" << std::endl;
    {
        std::shared_ptr<Obj> shared_ptr_obj;
        std::cout << "use count: " << shared_ptr_obj.use_count() << std::endl; // count to nullptr is 0

        shared_ptr_obj = build_shared_ptr_obj();
        std::cout << "use count: " << shared_ptr_obj.use_count() << std::endl;

        std::weak_ptr weak_ptr_obj = shared_ptr_obj;
        std::cout << "expired: " << weak_ptr_obj.expired() << std::endl;
        // the weak_ptr will expire
        shared_ptr_obj = nullptr;
        std::cout << "expired: " << weak_ptr_obj.expired() << std::endl;
    }
}