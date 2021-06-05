
add_executable(test_common_utils test_main.cc test_math_utils.cc)
target_link_libraries(test_common_utils catch2 common_utils)
