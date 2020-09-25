#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <math.h>
#include <cstdlib>
#define LOW 0
#define HIGH 1
#endif


#ifndef BUTTON_H
#define BUTTON_H

class Button {
public:
    Button();
    
    //  In setup function:
    void setSource(int Source);
    void setValue(int value);
    void setTolerance(int tolerance);
    void setBounceTime(unsigned long);
    void setLongPressRepeatTime(unsigned long);
    
    void setShortPress_time(unsigned long time_ms);
    void setLongPress_time(unsigned long time_ms);
    void setSwitchingTime(unsigned long time_ms);
    
    
    //  In loop function
    void setCurrentValues(int , unsigned long );
    
    bool isShortPress();
    bool isLongPress();
    
private:
    int p_currentValue, p_minimumValue, p_maximumValue, p_defaultValue;
    bool p_onRange, p_stillOnRange;
    unsigned long p_firstTimeOnRange, p_bounceTime, p_longPressTime;
    int p_centerValue;
    
    bool p_shortPress, p_longPress;
    void setPressType();
    
    int buttonSource, buttonValue_registered, buttonValue_current, buttonValue_last, buttonTolerance;
    unsigned long currentTime, shortPressTime, longPressTime, timeOnRange, timePressed, switchingTime;
    bool buttonPressed, isShortPress_p, isLongPress_p;
    
    bool isStable();
    bool inRange();
    
};


#endif
