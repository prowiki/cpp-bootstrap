#include <string>

// include dummy headers to increase compling time
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <thread>
#include <functional>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <utility>
#include <array>

namespace object
{

struct Book
{
    std::string name;
    double price;

    Book(const std::string& name, double price);

    double get_price() const;
    std::string get_name() const;

};

} // namespace object
