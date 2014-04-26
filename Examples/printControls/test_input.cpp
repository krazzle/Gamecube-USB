#include "GamecubeController.h"
#include "stdio.h"


int main()
{
    GamecubeController* gc = new GamecubeController("/dev/hidraw0");
    gc->init();
    bool going = true;
    while(going){
    
        //be aware that capture is non-blocking
        gc->capture();
        if(gc->A_PRESSED)
            printf("A has been pressed\n");
        if(gc->B_PRESSED)
            printf("B has been pressed\n");
        if(gc->X_PRESSED)
            printf("X has been pressed\n");
        if(gc->Y_PRESSED)
            printf("Y has been pressed\n");
        if(gc->START_PRESSED){
            printf("Start has been pressed. Did you want to quit? Press A to quit and any other key to return\n");
	    gc->blockingCapture(); 
            if(gc->A_PRESSED)
            	going = false;
        }
        if(gc->Z_PRESSED)
            printf("Z has been pressed\n");
        if(gc->L_PRESSED)
            printf("L has been pressed\n");
        if(gc->R_PRESSED)
            printf("R has been pressed\n");
        if(gc->D_UP)
            printf("D-UP has been pressed\n");
        if(gc->D_UP_D_RIGHT)
            printf("D-UP/D-RIGHT have been pressed\n");
        if(gc->D_RIGHT)
            printf("D-RIGHT has been pressed\n");
        if(gc->D_RIGHT_D_DOWN)
            printf("D-RIGHT/D-DOWN has been pressed\n");
        if(gc->D_DOWN)
            printf("D-DOWN has been pressed\n");
        if(gc->D_DOWN_D_LEFT)
            printf("D-DOWN/D-LEFT have been pressed\n");        
        if(gc->D_LEFT)
            printf("D-LEFT has been pressed\n");
        if(gc->D_LEFT_D_UP)
            printf("D-LEFT/D-UP has been pressed\n");
        if(gc->JOYSTICK_X != 0 || gc->JOYSTICK_Y != 0)
            printf("Joystick changed (%d, %d)\n", gc->JOYSTICK_X, gc->JOYSTICK_Y);
        if(gc->CSTICK_X != 0 || gc->CSTICK_Y != 0)
            printf("Cstick changed (%d, %d)\n", gc->CSTICK_X, gc->CSTICK_Y);
    }   
    gc->close();
}

