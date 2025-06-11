#include <iostream>
#include <chrono>
#include <thread>
#include "../sdk/include/FashionStar_UartServo.h"

using namespace fsuservo;

int main() {
    // Create protocol instance
    FSUS_Protocol protocol("/dev/ttyUSB0", itas109::BaudRate::BaudRate115200);
    
    // Create servo instance with ID 2
    FSUS_Servo servo(2, &protocol);
    
    // Initialize servo
    servo.init();
    
    if (!servo.isOnline) {
        std::cout << "Servo is not online!" << std::endl;
        return -1;
    }
    
    std::cout << "Servo is online!" << std::endl;
    
    // Test basic movement
    std::cout << "Moving to 0 degrees..." << std::endl;
    servo.setAngle(0.0, 1000); // Move to 0 degrees in 1 second
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "Moving to 90 degrees..." << std::endl;
    servo.setAngle(90.0, 1000); // Move to 90 degrees in 1 second
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "Moving to 180 degrees..." << std::endl;
    servo.setAngle(180.0, 1000); // Move to 180 degrees in 1 second
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "Moving back to 0 degrees..." << std::endl;
    servo.setAngle(0.0, 1000); // Move back to 0 degrees in 1 second
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "Test completed!" << std::endl;
    return 0;
} 