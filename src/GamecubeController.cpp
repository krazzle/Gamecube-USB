#include <iostream>
#include <stdio.h>

GamecubeController::GamecubeController(const char* name){
    A_PRESSED = false;
    B_PRESSED = false;
    X_PRESSED = false;
    Y_PRESSED = false;
    START_PRESSED = false;
    Z_PRESSED = false;
    L_PRESSED = false;
    R_PRESSED = false;
    D_UP = false;
    D_UP_D_RIGHT = false;
    D_RIGHT = false;
    D_RIGHT_D_DOWN = false;
    D_DOWN = false;
    D_DOWN_D_LEFT = false;
    D_LEFT = false;
    D_LEFT_D_UP = false;
    JOYSTICK_X = 0;
    JOYSTICK_Y = 0;
    CSTICK_X = 0;
    CSTICK_Y = 0;
    
    nameOfDevice = name;
}

GamecubeController::~GamecubeController(){
    close();
}

void GamecubeController::init(){
    if((device = fopen(nameOfDevice, "rw")) == NULL)
        perror("Failed to open the device: ");  
}

void GamecubeController::capture(){
    fread((void*)data, sizeof(data), 1, device);
    
    if(data[6] == 0x20)
        START_PRESSED  = true;  
    else {
        if(START_PRESSED)
            START_PRESSED = false;
    }

    if(data[5] ==  0x1f)
        Y_PRESSED = true;
    else{
        if(Y_PRESSED)
            Y_PRESSED = false;
    }

    if(data[5] == 0x2f)
        X_PRESSED = true;
    else{
        if(X_PRESSED)
            X_PRESSED = false;
    }

    if(data[5] == 0xffffff8f)
        B_PRESSED = true;
    else{
        if(B_PRESSED)
            B_PRESSED = false;
    }

    if(data[5] == 0x4f)
        A_PRESSED = true;
    else{
        if(A_PRESSED)
            A_PRESSED = false;
    }

    if(data[6] == 0x1)
        L_PRESSED = true;
    else{
        if(L_PRESSED)
            L_PRESSED = false;
    }
    
    if(data[6] == 0x2)
        R_PRESSED = true;
    else{
        if(R_PRESSED)
            R_PRESSED = false;
    }


    if(data[6] == 0x4)
        Z_PRESSED = true;
    else{
        if(Z_PRESSED)
            Z_PRESSED = false;
    }
    
    
    if(data[5] == 0x0)
        D_UP = true;
    else{
        if(D_UP)
            D_UP = false;
    }

    if(data[5] == 0x1)
        D_UP_D_RIGHT = true;
    else{
        if(D_UP_D_RIGHT)
            D_UP_D_RIGHT = false;
    }
    
    if(data[5] == 0x2)
        D_RIGHT = true;
    else{
        if(D_RIGHT)
            D_RIGHT = false;
    }

    if(data[5] == 0x3)
        D_RIGHT_D_DOWN = true;
    else{
        if(D_RIGHT_D_DOWN)
            D_RIGHT_D_DOWN = false;
    }

    if(data[5] == 0x4)
        D_DOWN = true;
    else{
        if(D_DOWN)
            D_DOWN = false;
    }
    
    if(data[5] == 0x5)
        D_DOWN_D_LEFT = true;
    else{
        if(D_DOWN_D_LEFT)
            D_DOWN_D_LEFT = false;
    }
    
    if(data[5] == 0x6)
        D_LEFT = true;
    else{
        if(D_LEFT)
            D_LEFT = false;
    }

    if(data[5] == 0x7)
        D_LEFT_D_UP = true;
    else{
        if(D_LEFT_D_UP)
            D_LEFT_D_UP = false;
    }

    if(prev_joystick_x != data[0]){
        int diff = data[0] - prev_joystick_x;
        prev_joystick_x = data[0];
        JOYSTICK_X = diff;
    } else
        JOYSTICK_X = 0;

    if(prev_joystick_y != data[1]){
        int diff = data[1] - prev_joystick_y;
        prev_joystick_y = data[1];
        JOYSTICK_Y = diff;
    } else 
        JOYSTICK_Y = 0;

    if(prev_cstick_x != data[3]){
        int diff = data[3] - prev_cstick_x;
        prev_cstick_x = data[3];
        CSTICK_X = diff;
    } else 
        CSTICK_X = 0;
    
    if(prev_cstick_y != data[4]){
        int diff = data[4] - prev_cstick_y;
        prev_cstick_y = data[4];
        CSTICK_Y = diff;
    } else 
        CSTICK_Y = 0;

}

void GamecubeController::close(){
    fclose(device);
}
