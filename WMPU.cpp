/////////////////////////////////////////////////////////////////////////
//
//  Here we implemente the functions of the abtract class of the interface 
//
/////////////////////////////////////////////////////////////////////////
#include "WMPU.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// Constructor for the WMPU class.
WMPU::WMPU(IeepromMPU& ieepromMPU)
    : eepromMngr(ieepromMPU)
{
}

// Function to initialize the MPU6050 sensor.
int WMPU::begin() {
    // Join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // Set I2C clock to 400kHz 
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // Initialize MPU6050 and check connection status
    nsMPU::mpu.initialize();
    return nsMPU::mpu.testConnection();
}

// Initialize the WMPU sensor.
void WMPU::Init() {
    int8_t devStatus = begin();
    if (devStatus == 0) {
        if (isCalibrated()) {
            loadCalibration();
            nsMPU::mpu.setDMPEnabled(true);
        } else {
            // MPU not calibrated, halt execution
            Serial.println("MPU not calibrated, halting execution");
            while (true) {
                // Failure: No calibration
            }
        }
    } else {
        // Bad devStatus, halt execution
        Serial.println("bad devStatus, halting execution");
        while (true) {
            // Failure
        }
    }
}

// Get the yaw, pitch, and roll angles from the MPU6050 sensor.
void WMPU::get_yaw_pitch_roll(float& y, float& p, float& r) {
    uint8_t fifoBuffer[64]; // FIFO storage buffer
    Quaternion q;           // [w, x, y, z] quaternion container
    if (nsMPU::mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { // Get the latest packet
        nsMPU::mpu.dmpGetQuaternion(&q, fifoBuffer);

        float q0 = q.w;
        float q1 = q.x;
        float q2 = q.y;
        float q3 = q.z;

        // Calculate yaw, pitch, and roll from quaternion data
        float yr = -atan2(-2 * q1 * q2 + 2 * q0 * q3, q2 * q2 - q3 * q3 - q1 * q1 + q0 * q0);
        float pr = asin(2 * q2 * q3 + 2 * q0 * q1);
        float rr = atan2(-2 * q1 * q3 + 2 * q0 * q2, q3 * q3 - q2 * q2 - q1 * q1 + q0 * q0);

        // Convert angles from radians to degrees
        y = yr * 180 / M_PI;
        p = pr * 180 / M_PI;
        r = rr * 180 / M_PI;
    }
}

// Function to set initial gyroscope offsets for the MPU6050 sensor.
void WMPU::guess_offsets() {
    // Supply your own gyro offsets here, scaled for minimum sensitivity
    nsMPU::mpu.setXGyroOffset(220);
    nsMPU::mpu.setYGyroOffset(76);
    nsMPU::mpu.setZGyroOffset(-85);
    nsMPU::mpu.setZAccelOffset(1788);
}

// Function to load calibration data from EEPROM into the MPU6050 sensor.
void WMPU::loadCalibration() {
    nsMPU::mpu.setXGyroOffset(eepromMngr.getXGyroOffset());
    nsMPU::mpu.setYGyroOffset(eepromMngr.getYGyroOffset());
    nsMPU::mpu.setZGyroOffset(eepromMngr.getZGyroOffset());
    nsMPU::mpu.setXAccelOffset(eepromMngr.getXAccelOffset());
    nsMPU::mpu.setYAccelOffset(eepromMngr.getYAccelOffset());
    nsMPU::mpu.setZAccelOffset(eepromMngr.getZAccelOffset());
}


void WMPU::Calibrate(){
    Serial.println("assuming module is flate and still!!!!!!!!");
    int8_t devStatus = begin();
    if(devStatus == 0){
        nsMPU::mpu.CalibrateAccel(6);
        nsMPU::mpu.CalibrateGyro(6);

        // Save calibration offsets to EEPROM manager
        eepromMngr.setXGyroOffset(nsMPU::mpu.getXGyroOffset());
        eepromMngr.setYGyroOffset(nsMPU::mpu.getYGyroOffset());
        eepromMngr.setZGyroOffset(nsMPU::mpu.getZGyroOffset());
        eepromMngr.setXAccelOffset(nsMPU::mpu.getXAccelOffset());
        eepromMngr.setYAccelOffset(nsMPU::mpu.getYAccelOffset());
        eepromMngr.setZAccelOffset(nsMPU::mpu.getZAccelOffset());
        eepromMngr.setCalibFlag();
        Serial.println("calibration complete");
    }
    else{
        Serial.println("bad devStatus, halting execution");
        while(true){
            //faillure
        }
    }
}
bool WMPU::isCalibrated(){
    return eepromMngr.getCalibFlag();
}
void WMPU::resetCalibFlag(){
    eepromMngr.resetCalibFlag();
}
