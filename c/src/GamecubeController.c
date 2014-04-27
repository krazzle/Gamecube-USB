#include "GamecubeController.h"
#include <stdio.h>
#include <stdlib.h>


void gc_init(char* name){
    setAllToFalse();
	prev_joystick_x = -999;
	prev_joystick_y = -999;
	prev_cstick_x = -999;
	prev_cstick_y = -999;

	int i;
	for(i = 0; i < 16; i++){
		states[i] = (struct State*) malloc(sizeof(struct State));
		prev_state[i] = 0;
	}

	states[0]->current = (long*)&data[6]; states[0]->expected = 0x20;
	states[1]->current = (long*)&data[5]; states[1]->expected = 0x1f;
	states[2]->current = (long*)&data[5]; states[2]->expected = 0x2f;
	states[3]->current = (long*)&data[5]; states[3]->expected = 0x8f;
	states[4]->current = (long*)&data[5]; states[4]->expected = 0x4f;
	states[5]->current = (long*)&data[6]; states[5]->expected = 0x1;
	states[6]->current = (long*)&data[6]; states[6]->expected = 0x2;
	states[7]->current = (long*)&data[6]; states[7]->expected = 0x4;
	states[8]->current = (long*)&data[5]; states[8]->expected = 0x0;
	states[9]->current = (long*)&data[5]; states[9]->expected = 0x1;
	states[10]->current = (long*)&data[5]; states[10]->expected = 0x2;
	states[11]->current = (long*)&data[5]; states[11]->expected = 0x3;
	states[12]->current = (long*)&data[5]; states[12]->expected = 0x4;
	states[13]->current = (long*)&data[5]; states[13]->expected = 0x5;
	states[14]->current = (long*)&data[5]; states[14]->expected = 0x6;
	states[15]->current = (long*)&data[5]; states[15]->expected = 0x7;	

    if((device = fopen(name, "rw")) == NULL)
        perror("Failed to open the device: ");  
    printf("connected to controller\n");
}

int* getItem(int i){
    switch(i){
        case 0: return &START_PRESSED;
        case 1: return &Y_PRESSED;
        case 2: return &X_PRESSED;
        case 3: return &B_PRESSED;
        case 4: return &A_PRESSED;
        case 5: return &L_PRESSED;
        case 6: return &R_PRESSED;
        case 7: return &Z_PRESSED;
        case 8: return &D_UP;
        case 9: return &D_UP_D_RIGHT;
        case 10: return &D_RIGHT;
        case 11: return &D_RIGHT_D_DOWN;
        case 12: return &D_DOWN;
        case 13: return &D_DOWN_D_LEFT;
        case 14: return &D_LEFT;
        case 15: return &D_LEFT_D_UP;
        default: break;
    }
    return 0;
}

void setAllToFalse(){

    A_PRESSED = 0;
    B_PRESSED = 0;
    X_PRESSED = 0;
    Y_PRESSED = 0;
    START_PRESSED = 0;
    Z_PRESSED = 0;
    L_PRESSED = 0;
    R_PRESSED = 0;
    D_UP = 0;
    D_UP_D_RIGHT = 0;
    D_RIGHT = 0;
    D_RIGHT_D_DOWN = 0;
    D_DOWN = 0;
    D_DOWN_D_LEFT = 0;
    D_LEFT = 0;
    D_LEFT_D_UP = 0;
    JOYSTICK_X = 0;
    JOYSTICK_Y = 0;
    CSTICK_X = 0;
    CSTICK_Y = 0;
}

int gc_blockingCapture(){
    int waiting = 1;
    int retval = -1;
    while(waiting){
        gc_capture();
		int i;
        for(i = 0; i < 8; i++){
            if(*getItem(i)){
                retval = i; 
                waiting = 0;
            }
        }   
    }
    return retval;
}

void gc_capture(){
    fread((void*)data, sizeof(data), 1, device);
    setAllToFalse();

    if((prev_joystick_x == -999) && (prev_joystick_y == -999) && (prev_cstick_x == -999) && (prev_cstick_y == -999)){
        prev_joystick_x = data[0];
        prev_joystick_y = data[1];
        prev_cstick_x = data[3];
        prev_cstick_y = data[4];
    }

	int i;
    for(i = 0; i < 16; i++){
        struct State* temp = states[i];
        if((*(temp->current) & 0xff) == (temp->expected&0xff))
            prev_state[i] = 1;
        else {
            if(prev_state[i]){
                prev_state[i] = 0;
                int* var = getItem(i);
                *var = 1;
            }
        }
    }

    if(prev_joystick_x != data[0]){
        int diff = data[0] - prev_joystick_x;
        prev_joystick_x = data[0];
        JOYSTICK_X = diff;
    }

    if(prev_joystick_y != data[1]){
        int diff = data[1] - prev_joystick_y;
        prev_joystick_y = data[1];
        JOYSTICK_Y = diff;
    } 

    if(prev_cstick_x != data[3]){
        int diff = data[3] - prev_cstick_x;
        prev_cstick_x = data[3];
        CSTICK_X = diff;
    }  
    
    if(prev_cstick_y != data[4]){
        int diff = data[4] - prev_cstick_y;
        prev_cstick_y = data[4];
        CSTICK_Y = diff;
    }  

}

void gc_close(){
	int i; 
	for(i = 0; i < 16; i++)
		free(states[i]);
	
    fclose(device);
}
