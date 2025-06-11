cmake_minimum_required(VERSION 3.16)
project(ros2_control_demo_example_1 LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra)
endif()

# set the same behavior for windows as it is on linux
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# find dependencies
set(THIS_PACKAGE_INCLUDE_DEPENDS
  hardware_interface
  pluginlib
  rclcpp
  rclcpp_lifecycle
  position_controllers
)

# find dependencies
find_package(backward_ros REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()

## COMPILE
add_library(
  ros2_control_demo_example_1
  SHARED
  hardware/rrbot.cpp
  hardware/sdk/src/FashionStar_UartServo.cpp
  hardware/sdk/src/FashionStar_UartServoProtocol.cpp
  hardware/sdk/dependency/CSerialPort/src/SerialPort.cpp
  hardware/sdk/dependency/CSerialPort/src/SerialPortBase.cpp
  hardware/sdk/dependency/CSerialPort/src/SerialPortInfo.cpp
  hardware/sdk/dependency/CSerialPort/src/SerialPortInfoBase.cpp
  hardware/sdk/dependency/CSerialPort/src/SerialPortInfoUnixBase.cpp
  hardware/sdk/dependency/CSerialPort/src/SerialPortUnixBase.cpp
)
target_compile_features(ros2_control_demo_example_1 PUBLIC cxx_std_17)
target_include_directories(ros2_control_demo_example_1 PUBLIC
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/hardware/include>
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/hardware/sdk/include>
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/hardware/sdk/dependency/CSerialPort/include>
$<INSTALL_INTERFACE:include/ros2_control_demo_example_1>
)
ament_target_dependencies(
  ros2_control_demo_example_1 PUBLIC
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)

# Export hardware plugins
pluginlib_export_plugin_description_file(hardware_interface ros2_control_demo_example_1.xml)

# INSTALL
install(
  DIRECTORY hardware/include/
  DESTINATION include/ros2_control_demo_example_1
)
# Install URDF files
install(
  DIRECTORY description/urdf/
  DESTINATION share/ros2_control_demo_example_1/description
)
# Install launch and config files
install(
  DIRECTORY bringup/launch/
  DESTINATION share/ros2_control_demo_example_1/launch
)
install(
  DIRECTORY bringup/config/
  DESTINATION share/ros2_control_demo_example_1/config
)
install(TARGETS ros2_control_demo_example_1
  EXPORT export_ros2_control_demo_example_1
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)

  ament_add_pytest_test(example_1_urdf_xacro test/test_urdf_xacro.py)
  ament_add_pytest_test(view_example_1_launch test/test_view_robot_launch.py)
  ament_add_pytest_test(run_example_1_launch test/test_rrbot_launch.py)
  ament_add_pytest_test(run_example_1_launch_cli_direct test/test_rrbot_launch_cli_direct.py)
endif()


## EXPORTS
ament_export_targets(export_ros2_control_demo_example_1 HAS_LIBRARY_TARGET)
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_package()
