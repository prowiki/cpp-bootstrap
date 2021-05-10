#include <string>

#include "book.hh"

namespace object
{

Book::Book(const std::string& name, double price): name(name), price(price)
{
}

double Book::get_price() const
{
    return price;
}

std::string Book::get_name() const
{
    return name;
}

} // namespace object
