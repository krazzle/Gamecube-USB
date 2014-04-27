#include <iostream>
#include <stdio.h>

struct State{
	long* current_state;
	char expected_state;
};


bool START_PRESSED; // 0
bool Y_PRESSED;		// 1
bool X_PRESSED;		// 2
bool B_PRESSED; 	// 3
bool A_PRESSED;		// 4
bool L_PRESSED;		// 5
bool R_PRESSED;		// 6
bool Z_PRESSED;		// 7
bool D_UP;			// 8
bool D_UP_D_RIGHT;	// 9 
bool D_RIGHT;		// 10
bool D_RIGHT_D_DOWN;// 11
bool D_DOWN;		// 12
bool D_DOWN_D_LEFT;	// 13
bool D_LEFT;		// 14
bool D_LEFT_D_UP;	// 15	

int JOYSTICK_X;
int JOYSTICK_Y;
int CSTICK_X;
int CSTICK_Y;


void init(char *name);
void close();
void capture();
int blockingCapture();

bool* getItem(int i);
void setAllToFalse();	

const char* nameOfDevice;
FILE* device;
char data[8];
State* states[16];
	
bool prev_state[16];
	
int prev_joystick_x;
int prev_joystick_y;
int prev_cstick_x;
int prev_cstick_y;
