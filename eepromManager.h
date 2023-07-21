/////////////////////////////////////////////////////////
//the implementation of the Interface eeprom manager class
/////////////////////////////////////////////////////////
#pragma once

#include"IeepromMPU.h"
class eepromManager : public IeepromMPU{
    enum OffsetAddr{
        AddrxgyroE = 2,
        AddrygyroE = 4,
        AddrzgyroE = 6,
        AddrxAccelE = 8,
        AddryAccelE = 10,
        AddrzAccelE = 12
    };
    const int CalibFlagAddr = 0;
    const int CalibFlagTrue = 77;
    const int CalibFlagFalse = 0;

    int ReadIntFromEeprom(int adresse);
    void WriteIntToEeprom(int adresse,int value);

    virtual int getXGyroOffset() override;
    virtual int getYGyroOffset() override;
    virtual int getZGyroOffset() override;
    virtual int getXAccelOffset() override;
    virtual int getYAccelOffset() override;
    virtual int getZAccelOffset() override;


    virtual void setXGyroOffset(int os) override;
    virtual void setYGyroOffset(int os) override;
    virtual void setZGyroOffset(int os) override;
    virtual void setXAccelOffset(int os) override;
    virtual void setYAccelOffset(int os) override;
    virtual void setZAccelOffset(int os) override;

        
    virtual bool getCalibFlag()override;
    virtual void setCalibFlag() override;//sets it to true value
    virtual void resetCalibFlag() override;//sets it to false value
};
