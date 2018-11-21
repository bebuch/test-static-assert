cmake_minimum_required(VERSION 3.12.4)

project(test)

# Setup testing
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Add test cpp file
include_directories("../include")


add_executable(unit_test unit_test.cpp)

add_test(NAME unit_test COMMAND unit_test)


add_executable(main_valid main_valid.cpp)

add_test(NAME main_valid COMMAND main_valid)


add_executable(main_invalid main_invalid.cpp)

set_target_properties(main_invalid PROPERTIES
                      EXCLUDE_FROM_ALL TRUE
                      EXCLUDE_FROM_DEFAULT_BUILD TRUE)

add_test(NAME main_invalid
         COMMAND ${CMAKE_COMMAND} --build . --target main_invalid --config $<CONFIGURATION>
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

set_tests_properties(main_invalid PROPERTIES WILL_FAIL TRUE)
