#include "objects/book.hh"

#include <iostream>

void print_book(const object::Book& book)
{
    std::cout << "Book Name: " << book.get_name() << std::endl;
    std::cout << "Book Price: " << book.get_price() << std::endl;
}

void print_book()
{
    object::Book book("c++ tutorial", 99.9);
    std::cout << "Book Name: " << book.get_name() << std::endl;
    std::cout << "Book Price: " << book.get_price() << std::endl;
}
