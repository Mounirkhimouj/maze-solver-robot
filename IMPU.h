#pragma once

// IMPU  User Interface of Motion Processing Unit (MPU6050)
// all functions should be implemented in the concrete class
class IMPU {
public:
    // Initialize the MPU sensor.
    //to initialize the sensor and any necessary settings.
    virtual void Init() = 0;

    // Get the yaw, pitch, and roll angles from the MPU sensor.
    // y: reference to store the yaw angle (rotation around the vertical axis).
    // p: reference to store the pitch angle (rotation around the lateral axis).
    // r: reference to store the roll angle (rotation around the longitudinal axis).
    virtual void get_yaw_pitch_roll(float& y, float& p, float& r) = 0;

    // Calibrate the MPU sensor if required.
    virtual void Calibrate() = 0;

    // Check if the MPU sensor is calibrated.
    // returns: true if the sensor is calibrated, false otherwise.
    virtual bool isCalibrated() = 0;

    // Reset the calibration offests of MPU sensor.
    virtual void resetCalibFlag() = 0;
};
