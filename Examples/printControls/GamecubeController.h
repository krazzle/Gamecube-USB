#include <iostream>
#include <stdio.h>

class State{
public:
	State(long *cur, char expected) { current_state = cur; expected_state = expected; }
	long* current_state;
	char expected_state;
};

class GamecubeController{
public:
	bool A_PRESSED;
	bool B_PRESSED;
	bool X_PRESSED;
	bool Y_PRESSED;
	bool START_PRESSED;
	bool Z_PRESSED;
	bool L_PRESSED;
	bool R_PRESSED;
	bool D_UP;
	bool D_UP_D_RIGHT;
	bool D_RIGHT;
	bool D_RIGHT_D_DOWN;
	bool D_DOWN;
	bool D_DOWN_D_LEFT;
	bool D_LEFT;
	bool D_LEFT_D_UP;

	int JOYSTICK_X;
	int JOYSTICK_Y;
	int CSTICK_X;
	int CSTICK_Y;

	GamecubeController(const char* name);
	~GamecubeController();

	void init();
	void close();
	void capture();

private:	
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
};
