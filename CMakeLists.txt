cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)

project(TPOOL VERSION 1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME}_LIB SHARED
    thread_pool.cpp
)
target_link_libraries(${PROJECT_NAME}_LIB pthread)

# Add the executable
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_NAME}_LIB
)


# Add compiler warnings (as errors) and other warning flags
target_compile_options(${PROJECT_NAME} PRIVATE
    -Werror
    -Wall
    -Wextra
    -Wconversion
    -Wsign-conversion
)


option(BUILD_TESTS "Build tests" ON)


if(BUILD_TESTS)
    enable_testing()    
    find_package(GTest REQUIRED)


    # Add the test executable
    add_executable(${PROJECT_NAME}_test test_thread_pool.cpp)

    # Link the test executable with Google Test and the thread pool library
    target_link_libraries(${PROJECT_NAME}_test 
        PRIVATE 
        GTest::gtest 
        GTest::gtest_main 
        ${PROJECT_NAME}_LIB
    )

endif()


