
#ifdef ARDUINO
//#include "Arduino.h"
#else
#include <cmath>
#include <cstdlib>
using namespace std;
#define LOW 0
#define HIGH 1
#endif

#include "Button.h"

#ifndef HEADUNIT_H
#define HEADUNIT_H

class HeadUnit {
public:
    HeadUnit();
    
    void allow();
    void disable();
    
    void setCurrentTime(unsigned long currentTime);
    
    void setSteeringInput_1(int value, bool isDefault = 0, int defaultTolerance = 20);
    void setSteeringInput_2(int value, bool isDefault = 0, int defaultTolerance = 20);
    void setButtonInput_1(int value, bool isDefault = 0, int defaultTolerance = 20);
    void setButtonInput_2(int value, bool isDefault = 0, int defaultTolerance = 20);
    
    
    enum COMMAND {VOID, SHUTDOWN, SLEEP, VOL_U, VOL_D, NEXT, PREV, FWD, RVS, PAUSE, MUTE, LOGIN, \
        ESCAPE, HOME, BACK};
    int getCommand();
    
    enum COMMAND_SOURCE {STEERING_1, STEERING_2, BUTTON_1, BUTTON_2};
    
    Button power;
    Button volumeUp;
    Button volumeDn;
    Button volumeMute;
    Button navigation;
    Button dvd;
    
    Button next;
    Button prev;
    Button eject;
    Button home;
    Button back;
    
    Button volumeUpSteering;
    Button volumeDnSteering;
    Button nextSteering;
    Button prevSteering;
    
    Button muteSteering;
    
    
    
private:
    bool allowedToControlHeadUnit;
    unsigned long currentTime;
    int currentButton_1, currentButton_2, currentSteering_1, currentSteering_2;
    int currentButton_1_default, currentButton_2_default, currentSteering_1_default, currentSteering_2_default;
    int currentButton_1_tolerance, currentButton_2_tolerance, currentSteering_1_tolerance, currentSteering_2_tolerance;
    
};
#endif
