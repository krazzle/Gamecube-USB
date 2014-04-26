#include <iostream>
#include <stdio.h>

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
	~GamecubeController()

	void init();
	void close();
	void capture();

private:	
	const char* nameOfDevice;
	FILE* device;
	char readData[8];
	int prev_joystick_x;
	int prev_joystick_y;
	int prev_cstick_x;
	int prev_cstick_y;
};
