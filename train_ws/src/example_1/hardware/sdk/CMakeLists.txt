cmake_minimum_required(VERSION 3.8)
project(fsuservo)

# Find required packages
find_package(Threads REQUIRED)

# Add CSerialPort dependency
add_subdirectory(dependency/CSerialPort)

# Add library
add_library(fsuservo
    src/FashionStar_UartServo.cpp
    src/FashionStar_UartServoProtocol.cpp
)

# Include directories
target_include_directories(fsuservo
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependency/CSerialPort/include
)

# Link libraries
target_link_libraries(fsuservo
    PRIVATE
    libcserialport
    Threads::Threads
) 