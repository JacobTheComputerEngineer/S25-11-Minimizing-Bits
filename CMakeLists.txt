cmake_minimum_required(VERSION 3.5)
project(ECE4806-S25-11 CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find ICU libraries
find_package(ICU REQUIRED COMPONENTS uc i18n)

# Source files
set(LIB_SOURCE
    preprocessor.h
    preprocessor.cpp
)

# Compile test_icu binary
add_executable(test_icu main.cpp ${LIB_SOURCE})

# Link ICU libraries
target_include_directories(test_icu PRIVATE ${ICU_INCLUDE_DIRS})
target_link_libraries(test_icu PRIVATE ${ICU_LIBRARIES})


# TODO: Make this more robust
