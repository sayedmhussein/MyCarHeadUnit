
#include "Constants.h"
#include "AdditionalCarComputerUnit.h"
#include "HeadUnit.h"
#include "Button.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include <HID-Project.h>
#include <HID-Settings.h>
#else
#include "ArduinoCpp.h"
#endif


AdditionalCarComputerUnit ACCU;
HeadUnit HU;


void setup() {
  // put your setup code here, to run once:

    ACCU.setWaitingTime(60000);
    ACCU.setShutdownTime(60000);
    ACCU.setRestartTime(20000);
    
    
    HU.setButtonInput_1(analogRead(PIN_BUTTON_1), HIGH);
    HU.setButtonInput_2(analogRead(PIN_BUTTON_2), HIGH);
    HU.setSteeringInput_1(analogRead(PIN_STEERING_1), HIGH);
    HU.setSteeringInput_2(analogRead(PIN_STEERING_2), HIGH);

    
    HU.volumeUp.setValue(100);
    HU.volumeUp.setTolerance(20);
    HU.volumeUp.setShortPress_time(300);
    HU.volumeUp.setLongPress_time(1500);
    //HU.volumeUp. = 100;
    //HU.volumeUp.tolerance = 20;
    //HU.volumeUp.source = HU.COMMAND_SOURCE::BUTTON_1;
    //  Add as you wish
    
    
    pinMode(PIN_KEY, INPUT);
    pinMode(PIN_ILL, INPUT);
    
    pinMode(PIN_POWER, OUTPUT);
    pinMode(PIN_AUX, OUTPUT);
    pinMode(PIN_AMP, OUTPUT);
    
    pinMode(PIN_LCD, OUTPUT);
    pinMode(PIN_R, OUTPUT);
    pinMode(PIN_G, OUTPUT);
    pinMode(PIN_B, OUTPUT);
    
    Consumer.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

    
    ACCU.setCurrentTime(millis());
    
    if (ACCU.keepPowerSupplyOn() == LOW) digitalWrite(PIN_POWER, LOW);
    else digitalWrite(PIN_POWER, HIGH);
    
    
    
    if (digitalRead(PIN_KEY) == HIGH) ACCU.userPutCarKey();
    else ACCU.userRemovedCarKey();
    
    
    
    if (ACCU.carIsOn() == HIGH) {
        digitalWrite(PIN_AUX, HIGH);
        digitalWrite(PIN_AMP, HIGH);
    }
    //
    else {
        digitalWrite(PIN_AUX, LOW);
        digitalWrite(PIN_AMP, LOW);
    }
    
    
    
    if (digitalRead(PIN_ILL) == LOW) ACCU.userTurnedOffAllLights();
    else ACCU.userTurnedOnLights();
    
    
    
    if (ACCU.isLightsOn() == LOW) {
        analogWrite(PIN_LCD, map(LCD_BRIGHTNESS_DAY, 0, 255, 0, 1023));
        analogWrite(PIN_R, 0);
        analogWrite(PIN_G, 0);
        analogWrite(PIN_B, 0);
    }
    //
    else if (ACCU.isNightTravelMode() == 0) {
        analogWrite(PIN_LCD, map(LCD_BRIGHTNESS_NIGHT, 0, 255, 0, 1023));
        analogWrite(PIN_R, map(R_BRIGHTNESS, 0, 255, 0, 1023));
        analogWrite(PIN_G, map(G_BRIGHTNESS, 0, 255, 0, 1023));
        analogWrite(PIN_B, B_BRIGHTNESS);
    }
    //
    else {
        analogWrite(PIN_LCD, map(LCD_BRIGHTNESS_NIGHT, 0, 255, 0, 1023) * (LCD_TRAVEL_PERCENTAGE / 100));
        analogWrite(PIN_R, map(R_BRIGHTNESS, 0, 255, 0, 1023) * (LED_TRAVEL_PERCENTAGE / 100));
        analogWrite(PIN_G, map(G_BRIGHTNESS, 0, 255, 0, 1023) * (LED_TRAVEL_PERCENTAGE / 100));
        analogWrite(PIN_B, map(B_BRIGHTNESS, 0, 255, 0, 1023) * (LED_TRAVEL_PERCENTAGE / 100));
    }

    
    
    
    if (ACCU.carIsOn() != 0) HU.allow();
    else HU.disable();
    
    
    
    HU.setCurrentTime(millis());
    
    HU.setButtonInput_1(analogRead(PIN_BUTTON_1));
    HU.setButtonInput_2(analogRead(PIN_BUTTON_2));
    HU.setSteeringInput_1(analogRead(PIN_STEERING_1));
    HU.setSteeringInput_2(analogRead(PIN_STEERING_2));
    
    
    switch (HU.getCommand()) {
        case HU.COMMAND::VOL_U:
            Consumer.write(MEDIA_VOLUME_UP);
            break;
            
        case HU.COMMAND::VOL_D:
            Consumer.write((MEDIA_VOLUME_DOWN));
            break;
            
        case HU.COMMAND::MUTE:
            Consumer.write((MEDIA_VOLUME_MUTE));
            break;
            
        case HU.COMMAND::PAUSE:
            Consumer.write(MEDIA_PLAY_PAUSE);
            break;
            
        //  Add as you wish.
            
        default:
            break;
    }
}
