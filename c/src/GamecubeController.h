#pragma once
#include <stdio.h>

struct State{
	long* current;
	char expected;
};


int START_PRESSED; // 0
int Y_PRESSED;		// 1
int X_PRESSED;		// 2
int B_PRESSED; 	// 3
int A_PRESSED;		// 4
int L_PRESSED;		// 5
int R_PRESSED;		// 6
int Z_PRESSED;		// 7
int D_UP;			// 8
int D_UP_D_RIGHT;	// 9 
int D_RIGHT;		// 10
int D_RIGHT_D_DOWN;// 11
int D_DOWN;		// 12
int D_DOWN_D_LEFT;	// 13
int D_LEFT;		// 14
int D_LEFT_D_UP;	// 15	

int JOYSTICK_X;
int JOYSTICK_Y;
int CSTICK_X;
int CSTICK_Y;


void gc_init(char *name);
void gc_close();
void gc_capture();
int gc_blockingCapture();

int* getItem(int i);
void setAllToFalse();	

const char* nameOfDevice;
FILE* device;
char data[8];
struct State* states[16];
	
int prev_state[16];
	
int prev_joystick_x;
int prev_joystick_y;
int prev_cstick_x;
int prev_cstick_y;
