#ifndef _GLOBALS_
#define _GLOBALS_

#include <windows.h>
enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FULLSCREEN false
#define RESIZABLE true
#define VSYNC true
#define TITLE "LittleEngine"


// Camera Default Configuration -----------
#define CAMERA_SPEED 0.05


#endif // !_GLOBALS_
