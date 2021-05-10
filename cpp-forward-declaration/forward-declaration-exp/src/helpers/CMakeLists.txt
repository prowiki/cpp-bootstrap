add_library(book_helper book_helper.hh book_helper.cc)

# this library relies on book implementation
target_link_libraries(book_helper book)
