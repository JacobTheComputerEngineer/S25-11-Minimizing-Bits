cmake_minimum_required(VERSION 3.5)
project(ECE4806-S25-11 CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add any new files here
#------------------------------

# Source files
set(LIB_SOURCE
    wordBank.h wordBank.cpp
    preprocessor.h preprocessor.cpp
    parser.h parser.cpp
    encoder.h encoder.cpp
    decoder.h decoder.cpp
)

# You should not need to edit anything below here
#------------------------------

# Try to prevent accidental in-source builds, these cause lots of problems
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Remove any files created thus far and use a different directory for the build.")
endif()

# optional strict mode in reference environment
if(UNIX AND CMAKE_COMPILER_IS_GNUCXX AND STRICT)
  message("-- Enabling strict compilation mode")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()


# Compile test_icu binary
add_executable(erl main.cpp ${LIB_SOURCE})

# Find and link ICU libraries
find_package(ICU REQUIRED COMPONENTS uc i18n)
target_include_directories(erl PRIVATE ${ICU_INCLUDE_DIRS})
target_link_libraries(erl PRIVATE ${ICU_LIBRARIES})


# TODO: Make this more robust
