

#include "Button.h"

Button::Button() {}

void Button::setSource(int Source) {
    buttonSource = Source;
}

void Button::setValue(int value) {
    buttonValue_registered = value;
}

void Button::setTolerance(int tolerance) {
    buttonTolerance = tolerance;
}

void Button::setBounceTime(unsigned long bounceTime) {
    p_bounceTime = bounceTime;
}

void Button::setShortPress_time(unsigned long time_ms) {
    shortPressTime = time_ms;
}

void Button::setLongPress_time(unsigned long time_ms) {
    longPressTime = time_ms;
}

void Button::setSwitchingTime(unsigned long time_ms) {
    switchingTime = time_ms;
}


void Button::setCurrentValues(int currentValue, unsigned long currentTime) {
    
    if ((currentValue < p_minimumValue) || (currentValue > p_maximumValue)) {
        p_onRange = LOW;
        p_stillOnRange = LOW;
        p_currentValue = p_defaultValue;
    }
    
    else {
        
        if (p_onRange == LOW) {
            p_firstTimeOnRange = currentTime;
            p_onRange = HIGH;
        }
        
        if (currentTime > (p_firstTimeOnRange + p_bounceTime)) {
            p_stillOnRange = HIGH;
        }
        
        
    }
}


bool Button::isShortPress() {
    if (p_shortPress) {
        p_shortPress = LOW;
        return HIGH;
    }
    else return LOW;
}

bool Button::isLongPress() {
    if (p_longPress) {
        p_longPress = LOW;
        return HIGH;
    }
    else return LOW;
}


void Button::setPressType() {
    
    static bool buttonPressed = LOW;
    static bool buttonPressedForLongTime = LOW;
    
    if (p_stillOnRange) buttonPressed = HIGH;
    
    if (buttonPressed && (currentTime > (p_firstTimeOnRange + p_longPressTime))) buttonPressedForLongTime = HIGH;
    else buttonPressedForLongTime = LOW;
    
    
    if (!p_stillOnRange && buttonPressed && !buttonPressedForLongTime) p_shortPress = HIGH;
    else if (p_stillOnRange && buttonPressedForLongTime) p_longPressTime = HIGH;
    else {
        p_shortPress = LOW;
        p_longPress = LOW;
    }
        
    if (!p_stillOnRange) buttonPressed = LOW;
}




bool Button::inRange() {
    static bool isInRange = 0;
    if (abs(buttonValue_registered - buttonValue_current) < buttonTolerance) {
        if (isInRange == 0) {
            isInRange = 1;
            timeOnRange = currentTime;
        }
        
        if (currentTime > (timeOnRange + longPressTime)) {
            //  A long press.
        }
    }
    else {
        if (currentTime < (timeOnRange + longPressTime)) {
            if (currentTime > (timeOnRange + shortPressTime)) {
                if (isInRange == 1) {
                    //  A short Press falling edge...
                    isShortPress_p = 1;
                    return 1;
                }
            }
        }
        isInRange = 0;
    }
    return 0;
}
