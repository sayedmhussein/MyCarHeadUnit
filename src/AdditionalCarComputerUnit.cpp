//
//  AdditionalCarComputerUnit.cpp
//  CarProject
//
//  Created by Sayed Hussein on 27/10/2018.
//  Copyright © 2018 Sayed Hussein. All rights reserved.
//
#include "AdditionalCarComputerUnit.h"


AdditionalCarComputerUnit::AdditionalCarComputerUnit() {
    //  The constructor, set all values to default..
    carKeyInserted = LOW;
    autoHeadLightsActive = LOW;
    lightsOn = LOW;
    headLightsOn = LOW;
    hightHeadLightsOn = LOW;
    //
    state = STATE::ON;
    //
    currentTime = 0;
    waitingTime = 0;
    shutdownTime = 0;
    restartTime = 0;
    
}

void AdditionalCarComputerUnit::userPutCarKey() {
    carKeyInserted = HIGH;
}

void AdditionalCarComputerUnit::userRemovedCarKey() {
    carKeyInserted = LOW;
}

void AdditionalCarComputerUnit::userTurnedOffAllLights() {
    autoHeadLightsActive = LOW;
    lightsOn = LOW;
    headLightsOn = LOW;
    hightHeadLightsOn = LOW;
}
//

void AdditionalCarComputerUnit::userSetLightsToAuto() {
    autoHeadLightsActive = HIGH;
}
//

void AdditionalCarComputerUnit::userTurnedOnLights() {
    lightsOn = HIGH;
}

void AdditionalCarComputerUnit::userTurnedOnHeadLights() {
    headLightsOn = HIGH;
}
//

void AdditionalCarComputerUnit::userTurnedOnHighHeadLights() {
    hightHeadLightsOn = HIGH;
}
void AdditionalCarComputerUnit::userTurnedOffHighHeadLights() {
    hightHeadLightsOn = LOW;
}


void AdditionalCarComputerUnit::setCurrentTime(unsigned long currentTime_ms) {
    currentTime = currentTime_ms;
}
//

void AdditionalCarComputerUnit::setWaitingTime(unsigned long waitingTime_ms) {
    waitingTime = waitingTime_ms;
}

void AdditionalCarComputerUnit::setShutdownTime(unsigned long shutdownTime_ms) {
    shutdownTime = shutdownTime_ms;
}

void AdditionalCarComputerUnit::setRestartTime(unsigned long restartTime_ms) {
    restartTime = restartTime_ms;
}

bool AdditionalCarComputerUnit::keepPowerSupplyOn() {
    switch (state) {
        case STATE::ON:
            if (carKeyInserted != 0) state = STATE::ON;
            else {
                waitingTime_saved = currentTime;
                state = STATE::WAITING;
            }
            
            break;
        
        case STATE::OFF:
            if (currentTime > (restartTime + restartTime_saved)) {
                if (carKeyInserted != 0) state = STATE::ON;
            }
            break;
            
        case STATE::WAITING:
            if (carKeyInserted != 0) state = STATE::ON;
            else {
                if (currentTime > (waitingTime + waitingTime_saved)) {
                    state = STATE::SHUTTING;
                    shutdownTime_saved = currentTime;
                }
            }
            break;
            
        case STATE::SHUTTING:
            if (currentTime > (shutdownTime + shutdownTime_saved)) {
                state = STATE::OFF;
                restartTime_saved = currentTime;
            }
            break;
            
        default:
            //  Should report error.
            state = STATE::ON;
            break;
    }
    
    switch (state) {
        case STATE::ON:
        case STATE::WAITING:
        case STATE::SHUTTING:
            return 1;
            break;
            
        default:
            return 0;
            break;
    }
}
//
bool AdditionalCarComputerUnit::carIsOn() {
    if (carKeyInserted == 0) return 0;
    else return 1;
}
//
bool AdditionalCarComputerUnit::isLightsOn() {
    if (lightsOn == 0) return 0;
    else return 1;
}

bool AdditionalCarComputerUnit::isNightTravelMode() {
    //For future implemenation.
    return 0;
}
