# C++ Smart Pointer

- [C++ Smart Pointer](#c-smart-pointer)
  - [basics](#basics)
  - [Self-Implemented Smart Pointer](#self-implemented-smart-pointer)

## basics

- `shared_ptr`

```cpp
struct Obj
{
    int x;
    std::string str;
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
    // should avoid this because it introduce an additional copy
    Obj obj(x, str);
    return std::make_shared<Obj>(obj);
}

std::shared_ptr<Obj> shared_ptr_obj;
std::cout << "use count: " << shared_ptr_obj.use_count() << std::endl; // count to nullptr is 0

shared_ptr_obj = build_shared_ptr_obj();
std::cout << "use count: " << shared_ptr_obj.use_count() << std::endl;
```

- `weak_ptr`

Use `weak_ptr` with `shared_ptr`:

```cpp
std::weak_ptr<Obj> weak_ptr_obj; // nullptr

{
    auto shared_ptr_obj = build_shared_ptr_obj();
    std::cout << "use count: " << shared_ptr_obj.use_count() << std::endl; // count 1

    weak_ptr_obj = shared_ptr_obj; // weak_ptr --> shared_ptr

    std::shared_ptr<Obj> locked_weak_ptr_obj = weak_ptr_obj.lock();

    std::cout << "use count: " << shared_ptr_obj.use_count() << std::endl; // count 2
    std::cout << "use count: " << locked_weak_ptr_obj.use_count() << std::endl; // count 2
}

// weak_ptr --> shared_ptr obj is deleted, so it's expired and can't be locked
std::cout << "expired: " << weak_ptr_obj.expired() << std::endl;

// segment fault
// std::cout << unique_ptr_obj.lock()->x << "  " << unique_ptr_obj.lock()->str << std::endl;
```

If we update `shared_ptr`, then the **"shared_count"** becomes 0 though the **"weak_count"** won't. The `weak_ptr` pointing to the same address will expire because the **"shared_count"** is 0. See [this](https://stackoverflow.com/questions/5671241/how-does-weak-ptr-work) for the implementation of `weak_ptr`.

```cpp
shared_ptr_obj = build_shared_ptr_obj();
std::weak_ptr weak_ptr_obj = shared_ptr_obj;
std::cout << "expired: " << weak_ptr_obj.expired() << std::endl;
// the weak_ptr will expire
shared_ptr_obj = nullptr;
std::cout << "expired: " << weak_ptr_obj.expired() << std::endl;
```

- `unique_ptr`

```cpp
std::unique_ptr<Obj> build_unique_ptr_obj()
{
    int x = 10;
    std::string str = "abcd";
    return std::make_unique<Obj>(x, str);
}

auto unique_ptr_obj = build_unique_ptr_obj();
std::cout << unique_ptr_obj->x << "  " << unique_ptr_obj->str << std::endl;

// compile error: can't copy unique ptr
// auto unique_ptr_obj_2 = unique_ptr_obj;
// std::cout << unique_ptr_obj_2->x << "  " << unique_ptr_obj_2->str << std::endl;

// this is legal because unique_ptr has move constructor
auto unique_ptr_obj_2 = std::move(unique_ptr_obj);
std::cout << unique_ptr_obj_2->x << "  " << unique_ptr_obj_2->str << std::endl;
```

## Self-Implemented Smart Pointer

TODO
