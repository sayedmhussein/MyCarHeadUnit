


#include "HeadUnit.h"

HeadUnit::HeadUnit() {
    allowedToControlHeadUnit = 0;
    currentButton_1 = 0;
    currentButton_2 = 0;
    currentSteering_1 = 0;
    currentSteering_2 = 0;
}


void HeadUnit::allow() {
    allowedToControlHeadUnit = 1;
}
void HeadUnit::disable() {
    allowedToControlHeadUnit = 0;
}


void HeadUnit::setCurrentTime(unsigned long currentTime) {
    this->currentTime = currentTime;
}

void HeadUnit::setSteeringInput_1(int value, bool isDefault, int defaultTolerance) {
    if (isDefault == 0) currentSteering_1 = value;
    else currentSteering_1_default = value;
    
    currentSteering_1_tolerance = defaultTolerance;
}

void HeadUnit::setSteeringInput_2(int value, bool isDefault, int defaultTolerance) {
    if (isDefault == 0) currentSteering_2 = value;
    else currentSteering_2_default = value;
    
    currentSteering_2_tolerance = defaultTolerance;
}

void HeadUnit::setButtonInput_1(int value, bool isDefault, int defaultTolerance) {
    if (isDefault == 0) currentButton_1 = value;
    else currentButton_1_default = value;
    
    currentButton_1_tolerance = defaultTolerance;
}

void HeadUnit::setButtonInput_2(int value, bool isDefault, int defaultTolerance) {
    if (isDefault == 0) currentButton_2 = value;
    else currentButton_2_default = value;
    
    currentButton_2_tolerance = defaultTolerance;
}


int HeadUnit::getCommand() {
    
    //Special Commands
    if (allowedToControlHeadUnit == LOW) return COMMAND::VOID;
    
    //  We've 4 sources of inputs
    //  We'll scan each one and if found then return the function
    
    //Set Button Current Value, then check for feedbacks
    //..
    
    //  Button 1:
    power.setCurrentValues(BUTTON_1, currentTime);
    if (power.isShortPress()) return COMMAND::SLEEP;
    else if (power.isLongPress()) return COMMAND::SHUTDOWN;
    
    volumeMute.setCurrentValues(BUTTON_1, currentTime);
    if (volumeMute.isShortPress()) return COMMAND::MUTE;
    
    
    //  Button 2:
    next.setCurrentValues(BUTTON_2, currentTime);
    if (next.isShortPress()) return COMMAND::NEXT;
    else if (next.isLongPress()) return COMMAND::FWD;
    
    prev.setCurrentValues(BUTTON_2, currentTime);
    if (prev.isShortPress()) return COMMAND::PREV;
    else if (prev.isLongPress()) return COMMAND::RVS;
    
    eject.setCurrentValues(BUTTON_2, currentTime);
    if (eject.isShortPress()) return COMMAND::ESCAPE;
    
    home.setCurrentValues(BUTTON_2, currentTime);
    if (home.isShortPress()) return COMMAND::HOME;
    
    back.setCurrentValues(BUTTON_2, currentTime);
    if (back.isShortPress()) return COMMAND::BACK;
    else if (back.isLongPress()) return COMMAND::ESCAPE;
    
    
    //Steering 1:
    volumeUpSteering.setCurrentValues(STEERING_1, currentTime);
    if (volumeUpSteering.isShortPress()) return COMMAND::VOL_U;
    
    volumeDnSteering.setCurrentValues(STEERING_1, currentTime);
    if (volumeDnSteering.isShortPress()) return COMMAND::VOL_D;
    else if (volumeDnSteering.isLongPress()) return COMMAND::LOGIN;
    
    nextSteering.setCurrentValues(STEERING_1, currentTime);
    if (nextSteering.isShortPress()) return COMMAND::NEXT;
    else if (nextSteering.isLongPress()) return COMMAND::FWD;
    
    prevSteering.setCurrentValues(STEERING_1, currentTime);
    //
    if (prevSteering.isShortPress()) return COMMAND::PREV;
    else if (prevSteering.isLongPress()) return COMMAND::RVS;

    muteSteering.setCurrentValues(STEERING_2, currentTime);
    if (muteSteering.isShortPress()) return COMMAND::MUTE;
    else if (muteSteering.isLongPress()) return COMMAND::PAUSE;
    
    
    //If neither of the above:
    return COMMAND::VOID;
}

