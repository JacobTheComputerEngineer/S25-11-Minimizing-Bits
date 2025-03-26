cmake_minimum_required(VERSION 3.5)
project(ECE4806-S25-11 CXX)

# Add any new files here
#------------------------------

# Source files
set(LIB_SOURCE
    wordbank.h wordbank.cpp
    preprocessor.h preprocessor.cpp
    parser.h parser.cpp
    encoder.h encoder.cpp
    decoder.h decoder.cpp
)

# Test files
set(TEST_SOURCE
  unittests.cpp
  test_wordbank.cpp
  test_preprocessor.cpp
  test_parser.cpp
  test_encoder.cpp
  test_decoder.cpp
)

# You should not need to edit anything below here
#------------------------------

# Try to prevent accidental in-source builds, these cause lots of problems
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Remove any files created thus far and use a different directory for the build.")
endif()

# Require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(UNIX AND CMAKE_COMPILER_IS_GNUCXX AND FULL)
  message("-- Enabling full build mode")
  set(STRICT TRUE CACHE BOOL "Enable strict build mode")
  set(MEMORY TRUE CACHE BOOL "Enable memory checks")
  set(TIDY TRUE CACHE BOOL "Enable clang-tidy checks")
  set(COVERAGE TRUE CACHE BOOL "Enable code coverage checks")
endif()

# Optional strict mode in reference environment
if(UNIX AND CMAKE_COMPILER_IS_GNUCXX AND STRICT)
  message("-- Enabling strict compilation mode")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()

# In the reference environment enable memory checking on tests
if(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX AND MEMORY)
  message("-- Enabling valgrind memory check")
  add_custom_target(memory
    COMMAND valgrind ${CMAKE_BINARY_DIR}/unittests
  )
endif()

# Run clang-tidy on all .cpp files
if(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX AND TIDY)
  message("-- Enabling clang-tidy check")
  add_custom_target(tidy
    COMMAND ${CMAKE_COMMAND} -E env "ROOT=${CMAKE_CURRENT_SOURCE_DIR}"
    ${CMAKE_CURRENT_SOURCE_DIR}/scripts/tidy.sh
  )
endif()


# Compile erl binary
add_executable(erl main.cpp ${LIB_SOURCE})

# Compile unittests binary
add_executable(unittests catch.hpp ${TEST_SOURCE} ${LIB_SOURCE})

# # Find and link ICU libraries
# find_package(ICU REQUIRED COMPONENTS uc i18n)
# target_include_directories(erl PRIVATE ${ICU_INCLUDE_DIRS})
# target_link_libraries(erl PRIVATE ${ICU_LIBRARIES})
# target_include_directories(unittests PRIVATE ${ICU_INCLUDE_DIRS})
# target_link_libraries(unittests PRIVATE ${ICU_LIBRARIES})

# Enable code coverage generation
if(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX AND COVERAGE)
  message("-- Enabling code coverage")
  set(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
  set_target_properties(unittests PROPERTIES COMPILE_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS} )
  target_link_libraries(unittests PRIVATE gcov)
  add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} -E env "ROOT=${CMAKE_CURRENT_SOURCE_DIR}"
    ${CMAKE_CURRENT_SOURCE_DIR}/scripts/coverage.sh)
endif()

# Copy testing files to build directory automatically
if(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX)
  # Assume Linux Docker
  file(COPY ${CMAKE_SOURCE_DIR}/tests/ DESTINATION ${CMAKE_BINARY_DIR})
else()
  # Assume Windows Visual Studio
  file(COPY ${CMAKE_SOURCE_DIR}/tests/ DESTINATION ${CMAKE_BINARY_DIR}/Debug)
endif()
