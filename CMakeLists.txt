cmake_minimum_required(VERSION 3.5)
project(ECE4806-S25-11 CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find ICU libraries
find_package(ICU REQUIRED COMPONENTS uc i18n)

# Source files
set(LIB_SOURCE
    wordBank.h wordBank.cpp
    preprocessor.h preprocessor.cpp
    parser.h parser.cpp
    encoder.h encoder.cpp
    decoder.h decoder.cpp
)

# Compile test_icu binary
add_executable(erl main.cpp ${LIB_SOURCE})

# Link ICU libraries
target_include_directories(erl PRIVATE ${ICU_INCLUDE_DIRS})
target_link_libraries(erl PRIVATE ${ICU_LIBRARIES})


# TODO: Make this more robust
