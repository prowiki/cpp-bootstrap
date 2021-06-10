#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <optional>
#include <variant>
#include <utility>

struct KeyValue
{
    std::string key;
    int value;

    KeyValue(const KeyValue& kv): key(kv.key), value(kv.value) {}
    KeyValue(const std::string& key, const int value): key(key), value(value) {}
};

using Identifier = std::variant<std::string, int, KeyValue>;

// helper type for the visitor #4
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

class SuperGetter
{
public:

    KeyValue get_kv(const std::string& key)
    {
        return key_value_map.at(key);
    }

    KeyValue get_kv(const int index)
    {
        return key_value_vec.at(index);
    }

    KeyValue get_kv(const KeyValue& kv)
    {
        return key_value_map.at(kv.key);
    }

    KeyValue get_kv(const Identifier& identifier)
    {
        std::optional<KeyValue> opt_kv;
        std::visit(overloaded{
            [this, &opt_kv](const std::string& key) { opt_kv = get_kv(key); },
            [this, &opt_kv](const int& index) { opt_kv = get_kv(index); },
            [this, &opt_kv](const KeyValue& kv) { opt_kv = get_kv(kv); }
        }, identifier);
        return opt_kv.value();
    }

    void add_kv(const std::string& key, const int value)
    {
        key_value_vec.emplace_back(key, value);
        key_value_map.emplace(std::make_pair(key, KeyValue{key, value}));
    }

private:
    std::vector<KeyValue> key_value_vec;
    std::unordered_map<std::string, KeyValue> key_value_map;
};

int main()
{
    std::string key("val");
    SuperGetter super_getter;
    super_getter.add_kv(key, 123);

    std::vector<Identifier> identifiers{key, 0, KeyValue(key, 123)};
    for (const auto identifier : identifiers)
    {
        auto kv = super_getter.get_kv(identifier);
        std::cout << kv.key << " " << kv.value << std::endl;
    }

    return 0;
}
