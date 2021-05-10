// only needs the declaration of object::Book
#include "objects/book_fwd.hh"

// though you can still include the header file, but this will increase the compiling time
// #include "objects/book.hh"

void print_book(const object::Book& book);

void print_book();
