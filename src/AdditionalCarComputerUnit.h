//
//  AdditionalCarComputerUnit.h
//  CarProject
//
//  Created by Sayed Hussein on 27/10/2018.
//  Copyright © 2018 Sayed Hussein. All rights reserved.
//
//  Will manage the power supply to the computer.
//  Will be the interface between the car and the computer.

#define LOW 0
#define HIGH 1

#ifndef ADDITIONAL_CAR_COMPUTER_UNIT_H
#define ADDITIONAL_CAR_COMPUTER_UNIT_H

class AdditionalCarComputerUnit {
public:
    AdditionalCarComputerUnit();
    
    //  Parameters
    //  Executed on the setup function
    void setWaitingTime(unsigned long waitingTime_ms);
    void setShutdownTime(unsigned long shutdownTime_ms);
    void setRestartTime(unsigned long restartTime_ms);
    
    
    //  Power management for the controller
    //  Must used functions
    void setCurrentTime(unsigned long currentTime_ms);
    bool keepPowerSupplyOn(); //To ensure power supply for the PCB.
    
    
    //  Car Entry 
    void userPutCarKey();
    void userRemovedCarKey();
    bool carIsOn();
    
    
    void userTurnedOffAllLights();
    //
    void userSetLightsToAuto();
    //
    void userTurnedOnLights();
    void userTurnedOnHeadLights();
    //
    void userTurnedOnHighHeadLights();
    void userTurnedOffHighHeadLights();
    //
    bool isLightsOn();
    bool isNightTravelMode();
    //
    
    
private:
    bool carKeyInserted;
    bool autoHeadLightsActive;
    bool lightsOn, headLightsOn, hightHeadLightsOn;
    //
    enum STATE {ON, WAITING, SHUTTING, OFF};
    int state;
    //
    unsigned long currentTime, waitingTime, shutdownTime, restartTime;
    unsigned long waitingTime_saved, shutdownTime_saved, restartTime_saved;
    //
    
};

#endif
