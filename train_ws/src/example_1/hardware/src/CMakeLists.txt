cmake_minimum_required(VERSION 3.8)
project(servo_test)

# Find required packages
find_package(Threads REQUIRED)

# Add SDK library
add_subdirectory(../sdk ${CMAKE_CURRENT_BINARY_DIR}/sdk)

# Add executable
add_executable(servo_test servo_test.cpp)

# Link libraries
target_link_libraries(servo_test
    PRIVATE
    fsuservo
    libcserialport
    Threads::Threads
)

# Include directories
target_include_directories(servo_test
    PRIVATE
    ${CMAKE_SOURCE_DIR}/sdk/include
) 