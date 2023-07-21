#pragma once

#include "IMPU.h"
#include "IeepromMPU.h"

// WMPU class: Represents a specific implementation of an interface of Motion Processing Unit (MPU).
//here we add a library wrapper over the MPU6050 linrary for our spesific application
class WMPU : public IMPU {
public:
    // Constructor for the WMPU class.
    // ieepromMPU: A reference to an instance of the IeepromMPU class for managing EEPROM data (calibration data).
    // the WMPU interacte with eeprom manager via IeepromMPU
    WMPU(IeepromMPU& ieepromMPU);

    virtual void Init() override;
    virtual void get_yaw_pitch_roll(float& y, float& p, float& r) override;
    virtual void Calibrate() override;
    virtual bool isCalibrated() override;
    virtual void resetCalibFlag() override;

private:
    // A reference to the IeepromMPU instance used for managing EEPROM data (calibration data).
    IeepromMPU& eepromMngr;

    // Function to guess the sensor's offsets (internal calibration).
    void guess_off_sets();

    // Function to load calibration data from EEPROM (if available).
    void loadCalibration();

    // Function to calibration the sensor 
    int begin();
};
