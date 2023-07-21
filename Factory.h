#pragma once
#include"IMPU.h"
#include"WMPU.h"
#include"eepromManager.h"
class Factory{
    private:
        eepromManager eepromMngr;
        WMPU mpu = WMPU(eepromMngr);
    public:
        IMPU& getMPU();
}; 