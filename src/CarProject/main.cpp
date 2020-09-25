//
//  main.cpp
//  CarProject
//
//  Created by Sayed Hussein on 27/10/2018.
//  Copyright © 2018 Sayed Hussein. All rights reserved.
//

#include <iostream>
#include "ArduinoCpp.h"
#include "CarProject.ino"

int main(int argc, const char * argv[]) {
    
    setup();
    
    while (true) {
        loop();
        break;
    }
    
    return 0;
}
