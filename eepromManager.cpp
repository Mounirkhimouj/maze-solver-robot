#include"Arduino.h"
#include"EEPROM.h"
#include"eepromManager.h"

int eepromManager::ReadIntFromEeprom(int adresse){
    int val;
    val = EEPROM.read(adresse);
    val |= EEPROM.read(adresse + 1) << 8 ;
    return val; 
}
void eepromManager::WriteIntToEeprom(int adresse,int value){
    EEPROM.update(adresse,value& 0xff);
    EEPROM.update(adresse + 1 ,value >> 8);
}


int eepromManager::getXGyroOffset(){
    return ReadIntFromEeprom(AddrxgyroE);
}
int eepromManager::getYGyroOffset(){
    return ReadIntFromEeprom(AddrygyroE);
}
int eepromManager::getZGyroOffset(){
    return ReadIntFromEeprom(AddrzgyroE);
}
int eepromManager::getXAccelOffset(){
    return ReadIntFromEeprom(AddrxAccelE);
}
int eepromManager::getYAccelOffset(){
    return ReadIntFromEeprom(AddryAccelE);
}
int eepromManager::getZAccelOffset(){
    return ReadIntFromEeprom(AddrzAccelE);
}


void eepromManager::setXGyroOffset(int os){
    WriteIntToEeprom(AddrxgyroE,os);
}
void eepromManager::setYGyroOffset(int os){
    WriteIntToEeprom(AddrygyroE,os);
}
void eepromManager::setZGyroOffset(int os){
    WriteIntToEeprom(AddrzgyroE,os);
}
void eepromManager::setXAccelOffset(int os){
    WriteIntToEeprom(AddrxAccelE,os);
}
void eepromManager::setYAccelOffset(int os){
    WriteIntToEeprom(AddryAccelE,os);
}
void eepromManager::setZAccelOffset(int os){
    WriteIntToEeprom(AddrzAccelE,os);
}


bool eepromManager::getCalibFlag(){
    return (ReadIntFromEeprom(CalibFlagAddr) == CalibFlagTrue);
}
void eepromManager::setCalibFlag(){
    WriteIntToEeprom(CalibFlagAddr,CalibFlagTrue);
}
void eepromManager::resetCalibFlag(){
    WriteIntToEeprom(CalibFlagAddr,CalibFlagFalse);
    Serial.println("calibration flag reset");
}