
# it's an interface library, which won't generate a binary file
add_library(catch2 INTERFACE)
target_sources(catch2 INTERFACE catch.hpp)
