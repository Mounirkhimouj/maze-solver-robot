//////////////////////////////////////////////////////////////////////////////////////
//  Date   : 05/2023
//  Developpers : Ouaaddi Mohamedbahae , khimouj Mounir , Nabil Oulhaj , Hicham Redone
//  Institution: National School of Applied Sciences, University of Cadi Ayyad,
//               Marrakech, Morocco
//
//  Description: Wall Following Algorithm
//  The robot attempts to follow a right wall (right turning is not the priority in 
//  if statements).
//  Some specifications have been added to the algorithm to match the design of the
//  maze in a competition.
//  Notes: Serial.print methods are for debugging purposes.
//        .
/////////////////////////////////////////////////////////////////////////////////////

// Include necessary libraries and header files
#include "IMPU.h"
#include "Factory.h"
#include "AFMotor.h"
#include "filter.h"
#include "PID.h"
#include "Ultrasonic.h"

// Define the pins for ultrasonic sensors
#define TRIGGER_PIN_front A0
#define ECHO_PIN_front A1
#define TRIGGER_PIN_left A2
#define ECHO_PIN_left A3

// Create Ultrasonic objects for front and left sensors
Ultrasonic sonar_front(TRIGGER_PIN_front, ECHO_PIN_front);
Ultrasonic sonar_left(TRIGGER_PIN_left, ECHO_PIN_left);

// Create instances for the IMPU, motors, and filters
Factory config;
IMPU& mpu = config.getMPU();

AF_DCMotor motor_r(1);
AF_DCMotor motor_l(2);

filter gyro_filter(5, 20, -1);

PID pid(3, 0, 30, 10, 10, -300, 300);

// Set motor speed
int mtrSpd = 150;

// Function to move the robot straight
void straight_movement() {
    float y, p, r, a;
    motor_r.run(FORWARD);
    motor_l.run(FORWARD);
    mpu.get_yaw_pitch_roll(y, p, r);
    a = gyro_filter.filtering(y);
    float s = pid.Update(a, 0);
    float right = constrain(mtrSpd + s, 0, 200);
    float left = constrain(mtrSpd - s, 0, 200);
    motor_r.setSpeed(right);
    motor_l.setSpeed(left);
    float d = sonar_left.read();
    float b = sonar_front.read();
    //Serial.print("raw angle  :");
    //Serial.print(y);
    //Serial.print('\t');
    //float t = (float)millis()/1000.0;
    //Serial.print(t);
    //Serial.print("filtred angle  :");
    //Serial.print(a);
    //Serial.print("  ");
    //Serial.print(s);
    //Serial.print("  ");
    //Serial.print("  right motor   : ");
    //Serial.print(right);
    //Serial.print("  ");
    //Serial.print("  left motor   : ");
    //Serial.print(left);
    //Serial.print("  ");
    //Serial.print("  left distance   : ");
    //Serial.print(d);
    //Serial.print("  ");
    //Serial.print("  front distance   : ");
    //Serial.println(b);
}
}

// Function to perform right turning
void right_turning(){
    Serial.println(" RIGHT TURNING  ");
    float y,p,r,a;
    mpu.get_yaw_pitch_roll(y,p,r);
    a=y;
    while(a<80){
        motor_r.run(RELEASE);
        motor_l.run(FORWARD);
        mpu.get_yaw_pitch_roll(y,p,r);
        a=y;
        Serial.print("RIGHT ANGLE ");
        Serial.println(a);
    }
}

// Function to perform left turning
void left_turning() {
    Serial.println(" LEFT TURNING  ");
    float y, p, r, a;
    mpu.get_yaw_pitch_roll(y, p, r);
    a = y;
    while (y > -80) {
        motor_l.run(RELEASE);
        motor_r.run(FORWARD);
        mpu.get_yaw_pitch_roll(y, p, r);
        a = y;
        Serial.print("LEFT ANGLE ");
        Serial.println(a);
    }
}

void setup() {
    // Initialize serial communication and wait until connected
    Serial.begin(115200);
    while (!Serial);
    
    // Calibrate the MPU and initialize it
    mpu.Calibrate();
    mpu.Init();
    
    // Set motors to run forward
    motor_r.run(FORWARD);
    motor_l.run(FORWARD);
}

void loop() {
    straight_movement(); // If there is no wall in front, drive straight
    
    if (sonar_front.read() < 20) { // If there is a wall in front
        motor_r.run(RELEASE);
        motor_l.run(RELEASE);
        delay(1000);
        if (sonar_left.read() < 10) { // If there is a wall on the left, drive right
            right_turning();
        } else { // If there is no wall on the left, drive left
            left_turning();
        }
        
        // Stop motors and reinitialize the MPU
        motor_r.run(RELEASE);
        motor_l.run(RELEASE);
        mpu.Calibrate();
        mpu.Init();
    }
}
